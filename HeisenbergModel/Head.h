//Here are some switches and adjusted parameters for
//the program.
//Try no to add functions here!

#ifndef _HEAD_H_
#define _HEAD_H_
#pragma once

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <random>
#include <cstdlib>
#include <ctime>

//#define CPP11_RANDOM
//#define OUTPUT_WIN_CSV
//#define OUTPUT_DATA
#define DISPLAY_PROGRESS
//#define USING_ARG_STEP

#define $LATTICE_LENGTH 100
#define $DATA_NUMBER 10000
#define $LAST_10_PERCENT 1000 //1/1000
#define $DISPLAY_NUMBER 10
#define $FILENAME_CSV "output.csv"
#define $FILENAME_DAT "output.dat"
#define $FILENAME_DATA "data.dat"

//Parameters:
//#define X_LENGTH $LATTICE_LENGTH
//#define Y_LENGTH $LATTICE_LENGTH
//#define SIZE (X_LENGTH * Y_LENGTH * LENGTH_Z)
#define STEP 1000000

//typedef bool Point;
//typedef std::vector<std::vector<std::vector<Point>>> LatticeData;
//typedef Point LatticeData[X_LENGTH][Y_LENGTH][LENGTH_Z];

//inline int randomInt(const int& min, const int& max)
//{
//#ifdef CPP11_RANDOM
//	random_device rd;
//	uniform_int_distribution<> dist(min, max);
//	mt19937 gen(rd());
//	return dist(gen);
//#else
//	return rand() % (max - min + 1) + min;
//#endif
//}
//
//inline double randomReal(const double& min, const double& max)
//{
//#ifdef CPP11_RANDOM
//	random_device rd;
//	uniform_real_distribution<> dist(min, max);
//	mt19937 gen(rd());
//	return dist(gen);
//#else
//	auto r = 0.0001 * (double) ((rand() * rand()) % 10000);
//	return (max - min) * r + min;
//#endif
//}

//inline int energyBetween(const Point& p1, const Point& p2)
//{
//	return ((p1 == p2) ? -1 : 1);
//}
//
//inline double possibilityOfFlip(const int& dE, const double& temperature)
//{
//	return ((dE > 0) ? exp(-dE / temperature) : 1);
//}

//inline void output(std::ofstream& file, const int& index, const int& E, const int& M)
//{
//	file << index << "," << E << "," << M << std::endl;
//}

#endif