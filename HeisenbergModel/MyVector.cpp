#include <cmath>
#include <cstdlib>
#include "Head.h"
#include "Function.h"
#include "MyVector.h"
using namespace std;

MyVector::MyVector() :data{ 0.0,0.0,0.0 }
{}

MyVector::MyVector(const double& x, const double& y, const double& z) : data{ x,y,z }
{}

double& MyVector::operator[](int index)
{
	return data[index];
}

double MyVector::operator[](int index) const
{
	return data[index];
}

MyVector& MyVector::operator+=(const MyVector& v)
{
	for (auto i = 0; i != 3; ++i)
		data[i] += v.data[i];
	return *this;
}

MyVector& MyVector::operator-=(const MyVector& v)
{
	for (auto i = 0; i != 3; ++i)
		data[i] -= v.data[i];
	return *this;
}

MyVector& MyVector::operator*=(const double& x)
{
	for (auto i = 0; i != 3; ++i)
		data[i] *= x;
	return *this;
}

MyVector& MyVector::operator/=(const double& x)
{
	for (auto i = 0; i != 3; ++i)
		data[i] /= x;
	return *this;
}

MyVector MyVector::initialize()
{
	//For Heisenberg model:
	double r[3] = { 0 };
	double rSumSqrt = 0.0;
	for (auto i = 0; i != 3; ++i)
		r[i] = randomReal(-10, 10);
	//Anisotropy:
	r[2] *= $ANISOTROPY_INDEX;

	rSumSqrt = sqrt(r[0] * r[0] + r[1] * r[1] + r[2] * r[2]);
	for (auto i = 0; i != 3; ++i)
		data[i] = r[i] / rSumSqrt;

	////For Ising model:
	//for (int i = 0; i != 3; ++i)
	//	data[i] = 0;
	//data[2] = randomInt(0, 1) * 2 - 1;
	
	return *this;
}

double MyVector::dot(const MyVector& v)
{
	return data[0] * v.data[0] + data[1] * v.data[1] + data[2] * v.data[2];
}

MyVector MyVector::cross(const MyVector& v)
{
	MyVector result(-data[2] * v.data[1] + data[1] * v.data[2], data[2] * v.data[0] - data[0] * v.data[2], -data[1] * v.data[0] + data[0] * v.data[1]);
	return result;
}

MyVector operator+(const MyVector& v1, const MyVector& v2)
{
	MyVector v_result(v1);
	return v_result += v2;
}

MyVector operator-(const MyVector& v1, const MyVector& v2)
{
	MyVector v_result(v1);
	return v_result -= v2;
}

MyVector operator*(const MyVector& v, const double& x)
{
	MyVector v_result(v);
	return v_result *= x;
}

MyVector operator*(const double& x, const MyVector& v)
{
	MyVector v_result(v);
	return v_result *= x;
}

MyVector operator/(const MyVector& v, const double& x)
{
	MyVector v_result(v);
	return v_result /= x;
}

ostream& operator<<(ostream & out, const MyVector & v)
{
	out << v.data[0] << "," << v.data[1] << "," << v.data[2];
	return out;
}
