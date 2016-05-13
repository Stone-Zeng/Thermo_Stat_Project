//This is the class for timing.
//For Windows only.

#ifndef _MYTIMING_H_
#define _MYTIMING_H_
#pragma once

#include <Windows.h>

class MyTiming
{
	LARGE_INTEGER m_nFreq;
	LARGE_INTEGER m_nBeginTime;
	LARGE_INTEGER nEndTime;

public:
	MyTiming();
	void timingStart();
	void timingEnd();
	double runTime();
	double runTime_ms();
};

#endif