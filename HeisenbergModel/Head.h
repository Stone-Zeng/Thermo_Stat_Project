//Here are some switches and adjusted parameters for
//the program.
//TODO: Do not add functions here.
//TODO: Do not add .h files here.

#ifndef _HEAD_H_
#define _HEAD_H_
#pragma once

#define $LATTICE_LENGTH 20
#define $DATA_NUMBER 100
#define $LAST_10_PERCENT 1000 // 1/1000
#define $AVERAGE_NUMBER 10

#define NORMAL_RUN
#ifndef NORMAL_RUN
#define VECTOR_TEST_ON
//#define AMP_TEST_ON
#endif

#define INPUT_PARAMETERS_ON
#define FLIP_DATA_OUTPUT_ON
#define VECTOR_PLOT_OUTPUT_ON

//#define CPP11_RANDOM


//#include <iostream>
//#include <fstream>
//#include <iomanip>
//#include <vector>
//#include <random>
//#include <cstdlib>
//#include <ctime>

//#define CPP11_RANDOM
//#define OUTPUT_WIN_CSV
//#define OUTPUT_DATA
//#define DISPLAY_PROGRESS
//#define USING_ARG_STEP

//#define $FILENAME_CSV "output.csv"
//#define $FILENAME_DAT "output.dat"
//#define $FILENAME_DATA "data.dat"

//Parameters:
//#define X_LENGTH $LATTICE_LENGTH
//#define Y_LENGTH $LATTICE_LENGTH
//#define SIZE (X_LENGTH * Y_LENGTH * LENGTH_Z)
//#define STEP 1000000

//typedef bool Point;
//typedef std::vector<std::vector<std::vector<Point>>> LatticeData;
//typedef Point LatticeData[X_LENGTH][Y_LENGTH][LENGTH_Z];

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