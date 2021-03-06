#include "MyTiming.h"

MyTiming::MyTiming()
{
#ifdef WIN_TIMING
	QueryPerformanceFrequency(&m_nFreq);
#endif
}

void MyTiming::timingStart()
{
#ifdef WIN_TIMING
	QueryPerformanceCounter(&BeginTime);
#endif
#ifdef GNU_TIMING
	gettimeofday(&tpstart, NULL);
#endif
}

void MyTiming::timingEnd()
{
#ifdef WIN_TIMING
	QueryPerformanceCounter(&EndTime);
#endif
#ifdef GNU_TIMING
	gettimeofday(&tpend, NULL);
#endif
}

double MyTiming::runTime()
{
#ifdef WIN_TIMING
	return (double) (EndTime.QuadPart - BeginTime.QuadPart) / m_nFreq.QuadPart;
#endif
#ifdef GNU_TIMING
	return (double) (tpend.tv_sec - tpstart.tv_sec) + tpend.tv_usec - tpstart.tv_usec;
#endif
}

double MyTiming::runTime_ms()
{
#ifdef WIN_TIMING
	return (double) 1000 * (EndTime.QuadPart - BeginTime.QuadPart) / m_nFreq.QuadPart;
#endif
#ifdef GNU_TIMING
	return (double) 1000 * (tpend.tv_sec - tpstart.tv_sec) + tpend.tv_usec - tpstart.tv_usec;
#endif
}