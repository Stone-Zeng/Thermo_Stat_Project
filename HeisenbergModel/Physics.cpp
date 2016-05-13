#include <iostream>
#include "Physics.h"
using namespace std;

Physics::Physics() :energy(0.0), magneticDipole(0, 0, 0)
{}

Physics& Physics::operator+=(const Physics& x)
{
	energy += x.energy;
	magneticDipole += x.magneticDipole;
	return *this;
}

Physics& Physics::operator/=(const double& x)
{
	energy /= x;
	magneticDipole /= x;
	return *this;
}

Physics operator+(const Physics& x, const Physics& y)
{
	Physics result(x);
	return result += y;
}

Physics operator/(const Physics& p, const double& x)
{
	Physics result(p);
	return result /= x;
}

std::ostream & operator<<(std::ostream& out, const Physics& x)
{
	out << x.energy << "," << x.magneticDipole;
	return out;
}
