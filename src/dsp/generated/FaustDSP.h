/* ------------------------------------------------------------
name: "optomotrist"
Code generated with Faust 2.79.3 (https://faust.grame.fr)
Compilation options: -lang cpp -ct 1 -cn OptomotristDSP -scn  -es 1 -mcd 0 -mdd 1024 -mdy 33 -uim -single -ftz 0 -vec -lv 1 -vs 32
------------------------------------------------------------ */

#ifndef  __OptomotristDSP_H__
#define  __OptomotristDSP_H__

#include "FaustDefs.h"

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

#ifndef FAUSTCLASS 
#define FAUSTCLASS OptomotristDSP
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

#if defined(_WIN32)
#define RESTRICT __restrict
#else
#define RESTRICT __restrict__
#endif

static float OptomotristDSP_faustpower2_f(float value) {
	return value * value;
}

struct OptomotristDSP {
	
	int fSampleRate;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fHslider0;
	float fConst2;
	float fRec7[64];
	int fRec7_idx;
	int fRec7_idx_save;
	FAUSTFLOAT fHslider1;
	float fRec8[64];
	int fRec8_idx;
	int fRec8_idx_save;
	float fConst3;
	float fYec0[64];
	int fYec0_idx;
	int fYec0_idx_save;
	float fRec6[64];
	int fRec6_idx;
	int fRec6_idx_save;
	FAUSTFLOAT fHslider2;
	float fRec10[64];
	int fRec10_idx;
	int fRec10_idx_save;
	float fRec9[64];
	int fRec9_idx;
	int fRec9_idx_save;
	FAUSTFLOAT fHslider3;
	float fRec11[64];
	int fRec11_idx;
	int fRec11_idx_save;
	float fYec1[64];
	int fYec1_idx;
	int fYec1_idx_save;
	float fRec12[64];
	int fRec12_idx;
	int fRec12_idx_save;
	float fRec13[64];
	int fRec13_idx;
	int fRec13_idx_save;
	float fConst4;
	float fConst5;
	float fRec5[64];
	int fRec5_idx;
	int fRec5_idx_save;
	FAUSTFLOAT fHslider4;
	float fRec14[64];
	int fRec14_idx;
	int fRec14_idx_save;
	FAUSTFLOAT fCheckbox0;
	float fConst6;
	float fRec3[64];
	int fRec3_idx;
	int fRec3_idx_save;
	FAUSTFLOAT fHslider5;
	float fRec15[64];
	int fRec15_idx;
	int fRec15_idx_save;
	float fRec4[64];
	int fRec4_idx;
	int fRec4_idx_save;
	FAUSTFLOAT fHbargraph0;
	float fRec0[64];
	int fRec0_idx;
	int fRec0_idx_save;
	float fConst7;
	float fConst8;
	float fRec16[64];
	int fRec16_idx;
	int fRec16_idx_save;
	float fYec2[64];
	int fYec2_idx;
	int fYec2_idx_save;
	float fRec18[64];
	int fRec18_idx;
	int fRec18_idx_save;
	float fRec17[64];
	int fRec17_idx;
	int fRec17_idx_save;
	FAUSTFLOAT fHslider6;
	float fRec19[64];
	int fRec19_idx;
	int fRec19_idx_save;
	float fRec20[64];
	int fRec20_idx;
	int fRec20_idx_save;
	float fYec3[64];
	int fYec3_idx;
	int fYec3_idx_save;
	float fRec22[64];
	int fRec22_idx;
	int fRec22_idx_save;
	float fRec21[64];
	int fRec21_idx;
	int fRec21_idx_save;
	FAUSTFLOAT fHslider7;
	float fRec23[64];
	int fRec23_idx;
	int fRec23_idx_save;
	
	OptomotristDSP() {
	}
	
	void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "1.21.0");
		m->declare("compile_options", "-lang cpp -ct 1 -cn OptomotristDSP -scn  -es 1 -mcd 0 -mdd 1024 -mdy 33 -uim -single -ftz 0 -vec -lv 1 -vs 32");
		m->declare("filename", "optomotrist.dsp");
		m->declare("filters.lib/dcblocker:author", "Julius O. Smith III");
		m->declare("filters.lib/dcblocker:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/dcblocker:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/highpass:author", "Julius O. Smith III");
		m->declare("filters.lib/highpass:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/lowpass0_highpass1", "MIT-style STK-4.3 license");
		m->declare("filters.lib/lowpass0_highpass1:author", "Julius O. Smith III");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/pole:author", "Julius O. Smith III");
		m->declare("filters.lib/pole:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/pole:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf1:author", "Julius O. Smith III");
		m->declare("filters.lib/tf1:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf1:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf1s:author", "Julius O. Smith III");
		m->declare("filters.lib/tf1s:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf1s:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/version", "1.7.1");
		m->declare("filters.lib/zero:author", "Julius O. Smith III");
		m->declare("filters.lib/zero:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/zero:license", "MIT-style STK-4.3 license");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.8.1");
		m->declare("misceffects.lib/dryWetMixer:author", "David Braun, revised by Stéphane Letz");
		m->declare("misceffects.lib/name", "Misc Effects Library");
		m->declare("misceffects.lib/version", "2.5.1");
		m->declare("name", "optomotrist");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "1.3.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "1.6.0");
	}

	virtual int getNumInputs() {
		return 2;
	}
	virtual int getNumOutputs() {
		return 2;
	}
	
	static void classInit(int sample_rate) {
		(void)sample_rate;
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		fConst0 = std::min<float>(1.92e+05f, std::max<float>(1.0f, float(fSampleRate)));
		fConst1 = 44.1f / fConst0;
		fConst2 = 1.0f - fConst1;
		fConst3 = 3.1415927f / fConst0;
		fConst4 = std::exp(-(2e+02f / fConst0));
		fConst5 = std::exp(-(1e+04f / fConst0));
		fConst6 = 1.0f / fConst0;
		fConst7 = std::exp(-(6283.1855f / fConst0));
		fConst8 = 1.0f - fConst7;
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(2e+01f);
		fHslider1 = FAUSTFLOAT(0.0f);
		fHslider2 = FAUSTFLOAT(1e+03f);
		fHslider3 = FAUSTFLOAT(5e+01f);
		fHslider4 = FAUSTFLOAT(5e+01f);
		fCheckbox0 = FAUSTFLOAT(0.0f);
		fHslider5 = FAUSTFLOAT(5e+01f);
		fHslider6 = FAUSTFLOAT(0.0f);
		fHslider7 = FAUSTFLOAT(1e+02f);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 64; l0 = l0 + 1) {
			fRec7[l0] = 0.0f;
		}
		fRec7_idx = 0;
		fRec7_idx_save = 0;
		for (int l1 = 0; l1 < 64; l1 = l1 + 1) {
			fRec8[l1] = 0.0f;
		}
		fRec8_idx = 0;
		fRec8_idx_save = 0;
		for (int l2 = 0; l2 < 64; l2 = l2 + 1) {
			fYec0[l2] = 0.0f;
		}
		fYec0_idx = 0;
		fYec0_idx_save = 0;
		for (int l3 = 0; l3 < 64; l3 = l3 + 1) {
			fRec6[l3] = 0.0f;
		}
		fRec6_idx = 0;
		fRec6_idx_save = 0;
		for (int l4 = 0; l4 < 64; l4 = l4 + 1) {
			fRec10[l4] = 0.0f;
		}
		fRec10_idx = 0;
		fRec10_idx_save = 0;
		for (int l5 = 0; l5 < 64; l5 = l5 + 1) {
			fRec9[l5] = 0.0f;
		}
		fRec9_idx = 0;
		fRec9_idx_save = 0;
		for (int l6 = 0; l6 < 64; l6 = l6 + 1) {
			fRec11[l6] = 0.0f;
		}
		fRec11_idx = 0;
		fRec11_idx_save = 0;
		for (int l7 = 0; l7 < 64; l7 = l7 + 1) {
			fYec1[l7] = 0.0f;
		}
		fYec1_idx = 0;
		fYec1_idx_save = 0;
		for (int l8 = 0; l8 < 64; l8 = l8 + 1) {
			fRec12[l8] = 0.0f;
		}
		fRec12_idx = 0;
		fRec12_idx_save = 0;
		for (int l9 = 0; l9 < 64; l9 = l9 + 1) {
			fRec13[l9] = 0.0f;
		}
		fRec13_idx = 0;
		fRec13_idx_save = 0;
		for (int l10 = 0; l10 < 64; l10 = l10 + 1) {
			fRec5[l10] = 0.0f;
		}
		fRec5_idx = 0;
		fRec5_idx_save = 0;
		for (int l11 = 0; l11 < 64; l11 = l11 + 1) {
			fRec14[l11] = 0.0f;
		}
		fRec14_idx = 0;
		fRec14_idx_save = 0;
		for (int l12 = 0; l12 < 64; l12 = l12 + 1) {
			fRec3[l12] = 0.0f;
		}
		fRec3_idx = 0;
		fRec3_idx_save = 0;
		for (int l13 = 0; l13 < 64; l13 = l13 + 1) {
			fRec15[l13] = 0.0f;
		}
		fRec15_idx = 0;
		fRec15_idx_save = 0;
		for (int l14 = 0; l14 < 64; l14 = l14 + 1) {
			fRec4[l14] = 0.0f;
		}
		fRec4_idx = 0;
		fRec4_idx_save = 0;
		for (int l15 = 0; l15 < 64; l15 = l15 + 1) {
			fRec0[l15] = 0.0f;
		}
		fRec0_idx = 0;
		fRec0_idx_save = 0;
		for (int l16 = 0; l16 < 64; l16 = l16 + 1) {
			fRec16[l16] = 0.0f;
		}
		fRec16_idx = 0;
		fRec16_idx_save = 0;
		for (int l17 = 0; l17 < 64; l17 = l17 + 1) {
			fYec2[l17] = 0.0f;
		}
		fYec2_idx = 0;
		fYec2_idx_save = 0;
		for (int l18 = 0; l18 < 64; l18 = l18 + 1) {
			fRec18[l18] = 0.0f;
		}
		fRec18_idx = 0;
		fRec18_idx_save = 0;
		for (int l19 = 0; l19 < 64; l19 = l19 + 1) {
			fRec17[l19] = 0.0f;
		}
		fRec17_idx = 0;
		fRec17_idx_save = 0;
		for (int l20 = 0; l20 < 64; l20 = l20 + 1) {
			fRec19[l20] = 0.0f;
		}
		fRec19_idx = 0;
		fRec19_idx_save = 0;
		for (int l21 = 0; l21 < 64; l21 = l21 + 1) {
			fRec20[l21] = 0.0f;
		}
		fRec20_idx = 0;
		fRec20_idx_save = 0;
		for (int l22 = 0; l22 < 64; l22 = l22 + 1) {
			fYec3[l22] = 0.0f;
		}
		fYec3_idx = 0;
		fYec3_idx_save = 0;
		for (int l23 = 0; l23 < 64; l23 = l23 + 1) {
			fRec22[l23] = 0.0f;
		}
		fRec22_idx = 0;
		fRec22_idx_save = 0;
		for (int l24 = 0; l24 < 64; l24 = l24 + 1) {
			fRec21[l24] = 0.0f;
		}
		fRec21_idx = 0;
		fRec21_idx_save = 0;
		for (int l25 = 0; l25 < 64; l25 = l25 + 1) {
			fRec23[l25] = 0.0f;
		}
		fRec23_idx = 0;
		fRec23_idx_save = 0;
	}
	
	virtual void init(int sample_rate) {
		classInit(sample_rate);
		instanceInit(sample_rate);
	}
	
	virtual void instanceInit(int sample_rate) {
		instanceConstants(sample_rate);
		instanceResetUserInterface();
		instanceClear();
	}
	
	virtual OptomotristDSP* clone() {
		return new OptomotristDSP();
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("optomotrist");
		ui_interface->declare(&fHbargraph0, "10", "");
		ui_interface->declare(&fHbargraph0, "id", "gr_meter");
		ui_interface->addHorizontalBargraph("GR", &fHbargraph0, FAUSTFLOAT(-6e+01f), FAUSTFLOAT(0.0f));
		ui_interface->declare(&fHslider1, "1", "");
		ui_interface->declare(&fHslider1, "id", "input_drive");
		ui_interface->addHorizontalSlider("Input Drive", &fHslider1, FAUSTFLOAT(0.0f), FAUSTFLOAT(-2e+01f), FAUSTFLOAT(2e+01f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fHslider4, "2", "");
		ui_interface->declare(&fHslider4, "id", "peak_reduction");
		ui_interface->addHorizontalSlider("Peak Reduction", &fHslider4, FAUSTFLOAT(5e+01f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1e+02f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fHslider6, "3", "");
		ui_interface->declare(&fHslider6, "id", "gain");
		ui_interface->addHorizontalSlider("Gain", &fHslider6, FAUSTFLOAT(0.0f), FAUSTFLOAT(-2e+01f), FAUSTFLOAT(4e+01f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fHslider7, "4", "");
		ui_interface->declare(&fHslider7, "id", "mix");
		ui_interface->addHorizontalSlider("Mix", &fHslider7, FAUSTFLOAT(1e+02f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1e+02f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fCheckbox0, "5", "");
		ui_interface->declare(&fCheckbox0, "id", "limit_mode");
		ui_interface->addCheckButton("Limit/Compress", &fCheckbox0);
		ui_interface->declare(&fHslider3, "6", "");
		ui_interface->declare(&fHslider3, "id", "sc_emphasis");
		ui_interface->addHorizontalSlider("SC Emphasis", &fHslider3, FAUSTFLOAT(5e+01f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1e+02f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fHslider2, "7", "");
		ui_interface->declare(&fHslider2, "id", "sc_emphasis_freq");
		ui_interface->declare(&fHslider2, "scale", "log");
		ui_interface->addHorizontalSlider("SC Emp Freq", &fHslider2, FAUSTFLOAT(1e+03f), FAUSTFLOAT(2e+02f), FAUSTFLOAT(8e+03f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider0, "8", "");
		ui_interface->declare(&fHslider0, "id", "sc_hpf");
		ui_interface->declare(&fHslider0, "scale", "log");
		ui_interface->addHorizontalSlider("SC HPF", &fHslider0, FAUSTFLOAT(2e+01f), FAUSTFLOAT(2e+01f), FAUSTFLOAT(5e+02f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider5, "9", "");
		ui_interface->declare(&fHslider5, "id", "t4_bias");
		ui_interface->addHorizontalSlider("T4 Bias", &fHslider5, FAUSTFLOAT(5e+01f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1e+02f), FAUSTFLOAT(0.1f));
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0_ptr = inputs[0];
		FAUSTFLOAT* input1_ptr = inputs[1];
		FAUSTFLOAT* output0_ptr = outputs[0];
		FAUSTFLOAT* output1_ptr = outputs[1];
		float fSlow0 = fConst1 * float(fHslider0);
		float fSlow1 = fConst1 * float(fHslider1);
		float fZec0[32];
		float fZec1[32];
		float fZec2[32];
		float fZec3[32];
		float fZec4[32];
		float fSlow2 = fConst1 * float(fHslider2);
		float fZec5[32];
		float fZec6[32];
		float fZec7[32];
		float fZec8[32];
		float fSlow3 = fConst1 * float(fHslider3);
		float fZec9[32];
		float fSlow4 = fConst1 * float(fHslider4);
		int iSlow5 = int(float(fCheckbox0));
		float fSlow6 = 1.0f / ((iSlow5) ? 1e+02f : 4.0f) + -1.0f;
		float fZec10[32];
		float fZec11[32];
		float fSlow7 = ((iSlow5) ? 6.0f : 12.0f);
		float fSlow8 = 0.5f * fSlow7;
		float fZec12[32];
		int iZec13[32];
		float fZec14[32];
		int iZec15[32];
		float fSlow9 = fConst1 * float(fHslider5);
		float fZec16[32];
		float fZec17[32];
		float fZec18[32];
		int iZec19[32];
		float fZec20[32];
		float fZec21[32];
		float fSlow10 = fConst1 * float(fHslider6);
		float fZec22[32];
		float fRec1[32];
		float fZec23[32];
		float fRec2[32];
		float fSlow11 = fConst1 * float(fHslider7);
		float fZec24[32];
		for (int vindex = 0; vindex < count; vindex = vindex + 32) {
			FAUSTFLOAT* input0 = &input0_ptr[vindex];
			FAUSTFLOAT* input1 = &input1_ptr[vindex];
			FAUSTFLOAT* output0 = &output0_ptr[vindex];
			FAUSTFLOAT* output1 = &output1_ptr[vindex];
			int vsize = std::min<int>(32, count - vindex);
			/* Recursive loop 0 */
			/* Pre code */
			fRec7_idx = (fRec7_idx + fRec7_idx_save) & 63;
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec7[(i + fRec7_idx) & 63] = fSlow0 + fConst2 * fRec7[(i + fRec7_idx - 1) & 63];
			}
			/* Post code */
			fRec7_idx_save = vsize;
			/* Recursive loop 1 */
			/* Pre code */
			fRec8_idx = (fRec8_idx + fRec8_idx_save) & 63;
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec8[(i + fRec8_idx) & 63] = fSlow1 + fConst2 * fRec8[(i + fRec8_idx - 1) & 63];
			}
			/* Post code */
			fRec8_idx_save = vsize;
			/* Vectorizable loop 2 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec0[i] = std::tan(fConst3 * fRec7[(i + fRec7_idx) & 63]);
			}
			/* Recursive loop 3 */
			/* Pre code */
			fRec10_idx = (fRec10_idx + fRec10_idx_save) & 63;
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec10[(i + fRec10_idx) & 63] = fSlow2 + fConst2 * fRec10[(i + fRec10_idx - 1) & 63];
			}
			/* Post code */
			fRec10_idx_save = vsize;
			/* Vectorizable loop 4 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec1[i] = 1.0f / fZec0[i];
			}
			/* Vectorizable loop 5 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec3[i] = std::pow(1e+01f, 0.05f * fRec8[(i + fRec8_idx) & 63]);
			}
			/* Vectorizable loop 6 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec5[i] = std::tan(fConst3 * fRec10[(i + fRec10_idx) & 63]);
			}
			/* Vectorizable loop 7 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec2[i] = 1.0f - fZec1[i];
			}
			/* Vectorizable loop 8 */
			/* Pre code */
			fYec0_idx = (fYec0_idx + fYec0_idx_save) & 63;
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec0[(i + fYec0_idx) & 63] = float(input0[i]) * fZec3[i];
			}
			/* Post code */
			fYec0_idx_save = vsize;
			/* Vectorizable loop 9 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec4[i] = fZec1[i] + 1.0f;
			}
			/* Vectorizable loop 10 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec6[i] = 1.0f / fZec5[i];
			}
			/* Vectorizable loop 11 */
			/* Pre code */
			fYec1_idx = (fYec1_idx + fYec1_idx_save) & 63;
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fYec1[(i + fYec1_idx) & 63] = float(input1[i]) * fZec3[i];
			}
			/* Post code */
			fYec1_idx_save = vsize;
			/* Recursive loop 12 */
			/* Pre code */
			fRec6_idx = (fRec6_idx + fRec6_idx_save) & 63;
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec6[(i + fRec6_idx) & 63] = -((fRec6[(i + fRec6_idx - 1) & 63] * fZec2[i] - (fYec0[(i + fYec0_idx) & 63] - fYec0[(i + fYec0_idx - 1) & 63]) / fZec0[i]) / fZec4[i]);
			}
			/* Post code */
			fRec6_idx_save = vsize;
			/* Vectorizable loop 13 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec7[i] = 1.0f - fZec6[i];
			}
			/* Vectorizable loop 14 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec8[i] = fZec6[i] + 1.0f;
			}
			/* Recursive loop 15 */
			/* Pre code */
			fRec12_idx = (fRec12_idx + fRec12_idx_save) & 63;
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec12[(i + fRec12_idx) & 63] = -((fZec2[i] * fRec12[(i + fRec12_idx - 1) & 63] - (fYec1[(i + fYec1_idx) & 63] - fYec1[(i + fYec1_idx - 1) & 63]) / fZec0[i]) / fZec4[i]);
			}
			/* Post code */
			fRec12_idx_save = vsize;
			/* Recursive loop 16 */
			/* Pre code */
			fRec9_idx = (fRec9_idx + fRec9_idx_save) & 63;
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec9[(i + fRec9_idx) & 63] = -((fRec9[(i + fRec9_idx - 1) & 63] * fZec7[i] - (fRec6[(i + fRec6_idx) & 63] - fRec6[(i + fRec6_idx - 1) & 63]) / fZec5[i]) / fZec8[i]);
			}
			/* Post code */
			fRec9_idx_save = vsize;
			/* Recursive loop 17 */
			/* Pre code */
			fRec11_idx = (fRec11_idx + fRec11_idx_save) & 63;
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec11[(i + fRec11_idx) & 63] = fSlow3 + fConst2 * fRec11[(i + fRec11_idx - 1) & 63];
			}
			/* Post code */
			fRec11_idx_save = vsize;
			/* Recursive loop 18 */
			/* Pre code */
			fRec13_idx = (fRec13_idx + fRec13_idx_save) & 63;
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec13[(i + fRec13_idx) & 63] = -((fZec7[i] * fRec13[(i + fRec13_idx - 1) & 63] - (fRec12[(i + fRec12_idx) & 63] - fRec12[(i + fRec12_idx - 1) & 63]) / fZec5[i]) / fZec8[i]);
			}
			/* Post code */
			fRec13_idx_save = vsize;
			/* Vectorizable loop 19 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec9[i] = std::max<float>(std::fabs(fRec6[(i + fRec6_idx) & 63] + 0.01f * fRec9[(i + fRec9_idx) & 63] * fRec11[(i + fRec11_idx) & 63]), std::fabs(fRec12[(i + fRec12_idx) & 63] + 0.01f * fRec11[(i + fRec11_idx) & 63] * fRec13[(i + fRec13_idx) & 63]));
			}
			/* Recursive loop 20 */
			/* Pre code */
			fRec5_idx = (fRec5_idx + fRec5_idx_save) & 63;
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec5[(i + fRec5_idx) & 63] = fRec5[(i + fRec5_idx - 1) & 63] + (fZec9[i] - fRec5[(i + fRec5_idx - 1) & 63]) * (1.0f - ((fZec9[i] > fRec5[(i + fRec5_idx - 1) & 63]) ? fConst5 : fConst4));
			}
			/* Post code */
			fRec5_idx_save = vsize;
			/* Recursive loop 21 */
			/* Pre code */
			fRec14_idx = (fRec14_idx + fRec14_idx_save) & 63;
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec14[(i + fRec14_idx) & 63] = fSlow4 + fConst2 * fRec14[(i + fRec14_idx - 1) & 63];
			}
			/* Post code */
			fRec14_idx_save = vsize;
			/* Vectorizable loop 22 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec10[i] = 2e+01f * std::log10(std::max<float>(fRec5[(i + fRec5_idx) & 63], 1e-30f)) + 0.3f * fRec14[(i + fRec14_idx) & 63];
			}
			/* Vectorizable loop 23 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec11[i] = fZec10[i] + 1e+01f;
			}
			/* Vectorizable loop 24 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec12[i] = fSlow6 * (fZec11[i] * float(fZec11[i] > fSlow8) + 0.5f * (float((fZec11[i] >= -fSlow8) * (fZec11[i] <= fSlow8)) * OptomotristDSP_faustpower2_f(fZec10[i] + fSlow8 + 1e+01f) / fSlow7));
			}
			/* Vectorizable loop 25 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				iZec13[i] = fZec12[i] < -0.5f;
			}
			/* Vectorizable loop 26 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec14[i] = std::max<float>(0.0001f, ((iZec13[i]) ? 1.0f : 2.0f));
			}
			/* Recursive loop 27 */
			/* Pre code */
			fRec15_idx = (fRec15_idx + fRec15_idx_save) & 63;
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec15[(i + fRec15_idx) & 63] = fSlow9 + fConst2 * fRec15[(i + fRec15_idx - 1) & 63];
			}
			/* Post code */
			fRec15_idx_save = vsize;
			/* Vectorizable loop 28 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec16[i] = 0.01f * fRec15[(i + fRec15_idx) & 63] + 0.5f;
			}
			/* Recursive loop 29 */
			/* Pre code */
			fRec19_idx = (fRec19_idx + fRec19_idx_save) & 63;
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec19[(i + fRec19_idx) & 63] = fSlow10 + fConst2 * fRec19[(i + fRec19_idx - 1) & 63];
			}
			/* Post code */
			fRec19_idx_save = vsize;
			/* Vectorizable loop 30 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				iZec15[i] = std::fabs(fZec14[i]) < 1.1920929e-07f;
			}
			/* Vectorizable loop 31 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec22[i] = std::pow(1e+01f, 0.05f * fRec19[(i + fRec19_idx) & 63]);
			}
			/* Recursive loop 32 */
			/* Pre code */
			fRec23_idx = (fRec23_idx + fRec23_idx_save) & 63;
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec23[(i + fRec23_idx) & 63] = fSlow11 + fConst2 * fRec23[(i + fRec23_idx - 1) & 63];
			}
			/* Post code */
			fRec23_idx_save = vsize;
			/* Recursive loop 33 */
			/* Pre code */
			fRec3_idx = (fRec3_idx + fRec3_idx_save) & 63;
			fRec4_idx = (fRec4_idx + fRec4_idx_save) & 63;
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec3[(i + fRec3_idx) & 63] = fRec3[(i + fRec3_idx - 1) & 63] + (float(iZec13[i]) - fRec3[(i + fRec3_idx - 1) & 63]) * (1.0f - ((iZec15[i]) ? 0.0f : std::exp(-(fConst6 / ((iZec15[i]) ? 1.0f : fZec14[i])))));
				fZec17[i] = 0.4f * fRec3[(i + fRec3_idx - 1) & 63];
				fZec18[i] = std::max<float>(0.0001f, ((fZec12[i] < fRec4[(i + fRec4_idx - 1) & 63]) ? 0.01f * fZec16[i] : fZec16[i] * ((fZec17[i] + 0.2f) * (1.2f * fRec3[(i + fRec3_idx - 1) & 63] + 0.3f) + 0.06f * (0.8f - fZec17[i]))));
				iZec19[i] = std::fabs(fZec18[i]) < 1.1920929e-07f;
				fRec4[(i + fRec4_idx) & 63] = fRec4[(i + fRec4_idx - 1) & 63] + (fZec12[i] - fRec4[(i + fRec4_idx - 1) & 63]) * (1.0f - ((iZec19[i]) ? 0.0f : std::exp(-(fConst6 / ((iZec19[i]) ? 1.0f : fZec18[i])))));
			}
			/* Post code */
			fRec3_idx_save = vsize;
			fRec4_idx_save = vsize;
			/* Recursive loop 34 */
			/* Pre code */
			fRec0_idx = (fRec0_idx + fRec0_idx_save) & 63;
			fRec16_idx = (fRec16_idx + fRec16_idx_save) & 63;
			fYec2_idx = (fYec2_idx + fYec2_idx_save) & 63;
			fRec18_idx = (fRec18_idx + fRec18_idx_save) & 63;
			fRec17_idx = (fRec17_idx + fRec17_idx_save) & 63;
			fRec20_idx = (fRec20_idx + fRec20_idx_save) & 63;
			fYec3_idx = (fYec3_idx + fYec3_idx_save) & 63;
			fRec22_idx = (fRec22_idx + fRec22_idx_save) & 63;
			fRec21_idx = (fRec21_idx + fRec21_idx_save) & 63;
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fHbargraph0 = FAUSTFLOAT(fRec4[(i + fRec4_idx) & 63]);
				fRec0[(i + fRec0_idx) & 63] = fHbargraph0;
				fRec16[(i + fRec16_idx) & 63] = fConst7 * fRec16[(i + fRec16_idx - 1) & 63] + fConst8 * fRec17[(i + fRec17_idx - 1) & 63];
				fZec20[i] = std::pow(1e+01f, 0.05f * fRec0[(i + fRec0_idx - 1) & 63]);
				fZec21[i] = fYec0[(i + fYec0_idx) & 63] * fZec20[i] - 0.3f * fRec16[(i + fRec16_idx - 1) & 63];
				fYec2[(i + fYec2_idx) & 63] = (((1.15f * fZec21[i]) >= 0.0f) ? 1.15f * (fZec21[i] / (0.69f * fZec21[i] + 1.0f)) : 1.15f * (fZec21[i] / (1.0f - 0.1725f * fZec21[i])));
				fRec18[(i + fRec18_idx) & 63] = 0.995f * fRec18[(i + fRec18_idx - 1) & 63] + 0.8695652f * (fYec2[(i + fYec2_idx) & 63] - fYec2[(i + fYec2_idx - 1) & 63]);
				fRec17[(i + fRec17_idx) & 63] = fRec18[(i + fRec18_idx) & 63];
				fRec1[i] = fRec17[(i + fRec17_idx) & 63] * fZec22[i];
				fRec20[(i + fRec20_idx) & 63] = fConst7 * fRec20[(i + fRec20_idx - 1) & 63] + fConst8 * fRec21[(i + fRec21_idx - 1) & 63];
				fZec23[i] = fYec1[(i + fYec1_idx) & 63] * fZec20[i] - 0.3f * fRec20[(i + fRec20_idx - 1) & 63];
				fYec3[(i + fYec3_idx) & 63] = (((1.15f * fZec23[i]) >= 0.0f) ? 1.15f * (fZec23[i] / (0.69f * fZec23[i] + 1.0f)) : 1.15f * (fZec23[i] / (1.0f - 0.1725f * fZec23[i])));
				fRec22[(i + fRec22_idx) & 63] = 0.995f * fRec22[(i + fRec22_idx - 1) & 63] + 0.8695652f * (fYec3[(i + fYec3_idx) & 63] - fYec3[(i + fYec3_idx - 1) & 63]);
				fRec21[(i + fRec21_idx) & 63] = fRec22[(i + fRec22_idx) & 63];
				fRec2[i] = fRec21[(i + fRec21_idx) & 63] * fZec22[i];
			}
			/* Post code */
			fYec3_idx_save = vsize;
			fRec22_idx_save = vsize;
			fRec20_idx_save = vsize;
			fRec21_idx_save = vsize;
			fYec2_idx_save = vsize;
			fRec18_idx_save = vsize;
			fRec16_idx_save = vsize;
			fRec17_idx_save = vsize;
			fRec0_idx_save = vsize;
			/* Vectorizable loop 35 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec24[i] = 1.0f - 0.01f * fRec23[(i + fRec23_idx) & 63];
			}
			/* Vectorizable loop 36 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				output0[i] = FAUSTFLOAT(0.01f * fRec1[i] * fRec23[(i + fRec23_idx) & 63] + float(input0[i]) * fZec24[i]);
			}
			/* Vectorizable loop 37 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				output1[i] = FAUSTFLOAT(0.01f * fRec23[(i + fRec23_idx) & 63] * fRec2[i] + float(input1[i]) * fZec24[i]);
			}
		}
	}

};

#ifdef FAUST_UIMACROS
	
	#define FAUST_FILE_NAME "optomotrist.dsp"
	#define FAUST_CLASS_NAME "OptomotristDSP"
	#define FAUST_COMPILATION_OPIONS "-lang cpp -ct 1 -cn OptomotristDSP -scn  -es 1 -mcd 0 -mdd 1024 -mdy 33 -uim -single -ftz 0 -vec -lv 1 -vs 32"
	#define FAUST_INPUTS 2
	#define FAUST_OUTPUTS 2
	#define FAUST_ACTIVES 9
	#define FAUST_PASSIVES 1

	FAUST_ADDHORIZONTALBARGRAPH("GR", fHbargraph0, -6e+01f, 0.0f);
	FAUST_ADDHORIZONTALSLIDER("Input Drive", fHslider1, 0.0f, -2e+01f, 2e+01f, 0.1f);
	FAUST_ADDHORIZONTALSLIDER("Peak Reduction", fHslider4, 5e+01f, 0.0f, 1e+02f, 0.1f);
	FAUST_ADDHORIZONTALSLIDER("Gain", fHslider6, 0.0f, -2e+01f, 4e+01f, 0.1f);
	FAUST_ADDHORIZONTALSLIDER("Mix", fHslider7, 1e+02f, 0.0f, 1e+02f, 0.1f);
	FAUST_ADDCHECKBOX("Limit/Compress", fCheckbox0);
	FAUST_ADDHORIZONTALSLIDER("SC Emphasis", fHslider3, 5e+01f, 0.0f, 1e+02f, 0.1f);
	FAUST_ADDHORIZONTALSLIDER("SC Emp Freq", fHslider2, 1e+03f, 2e+02f, 8e+03f, 1.0f);
	FAUST_ADDHORIZONTALSLIDER("SC HPF", fHslider0, 2e+01f, 2e+01f, 5e+02f, 1.0f);
	FAUST_ADDHORIZONTALSLIDER("T4 Bias", fHslider5, 5e+01f, 0.0f, 1e+02f, 0.1f);

	#define FAUST_LIST_ACTIVES(p) \
		p(HORIZONTALSLIDER, Input_Drive, "Input Drive", fHslider1, 0.0f, -2e+01f, 2e+01f, 0.1f) \
		p(HORIZONTALSLIDER, Peak_Reduction, "Peak Reduction", fHslider4, 5e+01f, 0.0f, 1e+02f, 0.1f) \
		p(HORIZONTALSLIDER, Gain, "Gain", fHslider6, 0.0f, -2e+01f, 4e+01f, 0.1f) \
		p(HORIZONTALSLIDER, Mix, "Mix", fHslider7, 1e+02f, 0.0f, 1e+02f, 0.1f) \
		p(CHECKBOX, Limit/Compress, "Limit/Compress", fCheckbox0, 0.0f, 0.0f, 1.0f, 1.0f) \
		p(HORIZONTALSLIDER, SC_Emphasis, "SC Emphasis", fHslider3, 5e+01f, 0.0f, 1e+02f, 0.1f) \
		p(HORIZONTALSLIDER, SC_Emp_Freq, "SC Emp Freq", fHslider2, 1e+03f, 2e+02f, 8e+03f, 1.0f) \
		p(HORIZONTALSLIDER, SC_HPF, "SC HPF", fHslider0, 2e+01f, 2e+01f, 5e+02f, 1.0f) \
		p(HORIZONTALSLIDER, T4_Bias, "T4 Bias", fHslider5, 5e+01f, 0.0f, 1e+02f, 0.1f) \

	#define FAUST_LIST_PASSIVES(p) \
		p(HORIZONTALBARGRAPH, GR, "GR", fHbargraph0, 0.0, -6e+01f, 0.0f, 0.0) \

#endif

#endif
