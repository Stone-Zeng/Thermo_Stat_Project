//Here are some simple functions:
//  fastrand
//	randomInt, randomReal
//	doubleToString
//	possibilityOfFlip

#ifndef _FUNCTION_H_
#define _FUNCTION_H_
#pragma once

#include "Head.h"

#ifdef CPP11_RANDOM
#include <random>
#endif
#include <string>
#include <cstdlib>
#include <ctime>

static unsigned int g_seed = (unsigned int) time(NULL);

inline unsigned int fastrand()
{
	g_seed = (214013 * g_seed + 2531011);
	return (g_seed >> 16) & 0x7FFF;
}

inline int randomInt(const int& min, const int& max)
{
#ifdef CPP11_RANDOM
	std::random_device rd;
	std::uniform_int_distribution<> dist(min, max);
	std::mt19937 gen(rd());
	return dist(gen);
#else
	return fastrand() % (max - min + 1) + min;
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
	auto r = 0.0001 * (double) ((fastrand() * fastrand()) % 10000);
	return (max - min) * r + min;
#endif
}

inline std::string doubleToString(const double& x)
{
	auto s = std::to_string(x);
	auto i = s.find_last_of(".123456789");
	s.erase(i + 1);

	if (s[s.length() - 1] == '.')
		--i;
	return s.substr(0, i + 1);
}

inline double possibilityOfFlip(const double& dE, const double& temperature)
{
	return ((dE > 0.0) ? exp(-dE / temperature) : 1);
}

#endif