//This is the class for timing.
//For Windows only.

#ifndef _MYTIMING_H_
#define _MYTIMING_H_
#pragma once

#include "Head.h"

#ifdef WIN_TIMING
#include <Windows.h>
#endif
#ifdef GNU_TIMING
#include <sys/time.h>
#endif

//#define GNU_TIMING
class MyTiming
{
#ifdef WIN_TIMING
	LARGE_INTEGER m_nFreq;
	LARGE_INTEGER BeginTime;
	LARGE_INTEGER EndTime;
#endif
#ifdef GNU_TIMING
	struct timeval tpstart, tpend;
	double timeuse;
#endif

public:
	MyTiming();
	void timingStart();
	void timingEnd();
	double runTime();
	double runTime_ms();
};
#endif