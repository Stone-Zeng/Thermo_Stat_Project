//This is the class for 2D Heisenberg model lattice.

#ifndef MYLATTICE_H_
#define MYLATTICE_H_
#pragma once

#include "Head.h"
#include "Function.h"
#include "MyVector.h"

#define LENGTH_X $LATTICE_LENGTH
#define LENGTH_Y $LATTICE_LENGTH
#define SIZE (LENGTH_X * LENGTH_Y)

typedef MyVector Point;
typedef Point LatticeData[LENGTH_X][LENGTH_Y];

class MyLattice
{
	LatticeData data;
	inline int x_minus_1(const int&);
	inline int x_plus_1(const int&);
	inline int y_minus_1(const int&);
	inline int y_plus_1(const int&);

	inline int energyCount(const Point&, const int&, const int&, const int&);
	inline int energyOfChange(const int&, const int&, const int&);

public:
	MyLattice(const int&, const int&, const int&);

	int totalEnergy;
	int totalMagneticDipole;
	void flipOnePoint(const double&);
	//void outputData(std::ofstream&);

	double calculateHeatCapacity();
	double calculateMagneticSusceptibility();
};

#endif