//This is the class for 2D Heisenberg model lattice.

#ifndef _MYLATTICE_H_
#define _MYLATTICE_H_
#pragma once

#include "Head.h"
#include "MyVector.h"
#include "Physics.h"

#define X_LENGTH $LATTICE_LENGTH
#define Y_LENGTH $LATTICE_LENGTH
//#define SIZE (X_LENGTH * Y_LENGTH)

typedef MyVector Point;
typedef Point LatticeData[X_LENGTH][Y_LENGTH];

class MyLattice
{
	inline int x_minus_1(const int&);
	inline int x_plus_1(const int&);
	inline int y_minus_1(const int&);
	inline int y_plus_1(const int&);

	inline double energyCount(const Point& p, const int& i, const int& j, const double& hamiltonian_J, const double& magnetic_B, const double& hamiltonian_D);

public:
	MyLattice(const double& hamiltonian_J, const double& magnetic_B, const double& hamiltonian_D);

	LatticeData data;

	void flipOnePoint(const double& temperature, const double& hamiltonian_J, const double& magnetic_B, const double& hamiltonian_D);
	Physics physicalQuantity;

	//void outputData(std::ofstream&);

	double calculateEnergy(const double& hamiltonian_J, const double& magnetic_B, const double& hamiltonian_D);
	//double calculateHeatCapacity();
	//double calculateMagneticSusceptibility();
};

#endif