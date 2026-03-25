// Optomotrist — LA-2A Style Optical Compressor (Perceptual Emulation)
// Edit this file, then run `just codegen` to regenerate
// the JUCE parameter bridge in src/dsp/generated/.

import("stdfaust.lib");

//==========================================================================
// Parameters
//==========================================================================

// --- Front Panel (authentic LA-2A controls) ---
peak_reduction = hslider("[1][id:peak_reduction] Peak Reduction", 50, 0, 100, 0.1) : si.smoo;
makeup_gain_db = hslider("[2][id:gain] Gain", 0, -20, 40, 0.1) : si.smoo;
limit_mode     = checkbox("[3][id:limit_mode] Limit/Compress");

// --- Back Panel ("screw" controls) ---
sc_emphasis = hslider("[4][id:sc_emphasis] SC Emphasis", 50, 0, 100, 0.1) : si.smoo;
sc_hpf_freq = hslider("[5][id:sc_hpf] SC HPF", 20, 20, 500, 1) : si.smoo;
t4_bias     = hslider("[6][id:t4_bias] T4 Bias", 50, 0, 100, 0.1) : si.smoo;

// --- Metering (output only, not an APVTS parameter) ---
gr_meter = hbargraph("[7][id:gr_meter] GR", -20, 0);

//==========================================================================
// Utilities
//==========================================================================

// Safe tau-to-pole conversion (prevents division by zero)
tau2p(t) = ba.tau2pole(max(0.0001, t));

// Custom tanh (in case ma.tanh is unavailable)
my_tanh(x) = (exp(2.0*x) - 1.0) / (exp(2.0*x) + 1.0);

// dB conversions
db2lin(x) = 10.0 ^ (x / 20.0);
lin2db(x) = 20.0 * log10(max(x, 1e-30));

//==========================================================================
// Sidechain Filter
//==========================================================================
// Highpass to reject low frequency pumping, then add HF emphasis
// to make compressor more sensitive to sibilance/presence

sc_filter(x) = hpf_out + hf_emphasis_out
with {
    hpf_out = fi.highpass(1, sc_hpf_freq, x);
    hf_component = fi.highpass(1, 1000, hpf_out);
    emphasis_amount = sc_emphasis / 100.0;
    hf_emphasis_out = hf_component * emphasis_amount;
};

//==========================================================================
// Gain Computer
//==========================================================================
// Soft-knee gain computation in dB domain.
// Mode selects between compress (gentler ratio, wide knee)
// and limit (high ratio, narrow knee).

gain_computer(level_db) = gr_db
with {
    threshold = -20.0;

    // Interpolate between compress and limit based on limit_mode
    ratio  = select2(limit_mode, 3.5, 100.0);
    knee_w = select2(limit_mode, 20.0, 6.0);

    half_knee = knee_w / 2.0;
    over = level_db - threshold;

    // Soft knee: below knee, in knee, above knee
    gr_below = 0.0;
    gr_knee  = ((1.0 / ratio - 1.0) * (over + half_knee) * (over + half_knee))
               / (2.0 * knee_w);
    gr_above = (1.0 / ratio - 1.0) * over;

    gr_db = (over < -half_knee) * gr_below
          + (over >= -half_knee) * (over <= half_knee) * gr_knee
          + (over > half_knee) * gr_above;
};

//==========================================================================
// T4 Opto Cell Model
//==========================================================================
// Models the CdS photoresistor behavior:
// - Fast attack (~10ms)
// - Program-dependent release: dual time constants blended by
//   a "charge" accumulator that tracks compression history
// - T4 bias control shifts the attack/release characteristics

// T4 opto cell outputs envelope level (linear).
// Gain computer is applied externally.
t4_cell(sc_level) = opto_env
letrec {
    // Charge accumulator: tracks compression history
    // Increases when compressing (short tau), decays when idle (long tau)
    'charge = charge + (target_charge - charge) * (1.0 - charge_pole)
    with {
        is_compressing = (sc_level > 0.001);
        target_charge = is_compressing;
        charge_tau = select2(is_compressing, 10.0, 2.0);
        charge_pole = tau2p(charge_tau);
    };

    // Envelope follower with asymmetric attack/release
    'opto_env = opto_env + (target - opto_env) * (1.0 - pole)
    with {
        // T4 bias shifts the base attack/release times
        bias_scale = 0.5 + (t4_bias / 100.0);  // 0.5 to 1.5

        // Attack: ~10ms base, modulated by bias
        attack_tau = 0.010 * bias_scale;

        // Release: blend of fast and slow, modulated by charge history
        fast_rel_tau = 0.060 * bias_scale;
        slow_rel_tau = (0.5 + charge * 4.5) * bias_scale;

        // More charge = more slow release (CdS memory effect)
        slow_blend = 0.30 + charge * 0.55;  // 30% to 85% slow
        rel_tau = fast_rel_tau * (1.0 - slow_blend) + slow_rel_tau * slow_blend;

        is_attack = (sc_level > opto_env);
        current_tau = select2(is_attack, rel_tau, attack_tau);
        pole = tau2p(current_tau);

        target = sc_level;
    };
};

//==========================================================================
// Tube Saturation Stage
//==========================================================================
// Asymmetric tanh waveshaper for even harmonic generation.
// Offset creates asymmetry; DC blocker removes resulting offset.

tube_stage(x) = saturated : fi.dcblocker
with {
    drive = 1.5;
    offset = 0.1;  // asymmetry for even harmonics
    saturated = (my_tanh(x * drive + offset) - my_tanh(offset)) / drive;
};

//==========================================================================
// Main Stereo Compressor (Feedback Topology)
//==========================================================================
// Signal flow:
//   Input L/R -> [apply gain reduction] -> [tube stage] -> [makeup gain] -> Output L/R
//                       ^                                                     |
//                       |                 feedback path (1-sample delay)       |
//                   gr_db  <-- gain_computer <-- t4_cell <-- sc_filter <-- max(|L|,|R|)

stereo_compressor = (stereo_block ~ _) : (!, _, _)
with {
    // Peak Reduction scales the sidechain drive (like the real knob)
    sc_drive = peak_reduction / 100.0 * 4.0;  // 0 to 4x sidechain gain
    makeup_lin = db2lin(makeup_gain_db);

    // Core processing block
    // Takes feedback gr_db from previous sample, plus stereo input
    // Outputs: new gr_db (for feedback), processed L, processed R
    stereo_block(gr_prev, l, r) = gr_new, out_l, out_r
    with {
        // Apply previous gain reduction
        gr_lin = db2lin(gr_prev);
        comp_l = l * gr_lin;
        comp_r = r * gr_lin;

        // Tube saturation on compressed signal
        sat_l = tube_stage(comp_l);
        sat_r = tube_stage(comp_r);

        // Output with makeup gain
        out_l = sat_l * makeup_lin;
        out_r = sat_r * makeup_lin;

        // Sidechain: detect from compressed output (feedback topology)
        sc_input = max(abs(comp_l), abs(comp_r));
        sc_filtered = sc_filter(sc_input);
        sc_driven = abs(sc_filtered) * sc_drive;

        // T4 opto cell produces envelope level; gain_computer converts to dB reduction
        gr_new = gain_computer(lin2db(max(t4_cell(sc_driven), 1e-30))) : gr_meter;
    };
};

//==========================================================================
// Process
//==========================================================================

process = stereo_compressor;
