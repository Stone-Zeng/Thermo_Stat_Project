//This is the class for one complete flip at one temperature.

#ifndef _SINGLELATTICE_H_
#define _SINGLELATTICE_H_
#pragma once

#include <array>
#include <iostream>
#include "MyLattice.h"
#include "Physics.h"

typedef std::array<Physics, $DATA_NUMBER> PhysicsData;

class SingleLattice
{
public:
	MyLattice lattice;
	Physics result;
	PhysicsData flipData;

	void completeFlip(const int& step, const double& temperature);
	void output(std::ostream& out_Result, const int& step, const double& temperature);
};

#endif