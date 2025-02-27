//
// Created on 10/30/23.
//

#ifndef FOSSSCOPE_WAVEFORM_H
#define FOSSSCOPE_WAVEFORM_H

#include <gccore.h>

#define WAVEFORM_SAMPLES 3000
// individual datapoint from polling
typedef struct WaveformDatapoint {
	// analog stick
	int ax;
	int ay;
	// c stick
	int cx;
	int cy;
	// time from last datapoint
	u64 timeDiffUs;
	// for converted values
	bool isAXNegative;
	bool isAYNegative;
	bool isCXNegative;
	bool isCYNegative;
} WaveformDatapoint;

typedef struct WaveformData {
	// sampling a 1ms
	WaveformDatapoint data[WAVEFORM_SAMPLES];
	unsigned int endPoint;

	// total time the read took
	u64 totalTimeUs;
	
	bool isDataReady;
	
	// set to true for logic to ignore stick movement stuff and just fill the array
	bool fullMeasure;

} WaveformData;

void measureWaveform(WaveformData *data);

// converts raw input values to melee coordinates
WaveformDatapoint convertStickValues(WaveformDatapoint *data);

// drawing functions from phobconfigtool
void DrawHLine (int x1, int x2, int y, int color, void *xfb);
void DrawVLine (int x, int y1, int y2, int color, void *xfb);
void DrawBox (int x1, int y1, int x2, int y2, int color, void *xfb);

// expanded drawing functions
void DrawFilledBox (int x1, int y1, int x2, int y2, int color, void *xfb);
void DrawLine (int x1, int y1, int x2, int y2, int color, void *xfb);
void DrawDot (int x, int y, int color, void *xfb);
void DrawCircle (int cx, int cy, int r, int color, void *xfb);
void DrawFilledCircle(int cx, int cy, int r, int interval, int color, void *xfb);

#endif //FOSSSCOPE_WAVEFORM_H
