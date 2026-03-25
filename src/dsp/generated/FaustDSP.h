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
	float fRec5[64];
	int fRec5_idx;
	int fRec5_idx_save;
	FAUSTFLOAT fHslider1;
	float fRec7[64];
	int fRec7_idx;
	int fRec7_idx_save;
	float fConst3;
	float fYec0[64];
	int fYec0_idx;
	int fYec0_idx_save;
	float fRec6[64];
	int fRec6_idx;
	int fRec6_idx_save;
	float fConst4;
	float fConst5;
	float fConst6;
	float fRec8[64];
	int fRec8_idx;
	int fRec8_idx_save;
	FAUSTFLOAT fHslider2;
	float fRec9[64];
	int fRec9_idx;
	int fRec9_idx_save;
	float fConst7;
	float fRec3[64];
	int fRec3_idx;
	int fRec3_idx_save;
	FAUSTFLOAT fHslider3;
	float fRec10[64];
	int fRec10_idx;
	int fRec10_idx_save;
	float fRec4[64];
	int fRec4_idx;
	int fRec4_idx_save;
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT fHbargraph0;
	float fRec0[64];
	int fRec0_idx;
	int fRec0_idx_save;
	float fYec1[64];
	int fYec1_idx;
	int fYec1_idx_save;
	float fRec11[64];
	int fRec11_idx;
	int fRec11_idx_save;
	FAUSTFLOAT fHslider4;
	float fRec12[64];
	int fRec12_idx;
	int fRec12_idx_save;
	float fYec2[64];
	int fYec2_idx;
	int fYec2_idx_save;
	float fRec13[64];
	int fRec13_idx;
	int fRec13_idx_save;
	
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
		m->declare("filters.lib/lowpass0_highpass1", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
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
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		fConst0 = std::min<float>(1.92e+05f, std::max<float>(1.0f, float(fSampleRate)));
		fConst1 = 44.1f / fConst0;
		fConst2 = 1.0f - fConst1;
		fConst3 = 3.1415927f / fConst0;
		fConst4 = 1.0f / std::tan(3141.5928f / fConst0);
		fConst5 = 1.0f / (fConst4 + 1.0f);
		fConst6 = 1.0f - fConst4;
		fConst7 = 1.0f / fConst0;
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(5e+01f);
		fHslider1 = FAUSTFLOAT(2e+01f);
		fHslider2 = FAUSTFLOAT(5e+01f);
		fHslider3 = FAUSTFLOAT(5e+01f);
		fCheckbox0 = FAUSTFLOAT(0.0f);
		fHslider4 = FAUSTFLOAT(0.0f);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 64; l0 = l0 + 1) {
			fRec5[l0] = 0.0f;
		}
		fRec5_idx = 0;
		fRec5_idx_save = 0;
		for (int l1 = 0; l1 < 64; l1 = l1 + 1) {
			fRec7[l1] = 0.0f;
		}
		fRec7_idx = 0;
		fRec7_idx_save = 0;
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
			fRec8[l4] = 0.0f;
		}
		fRec8_idx = 0;
		fRec8_idx_save = 0;
		for (int l5 = 0; l5 < 64; l5 = l5 + 1) {
			fRec9[l5] = 0.0f;
		}
		fRec9_idx = 0;
		fRec9_idx_save = 0;
		for (int l6 = 0; l6 < 64; l6 = l6 + 1) {
			fRec3[l6] = 0.0f;
		}
		fRec3_idx = 0;
		fRec3_idx_save = 0;
		for (int l7 = 0; l7 < 64; l7 = l7 + 1) {
			fRec10[l7] = 0.0f;
		}
		fRec10_idx = 0;
		fRec10_idx_save = 0;
		for (int l8 = 0; l8 < 64; l8 = l8 + 1) {
			fRec4[l8] = 0.0f;
		}
		fRec4_idx = 0;
		fRec4_idx_save = 0;
		for (int l9 = 0; l9 < 64; l9 = l9 + 1) {
			fRec0[l9] = 0.0f;
		}
		fRec0_idx = 0;
		fRec0_idx_save = 0;
		for (int l10 = 0; l10 < 64; l10 = l10 + 1) {
			fYec1[l10] = 0.0f;
		}
		fYec1_idx = 0;
		fYec1_idx_save = 0;
		for (int l11 = 0; l11 < 64; l11 = l11 + 1) {
			fRec11[l11] = 0.0f;
		}
		fRec11_idx = 0;
		fRec11_idx_save = 0;
		for (int l12 = 0; l12 < 64; l12 = l12 + 1) {
			fRec12[l12] = 0.0f;
		}
		fRec12_idx = 0;
		fRec12_idx_save = 0;
		for (int l13 = 0; l13 < 64; l13 = l13 + 1) {
			fYec2[l13] = 0.0f;
		}
		fYec2_idx = 0;
		fYec2_idx_save = 0;
		for (int l14 = 0; l14 < 64; l14 = l14 + 1) {
			fRec13[l14] = 0.0f;
		}
		fRec13_idx = 0;
		fRec13_idx_save = 0;
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
		ui_interface->declare(&fHslider0, "1", "");
		ui_interface->declare(&fHslider0, "id", "peak_reduction");
		ui_interface->addHorizontalSlider("Peak Reduction", &fHslider0, FAUSTFLOAT(5e+01f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1e+02f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fHslider4, "2", "");
		ui_interface->declare(&fHslider4, "id", "gain");
		ui_interface->addHorizontalSlider("Gain", &fHslider4, FAUSTFLOAT(0.0f), FAUSTFLOAT(-2e+01f), FAUSTFLOAT(4e+01f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fCheckbox0, "3", "");
		ui_interface->declare(&fCheckbox0, "id", "limit_mode");
		ui_interface->addCheckButton("Limit/Compress", &fCheckbox0);
		ui_interface->declare(&fHslider2, "4", "");
		ui_interface->declare(&fHslider2, "id", "sc_emphasis");
		ui_interface->addHorizontalSlider("SC Emphasis", &fHslider2, FAUSTFLOAT(5e+01f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1e+02f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fHslider1, "5", "");
		ui_interface->declare(&fHslider1, "id", "sc_hpf");
		ui_interface->addHorizontalSlider("SC HPF", &fHslider1, FAUSTFLOAT(2e+01f), FAUSTFLOAT(2e+01f), FAUSTFLOAT(5e+02f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider3, "6", "");
		ui_interface->declare(&fHslider3, "id", "t4_bias");
		ui_interface->addHorizontalSlider("T4 Bias", &fHslider3, FAUSTFLOAT(5e+01f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1e+02f), FAUSTFLOAT(0.1f));
		ui_interface->declare(&fHbargraph0, "7", "");
		ui_interface->declare(&fHbargraph0, "id", "gr_meter");
		ui_interface->addHorizontalBargraph("GR", &fHbargraph0, FAUSTFLOAT(-2e+01f), FAUSTFLOAT(0.0f));
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
		int iZec6[32];
		float fZec7[32];
		int iZec8[32];
		float fSlow3 = fConst1 * float(fHslider3);
		float fZec9[32];
		float fZec10[32];
		float fZec11[32];
		int iZec12[32];
		int iSlow4 = int(float(fCheckbox0));
		float fSlow5 = 1.0f / ((iSlow4) ? 1e+02f : 3.5f) + -1.0f;
		float fZec13[32];
		float fZec14[32];
		float fSlow6 = ((iSlow4) ? 6.0f : 2e+01f);
		float fSlow7 = 0.5f * fSlow6;
		float fZec15[32];
		float fSlow8 = fConst1 * float(fHslider4);
		float fZec16[32];
		float fRec1[32];
		float fZec17[32];
		float fRec2[32];
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
				fRec7[(i + fRec7_idx) & 63] = fSlow1 + fConst2 * fRec7[(i + fRec7_idx - 1) & 63];
			}
			/* Post code */
			fRec7_idx_save = vsize;
			/* Recursive loop 1 */
			/* Pre code */
			fRec12_idx = (fRec12_idx + fRec12_idx_save) & 63;
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec12[(i + fRec12_idx) & 63] = fSlow8 + fConst2 * fRec12[(i + fRec12_idx - 1) & 63];
			}
			/* Post code */
			fRec12_idx_save = vsize;
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
				fRec10[(i + fRec10_idx) & 63] = fSlow3 + fConst2 * fRec10[(i + fRec10_idx - 1) & 63];
			}
			/* Post code */
			fRec10_idx_save = vsize;
			/* Vectorizable loop 4 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec16[i] = std::pow(1e+01f, 0.05f * fRec12[(i + fRec12_idx) & 63]);
			}
			/* Vectorizable loop 5 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec1[i] = 1.0f / fZec0[i];
			}
			/* Recursive loop 6 */
			/* Pre code */
			fRec9_idx = (fRec9_idx + fRec9_idx_save) & 63;
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec9[(i + fRec9_idx) & 63] = fSlow2 + fConst2 * fRec9[(i + fRec9_idx - 1) & 63];
			}
			/* Post code */
			fRec9_idx_save = vsize;
			/* Vectorizable loop 7 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec9[i] = 0.01f * fRec10[(i + fRec10_idx) & 63] + 0.5f;
			}
			/* Recursive loop 8 */
			/* Pre code */
			fRec5_idx = (fRec5_idx + fRec5_idx_save) & 63;
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fRec5[(i + fRec5_idx) & 63] = fSlow0 + fConst2 * fRec5[(i + fRec5_idx - 1) & 63];
			}
			/* Post code */
			fRec5_idx_save = vsize;
			/* Recursive loop 9 */
			/* Pre code */
			fYec0_idx = (fYec0_idx + fYec0_idx_save) & 63;
			fRec6_idx = (fRec6_idx + fRec6_idx_save) & 63;
			fRec8_idx = (fRec8_idx + fRec8_idx_save) & 63;
			fRec3_idx = (fRec3_idx + fRec3_idx_save) & 63;
			fRec4_idx = (fRec4_idx + fRec4_idx_save) & 63;
			fRec0_idx = (fRec0_idx + fRec0_idx_save) & 63;
			fYec1_idx = (fYec1_idx + fYec1_idx_save) & 63;
			fRec11_idx = (fRec11_idx + fRec11_idx_save) & 63;
			fYec2_idx = (fYec2_idx + fYec2_idx_save) & 63;
			fRec13_idx = (fRec13_idx + fRec13_idx_save) & 63;
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				fZec2[i] = std::pow(1e+01f, 0.05f * fRec0[(i + fRec0_idx - 1) & 63]);
				fZec3[i] = float(input0[i]) * fZec2[i];
				fZec4[i] = float(input1[i]) * fZec2[i];
				fYec0[(i + fYec0_idx) & 63] = std::max<float>(std::fabs(fZec3[i]), std::fabs(fZec4[i]));
				fRec6[(i + fRec6_idx) & 63] = -((fRec6[(i + fRec6_idx - 1) & 63] * (1.0f - fZec1[i]) - (fYec0[(i + fYec0_idx) & 63] - fYec0[(i + fYec0_idx - 1) & 63]) / fZec0[i]) / (fZec1[i] + 1.0f));
				fRec8[(i + fRec8_idx) & 63] = -(fConst5 * (fConst6 * fRec8[(i + fRec8_idx - 1) & 63] - fConst4 * (fRec6[(i + fRec6_idx) & 63] - fRec6[(i + fRec6_idx - 1) & 63])));
				fZec5[i] = 0.04f * fRec5[(i + fRec5_idx) & 63] * std::fabs(fRec6[(i + fRec6_idx) & 63] + 0.01f * fRec8[(i + fRec8_idx) & 63] * fRec9[(i + fRec9_idx) & 63]);
				iZec6[i] = fZec5[i] > 0.001f;
				fZec7[i] = std::max<float>(0.0001f, ((iZec6[i]) ? 2.0f : 1e+01f));
				iZec8[i] = std::fabs(fZec7[i]) < 1.1920929e-07f;
				fRec3[(i + fRec3_idx) & 63] = fRec3[(i + fRec3_idx - 1) & 63] + (float(iZec6[i]) - fRec3[(i + fRec3_idx - 1) & 63]) * (1.0f - ((iZec8[i]) ? 0.0f : std::exp(-(fConst7 / ((iZec8[i]) ? 1.0f : fZec7[i])))));
				fZec10[i] = 0.55f * fRec3[(i + fRec3_idx - 1) & 63];
				fZec11[i] = std::max<float>(0.0001f, ((fZec5[i] > fRec4[(i + fRec4_idx - 1) & 63]) ? 0.01f * fZec9[i] : fZec9[i] * ((fZec10[i] + 0.3f) * (4.5f * fRec3[(i + fRec3_idx - 1) & 63] + 0.5f) + 0.06f * (0.7f - fZec10[i]))));
				iZec12[i] = std::fabs(fZec11[i]) < 1.1920929e-07f;
				fRec4[(i + fRec4_idx) & 63] = fRec4[(i + fRec4_idx - 1) & 63] + (fZec5[i] - fRec4[(i + fRec4_idx - 1) & 63]) * (1.0f - ((iZec12[i]) ? 0.0f : std::exp(-(fConst7 / ((iZec12[i]) ? 1.0f : fZec11[i])))));
				fZec13[i] = std::log10(std::max<float>(std::max<float>(fRec4[(i + fRec4_idx) & 63], 1e-30f), 1e-30f)) + 1.0f;
				fZec14[i] = 2e+01f * fZec13[i];
				fHbargraph0 = FAUSTFLOAT(fSlow5 * (0.5f * (float((fZec14[i] >= -fSlow7) * (fZec14[i] <= fSlow7)) * OptomotristDSP_faustpower2_f(fZec14[i] + fSlow7) / fSlow6) + 2e+01f * fZec13[i] * float(fZec14[i] > fSlow7)));
				fRec0[(i + fRec0_idx) & 63] = fHbargraph0;
				fZec15[i] = std::exp(2.0f * (1.5f * fZec3[i] + 0.1f));
				fYec1[(i + fYec1_idx) & 63] = (fZec15[i] + -1.0f) / (fZec15[i] + 1.0f) + -0.099667996f;
				fRec11[(i + fRec11_idx) & 63] = 0.995f * fRec11[(i + fRec11_idx - 1) & 63] + 0.6666667f * (fYec1[(i + fYec1_idx) & 63] - fYec1[(i + fYec1_idx - 1) & 63]);
				fRec1[i] = fRec11[(i + fRec11_idx) & 63] * fZec16[i];
				fZec17[i] = std::exp(2.0f * (1.5f * fZec4[i] + 0.1f));
				fYec2[(i + fYec2_idx) & 63] = (fZec17[i] + -1.0f) / (fZec17[i] + 1.0f) + -0.099667996f;
				fRec13[(i + fRec13_idx) & 63] = 0.995f * fRec13[(i + fRec13_idx - 1) & 63] + 0.6666667f * (fYec2[(i + fYec2_idx) & 63] - fYec2[(i + fYec2_idx - 1) & 63]);
				fRec2[i] = fRec13[(i + fRec13_idx) & 63] * fZec16[i];
			}
			/* Post code */
			fYec2_idx_save = vsize;
			fRec13_idx_save = vsize;
			fYec1_idx_save = vsize;
			fRec11_idx_save = vsize;
			fRec8_idx_save = vsize;
			fYec0_idx_save = vsize;
			fRec6_idx_save = vsize;
			fRec3_idx_save = vsize;
			fRec4_idx_save = vsize;
			fRec0_idx_save = vsize;
			/* Vectorizable loop 10 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				output1[i] = FAUSTFLOAT(fRec2[i]);
			}
			/* Vectorizable loop 11 */
			/* Compute code */
			for (int i = 0; i < vsize; i = i + 1) {
				output0[i] = FAUSTFLOAT(fRec1[i]);
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
	#define FAUST_ACTIVES 6
	#define FAUST_PASSIVES 1

	FAUST_ADDHORIZONTALSLIDER("Peak Reduction", fHslider0, 5e+01f, 0.0f, 1e+02f, 0.1f);
	FAUST_ADDHORIZONTALSLIDER("Gain", fHslider4, 0.0f, -2e+01f, 4e+01f, 0.1f);
	FAUST_ADDCHECKBOX("Limit/Compress", fCheckbox0);
	FAUST_ADDHORIZONTALSLIDER("SC Emphasis", fHslider2, 5e+01f, 0.0f, 1e+02f, 0.1f);
	FAUST_ADDHORIZONTALSLIDER("SC HPF", fHslider1, 2e+01f, 2e+01f, 5e+02f, 1.0f);
	FAUST_ADDHORIZONTALSLIDER("T4 Bias", fHslider3, 5e+01f, 0.0f, 1e+02f, 0.1f);
	FAUST_ADDHORIZONTALBARGRAPH("GR", fHbargraph0, -2e+01f, 0.0f);

	#define FAUST_LIST_ACTIVES(p) \
		p(HORIZONTALSLIDER, Peak_Reduction, "Peak Reduction", fHslider0, 5e+01f, 0.0f, 1e+02f, 0.1f) \
		p(HORIZONTALSLIDER, Gain, "Gain", fHslider4, 0.0f, -2e+01f, 4e+01f, 0.1f) \
		p(CHECKBOX, Limit/Compress, "Limit/Compress", fCheckbox0, 0.0f, 0.0f, 1.0f, 1.0f) \
		p(HORIZONTALSLIDER, SC_Emphasis, "SC Emphasis", fHslider2, 5e+01f, 0.0f, 1e+02f, 0.1f) \
		p(HORIZONTALSLIDER, SC_HPF, "SC HPF", fHslider1, 2e+01f, 2e+01f, 5e+02f, 1.0f) \
		p(HORIZONTALSLIDER, T4_Bias, "T4 Bias", fHslider3, 5e+01f, 0.0f, 1e+02f, 0.1f) \

	#define FAUST_LIST_PASSIVES(p) \
		p(HORIZONTALBARGRAPH, GR, "GR", fHbargraph0, 0.0, -2e+01f, 0.0f, 0.0) \

#endif

#endif
