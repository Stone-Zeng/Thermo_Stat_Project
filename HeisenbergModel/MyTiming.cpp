#include "MyTiming.h"

MyTiming::MyTiming()
{
	QueryPerformanceFrequency(&m_nFreq);
}

void MyTiming::timingStart()
{
	QueryPerformanceCounter(&m_nBeginTime);
}

void MyTiming::timingEnd()
{
	QueryPerformanceCounter(&nEndTime);
}

double MyTiming::runTime()
{
	return (double) (nEndTime.QuadPart - m_nBeginTime.QuadPart) / m_nFreq.QuadPart;
}

double MyTiming::runTime_ms()
{
	return (double) 1000 * (nEndTime.QuadPart - m_nBeginTime.QuadPart) / m_nFreq.QuadPart;
}
