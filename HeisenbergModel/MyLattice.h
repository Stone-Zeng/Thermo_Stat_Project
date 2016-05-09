//This is the class for 2D Heisenberg model lattice.

#ifndef _MYLATTICE_H_
#define _MYLATTICE_H_
#pragma once

#include "Head.h"
#include "MyVector.h"

#define X_LENGTH $LATTICE_LENGTH
#define Y_LENGTH $LATTICE_LENGTH
//#define SIZE (X_LENGTH * Y_LENGTH)

typedef MyVector Point;
typedef Point LatticeData[X_LENGTH][Y_LENGTH];

class MyLattice
{
	LatticeData data;
	inline int x_minus_1(const int&);
	inline int x_plus_1(const int&);
	inline int y_minus_1(const int&);
	inline int y_plus_1(const int&);

	inline double energyCount(const Point&, const int&, const int&);
	//inline double energyOfChange(const int&, const int&, const int&);

public:
	MyLattice();

	//int->double
	double totalEnergy;
	int totalMagneticDipole;
	void flipOnePoint(const double&);
	//void outputData(std::ofstream&);

	double calculateHeatCapacity();
	double calculateMagneticSusceptibility();
};

#endif