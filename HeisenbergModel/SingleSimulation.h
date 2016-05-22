//This is the class for one complete simulation at one specific condition.

#ifndef _SINGLESIMULATTION_H_
#define _SINGLESIMULATTION_H_
#pragma once

#include <vector>
#include <iostream>
#include "MyLattice.h"
#include "Physics.h"

typedef std::vector<Physics> PhysicsData;

class SingleSimulation
{
public:
	SingleSimulation(const double& hamiltonian_J, const double& magnetic_B, const double& hamiltonian_D);

	MyLattice lattice;
	Physics result;
	PhysicsData flipData;

	void completeFlip(const int& step, const double& temperature, const double& hamiltonian_J, const double& magnetic_B, const double& hamiltonian_D);
	void output(std::ostream& out_Result, const int& step, const double& temperature, const double& hamiltonian_J, const double& magnetic_B, const double& hamiltonian_D);
};

#endif