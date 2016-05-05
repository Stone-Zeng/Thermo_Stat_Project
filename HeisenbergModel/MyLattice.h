#ifndef MYLATTICE_H_
#define MYLATTICE_H_
#pragma once

#include "Head.h"

class MyLattice
{
	int x_Length;
	int y_Length;
	int z_Length;
	
	LatticeData data;
	inline int x_minus_1(const int&);
	inline int x_plus_1(const int&);
	inline int y_minus_1(const int&);
	inline int y_plus_1(const int&);
	inline int z_minus_1(const int&);
	inline int z_plus_1(const int&);

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