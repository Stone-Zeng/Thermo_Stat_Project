//Here are some simple functions:
//	randomInt
//	randomReal
//	possibilityOfFlip
//	doubleToString

#ifndef _FUNCTION_H_
#define _FUNCTION_H_
#pragma once

#include "Head.h"

#ifdef CPP11_RANDOM
#include <random>
#endif
#include <string>
#include <cstdlib>
#include <cmath>

static unsigned int randSeed = 100; 

inline int randomInt(const int& min, const int& max)
{
#ifdef CPP11_RANDOM
	std::random_device rd;
	std::uniform_int_distribution<> dist(min, max);
	std::mt19937 gen(rd());
	return dist(gen);
#else
	return rand_r(&randSeed) % (max - min + 1) + min;
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
	auto r = 0.0001 * (double) ((rand_r(&randSeed) * rand_r(&randSeed)) % 10000);
	////Fast:
	//auto r = 0.001 * (double) (rand_r(&randSeed) % 1000);
	return (max - min) * r + min;
#endif
}

inline double possibilityOfFlip(const double& dE, const double& temperature)
{
	return ((dE > 0.0) ? exp(-dE / temperature) : 1);
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

#endif
