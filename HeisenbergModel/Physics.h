//This is the class for physical varibles.

#ifndef _PHYSICS_H_
#define _PHYSICS_H_
#pragma once

#include <iostream>
#include "MyVector.h"

#define PHYSICS_LIST "E, M_x, M_y, M_z"
class Physics
{
public:
	Physics();

	double energy;
	MyVector magneticDipole;

	Physics& operator+=(const Physics&);
	Physics& operator/=(const double&);

	friend Physics operator+(const Physics&, const Physics&);
	friend Physics operator/(const Physics&, const double&);
	friend std::ostream& operator<<(std::ostream&, const Physics&);
};

#endif