//This is the class for 3D unit vector, which is used for lattice 
//points in Heisenberg model.

#ifndef MYVECTOR_H_
#define MYVECTOR_H_
#pragma once

#include <iostream>
#include <cmath>
#include <cstdlib>
#include "Function.h"

class MyVector
{
private:
	double data[3];
public:
	MyVector();
	MyVector(const double&, const double&, const double&);
	
	double& operator[](int);
	double operator[](int) const;

	MyVector& operator+=(const MyVector&);
	MyVector& operator-=(const MyVector&);
	MyVector& operator*=(const double&);
	MyVector& operator/=(const double&);
	
	void initialize();
	double dot(const MyVector&);
	MyVector cross(const MyVector&);

	friend MyVector operator+(const MyVector&, const MyVector&);
	friend MyVector operator-(const MyVector&, const MyVector&);
	friend MyVector operator*(const MyVector&, const double&);
	friend MyVector operator*(const double&, const MyVector&);
	friend MyVector operator/(const MyVector&, const double&);

	friend std::ostream& operator<<(std::ostream&, const MyVector&);
};

#endif