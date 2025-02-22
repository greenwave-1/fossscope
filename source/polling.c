//
// Created on 2/21/25.
//

#include "polling.h"
#include <ogc/video.h>
#include <ogc/video_types.h>
#include <ogc/si.h>

#ifdef DEBUG
#include "gecko.h"
#endif

static bool unsupportedMode = false;
static bool firstRun = true;
static int xLineCountNormal = 0;
static int xLineCountHigh = 0;
static int pollsPerFrameNormal = 2;
static int pollsPerFrameHigh = 24;

// set xLineCount based on video mode
void __setStaticXYValues() {
	switch(VIDEO_GetScanMode()) {
		case VI_INTERLACE:
			xLineCountNormal = 120;
			xLineCountHigh = 11;
#ifdef DEBUG
			sendMessage("Video scan mode is interlaced", 100);
#endif
			break;
		case VI_PROGRESSIVE:
			xLineCountNormal = 240;
			xLineCountHigh = 22;
#ifdef DEBUG
			sendMessage("Video scan mode is progressive", 100);
#endif
			break;
		case VI_NON_INTERLACE:
		default:
			xLineCountNormal = 240;
			xLineCountHigh = 240;
			unsupportedMode = true;
#ifdef DEBUG
			sendMessage("Video scan mode is unsupported", 100);
#endif
	}
	firstRun = false;
}

void setSamplingRateHigh() {
	if (firstRun) {
		__setStaticXYValues();
	}
	SI_SetXY(xLineCountHigh, pollsPerFrameHigh);
}

void setSamplingRateNormal() {
	if (firstRun) {
		__setStaticXYValues();
	}
	SI_SetXY(xLineCountNormal, pollsPerFrameNormal);
}

bool isUnsupportedMode() {
	return unsupportedMode;
}
