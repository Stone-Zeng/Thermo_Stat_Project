//Here are some simple functions:
//	randomInt
//	randomReal

#ifndef _FUNCTION_H_
#define _FUNCTION_H_
#pragma once

//#define CPP11_RANDOM

#include <random> //For C++11 random
#include <cstdlib>

inline int randomInt(const int& min, const int& max)
{
#ifdef CPP11_RANDOM
	std::random_device rd;
	std::uniform_int_distribution<> dist(min, max);
	std::mt19937 gen(rd());
	return dist(gen);
#else
	return rand() % (max - min + 1) + min;
#endif
}

inline double randomReal(const double& min, const double& max)
{
#ifdef CPP11_RANDOM
	std::random_device rd;
	std::uniform_real_distribution<> dist(min, max);
	std::mt19937 gen(rd());
	return dist(gen);
#else
	auto r = 0.0001 * (double) ((rand() * rand()) % 10000);
	return (max - min) * r + min;
#endif
}

inline double possibilityOfFlip(const double& dE, const double& temperature)
{
	return ((dE > 0.0) ? exp(-dE / temperature) : 1);
}

#endif