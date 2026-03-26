// Optomotrist — LA-2A Style Optical Compressor (Perceptual Emulation)
// Edit this file, then run `just codegen` to regenerate
// the JUCE parameter bridge in src/dsp/generated/.

import("stdfaust.lib");

//==========================================================================
// Parameters
//==========================================================================

// --- Front Panel (authentic LA-2A controls) ---
input_drive_db = hslider("[1][id:input_drive] Input Drive", 0, -20, 20, 0.1) : si.smoo;
peak_reduction = hslider("[2][id:peak_reduction] Peak Reduction", 50, 0, 100, 0.1) : si.smoo;
makeup_gain_db = hslider("[3][id:gain] Gain", 0, -20, 40, 0.1) : si.smoo;
mix            = hslider("[4][id:mix] Mix", 100, 0, 100, 0.1) : si.smoo;
limit_mode     = checkbox("[5][id:limit_mode] Limit/Compress");

// --- Back Panel ("screw" controls) ---
sc_emphasis      = hslider("[6][id:sc_emphasis] SC Emphasis", 50, 0, 100, 0.1) : si.smoo;
sc_emphasis_freq = hslider("[7][id:sc_emphasis_freq][scale:log] SC Emp Freq", 1000, 200, 8000, 1) : si.smoo;
sc_hpf_freq      = hslider("[8][id:sc_hpf][scale:log] SC HPF", 20, 20, 500, 1) : si.smoo;
t4_bias          = hslider("[9][id:t4_bias] T4 Bias", 50, 0, 100, 0.1) : si.smoo;

// --- Metering (output only, not an APVTS parameter) ---
gr_meter = hbargraph("[10][id:gr_meter] GR", -60, 0);

//==========================================================================
// Utilities
//==========================================================================

// Safe tau-to-pole conversion (prevents division by zero)
tau2p(t) = ba.tau2pole(max(0.0001, t));

// dB conversions
db2lin(x) = 10.0 ^ (x / 20.0);
lin2db(x) = 20.0 * log10(max(x, 1e-30));

//==========================================================================
// Sidechain Filter
//==========================================================================
// Applied to the RAW BIPOLAR audio signal (not rectified).
// Highpass to reject low frequency pumping, then add HF emphasis
// to make compressor more sensitive to sibilance/presence.

sc_filter(x) = hpf_out + hf_emphasis_out
with {
    hpf_out = fi.highpass(1, sc_hpf_freq, x);
    hf_component = fi.highpass(1, sc_emphasis_freq, hpf_out);
    emphasis_amount = sc_emphasis / 100.0;
    hf_emphasis_out = hf_component * emphasis_amount;
};

//==========================================================================
// Peak Detector
//==========================================================================
// Fast envelope follower to bridge across zero-crossings.
// The T4 cell handles the musically meaningful attack/release shaping;
// this just ensures the gain computer sees a stable per-cycle peak level.
//   Attack:  ~0.1ms (near-instant peak capture)
//   Release: ~5ms   (bridges zero crossings; decays within a few cycles)

peak_detector(x) = peak_env
letrec {
    'peak_env = peak_env + (x - peak_env) * (1.0 - pole)
    with {
        is_attack = (x > peak_env);
        att_pole = tau2p(0.0001);  // 0.1ms
        rel_pole = tau2p(0.005);   // 5ms
        pole = select2(is_attack, rel_pole, att_pole);
    };
};

//==========================================================================
// Gain Computer
//==========================================================================
// Soft-knee gain computation in dB domain.
//
// Peak Reduction controls the threshold: higher PR = lower threshold =
// more signal above threshold = more compression. This models the real
// LA-2A where PR controls EL panel drive (more drive = more light =
// more photoresistor change = more gain reduction).
//
// PR also adds a small SC boost (0-10dB) for additional sensitivity
// at high settings, matching the real unit's behavior at extremes.

gain_computer(level_db) = gr_db
with {
    // Threshold sweeps from -10dB (PR=0, nothing compresses)
    // down to -30dB (PR=100, quiet material compresses too)
    pr_norm = peak_reduction / 100.0;
    threshold = -10.0 - pr_norm * 20.0;

    // Small SC boost at high PR settings (0 to 10dB)
    sc_boost = pr_norm * 10.0;
    boosted_level = level_db + sc_boost;

    // Compress mode: gentle ratio, wide knee for smooth leveling
    // Limit mode: high ratio, narrow knee for brickwall behavior
    ratio  = select2(limit_mode, 4.0, 100.0);
    knee_w = select2(limit_mode, 12.0, 6.0);

    half_knee = knee_w / 2.0;
    over = boosted_level - threshold;

    // Soft knee: below knee, in knee, above knee
    gr_knee  = ((1.0 / ratio - 1.0) * (over + half_knee) * (over + half_knee))
               / (2.0 * knee_w);
    gr_above = (1.0 / ratio - 1.0) * over;

    gr_db = (over < -half_knee) * 0.0
          + (over >= -half_knee) * (over <= half_knee) * gr_knee
          + (over > half_knee) * gr_above;
};

//==========================================================================
// T4 Opto Cell Model
//==========================================================================
// The T4 cell smooths the GAIN REDUCTION value (in dB), not the raw signal.
// This models the CdS photoresistor's sluggish response to the EL panel:
// - Fast attack (~10ms)
// - Program-dependent release: dual time constants blended by
//   a "charge" accumulator that tracks compression history
// - T4 bias control shifts the attack/release characteristics
//
// Input: desired_gr (dB, negative, from gain computer)
// Output: smoothed gr (dB, negative)

t4_cell(desired_gr) = opto_env
letrec {
    // Charge accumulator: tracks compression history (how long we've been compressing)
    // Increases when compressing (short tau), decays when idle (long tau)
    'charge = charge + (target_charge - charge) * (1.0 - charge_pole)
    with {
        is_compressing = (desired_gr < -0.5);  // more than 0.5dB of GR requested
        target_charge = is_compressing;
        charge_tau = select2(is_compressing, 2.0, 1.0);  // 1s charge, 2s decay
        charge_pole = tau2p(charge_tau);
    };

    // Envelope follower: smooths the gain reduction value
    // Asymmetric attack/release like real opto cell
    'opto_env = opto_env + (desired_gr - opto_env) * (1.0 - pole)
    with {
        // T4 bias shifts the base attack/release times
        // bias 0 = fast (0.5x), bias 100 = slow (1.5x)
        bias_scale = 0.5 + (t4_bias / 100.0);

        // Attack: ~10ms base (opto cell lights up fast)
        attack_tau = 0.010 * bias_scale;

        // Release: blend of fast and slow, modulated by charge history
        // Fast release: ~60ms (initial recovery, first 50% of GR)
        // Slow release: 0.3s to 1.5s depending on compression history
        fast_rel_tau = 0.060 * bias_scale;
        slow_rel_tau = (0.3 + charge * 1.2) * bias_scale;

        // More charge = more slow release dominance (CdS memory effect)
        slow_blend = 0.20 + charge * 0.40;  // 20% to 60% slow
        rel_tau = fast_rel_tau * (1.0 - slow_blend) + slow_rel_tau * slow_blend;

        // Attack = GR getting deeper (desired_gr more negative than current)
        // Release = GR getting shallower (desired_gr less negative than current)
        is_attack = (desired_gr < opto_env);
        current_tau = select2(is_attack, rel_tau, attack_tau);
        pole = tau2p(current_tau);
    };
};

//==========================================================================
// Tube Saturation Stage
//==========================================================================
// Models a 12AX7 triode stage with:
//   1. Asymmetric soft-clip transfer function:
//      - Positive swing (grid conduction): clips harder (k=0.6)
//      - Negative swing (cutoff region): clips gently (k=0.15)
//      - Produces 2nd-harmonic-dominant spectrum (H2 ~4dB above H3)
//   2. Feedback lowpass for frequency-dependent saturation:
//      - Lows pass through cleaner (feedback reduces net drive)
//      - Highs get more harmonic content (feedback attenuated)
//      - Models plate impedance / coupling cap interaction
//   3. DC blocker to remove asymmetry-induced offset

// Asymmetric waveshaper: rational soft-clip with different
// coefficients for positive (grid conduction) and negative (cutoff)
triode_clip(x) = clipped / drive
with {
    drive = 1.15;   // subtle — this is a compressor, not a guitar amp
    k_pos = 0.6;   // harder clip on positive (grid conduction)
    k_neg = 0.15;  // gentle clip on negative (cutoff region)
    xd = x * drive;
    clipped = select2(xd >= 0,
        xd / (1.0 - k_neg * xd),    // negative: xd<0, so -k_neg*xd is positive
        xd / (1.0 + k_pos * xd));   // positive: soft clip toward ceiling
};

// Tube stage with feedback lowpass
// Feedback loop: output is lowpass-filtered and subtracted from input,
// so low frequencies see reduced net drive (cleaner) while highs
// see full drive (more harmonics). Cutoff ~1kHz, amount 0.3.
tube_stage(x) = tube_out
letrec {
    'fb_lp = fb_lp * fb_pole + tube_out * (1.0 - fb_pole)
    with {
        fb_pole = exp(-2.0 * ma.PI * 1000.0 / ma.SR);
    };
    'tube_out = triode_clip(x - 0.3 * fb_lp) : fi.dcblocker;
};

//==========================================================================
// Main Stereo Compressor (Feedforward Sidechain)
//==========================================================================
// The sidechain detects the INPUT signal level (before compression).
// Peak Reduction controls the gain computer's threshold and SC sensitivity
// (moved into the gain computer, not a separate boost stage).
//
// Signal flow:
//   Input L/R ─┬─> [apply GR] -> [tube stage] -> [makeup gain] -> Output L/R
//              |        ^
//              |     gr_db (1-sample delay)
//              |        |
//              └─> [sc_filter] -> [peak_det] -> [gain_computer(PR)] -> [t4_cell] -> gr_db

stereo_compressor = (stereo_block ~ _) : (!, _, _)
with {
    input_drive_lin = db2lin(input_drive_db);
    makeup_lin = db2lin(makeup_gain_db);

    // Core processing block
    // Takes feedback gr_db from previous sample, plus stereo input
    // Outputs: new gr_db (for feedback), processed L, processed R
    stereo_block(gr_prev, l, r) = gr_new, out_l, out_r
    with {
        // Input drive: boosts signal before compression and sidechain
        driven_l = l * input_drive_lin;
        driven_r = r * input_drive_lin;

        // Apply previous gain reduction (gr_prev is negative dB)
        gr_lin = db2lin(gr_prev);
        comp_l = driven_l * gr_lin;
        comp_r = driven_r * gr_lin;

        // Tube saturation on compressed signal
        sat_l = tube_stage(comp_l);
        sat_r = tube_stage(comp_r);

        // Output with makeup gain
        out_l = sat_l * makeup_lin;
        out_r = sat_r * makeup_lin;

        // --- Sidechain path (sees the driven signal) ---
        sc_l = sc_filter(driven_l);
        sc_r = sc_filter(driven_r);
        sc_peak = peak_detector(max(abs(sc_l), abs(sc_r)));

        // Gain computer uses peak-detected level; PR is internal to gain_computer
        sc_level_db = lin2db(sc_peak);
        desired_gr = gain_computer(sc_level_db);

        // T4 opto cell: smooth the GR with attack/release envelope
        gr_new = t4_cell(desired_gr) : gr_meter;
    };
};

//==========================================================================
// Process
//==========================================================================

process = ef.dryWetMixer(mix / 100.0, stereo_compressor);
