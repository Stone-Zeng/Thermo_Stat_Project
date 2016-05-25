#include <cmath>
#include <cstdlib>
#include "Function.h"
#include "MyVector.h"
#include "MyLattice.h"
using namespace std;

inline int MyLattice::x_minus_1(const int& x)
{
	return (x == 0 ? X_LENGTH - 1 : x - 1);
}

inline int MyLattice::x_plus_1(const int& x)
{
	return (x == X_LENGTH - 1 ? 0 : x + 1);
}

inline int MyLattice::y_minus_1(const int& y)
{
	return (y == 0 ? Y_LENGTH - 1 : y - 1);
}

inline int MyLattice::y_plus_1(const int& y)
{
	return (y == Y_LENGTH - 1 ? 0 : y + 1);
}

//#define HAMILTONIAN_J 1.0
//#define HAMILTONIAN_D 2.4494897427831780981972840747059

inline double MyLattice::energyCount(const Point& p, const int& i, const int& j, const double& hamiltonian_J,const double& magnetic_B, const double& hamiltonian_D)
{
	double H = 0.0;
	auto leftP = data[x_minus_1(i)][j], rightP = data[x_plus_1(i)][j];
	auto downP = data[i][y_minus_1(j)], upP = data[i][y_plus_1(j)];
	//TODO: Outside field can be added here.

	//Exchange:
	H -= hamiltonian_J * (leftP + rightP + downP + upP).dot(p);

	////Zeeman(magnetic field):
	MyVector B(0, 0, magnetic_B);
	H -= B.dot(p);

	//D-M interaction:
	MyVector ex(1, 0, 0), ey(0, 1, 0);
	H -= hamiltonian_D * (
		(-(leftP.cross(p)).dot(ex)) + (rightP.cross(p)).dot(ex)
		- (downP.cross(p)).dot(ey) + (upP.cross(p)).dot(ey)
		);

	return H;
}

MyLattice::MyLattice(const double& hamiltonian_J, const double& magnetic_B, const double& hamiltonian_D)
{
	for (auto i = 0; i != X_LENGTH; ++i)
		for (auto j = 0; j != Y_LENGTH; ++j)
			data[i][j].initialize();

	//Calculate the initial physical varibles:
	for (auto i = 0; i != X_LENGTH; ++i)
		for (auto j = 0; j != Y_LENGTH; ++j)
		{
			physicalQuantity.energy += energyCount(data[i][j], i, j, hamiltonian_J, magnetic_B, hamiltonian_D);
			physicalQuantity.magneticDipole += data[i][j];
		}
}

void MyLattice::oneMonteCarloStep(const double& temperature, const double& hamiltonian_J, const double& magnetic_B, const double& hamiltonian_D)
{
	//Calculate origin energy and magnetic dipole:
	//TODO: Not necessary.
	//physicalQuantity.energy = calculateEnergy(hamiltonian_J, magnetic_B, hamiltonian_D);
	//physicalQuantity.magneticDipole = calculateMagneticDipole();

	for (auto i = 0; i != X_LENGTH; ++i)
		for (auto j = 0; j != Y_LENGTH; ++j)
		{
			MyVector pointAfter;
			pointAfter.initialize();
			//auto dE = energyCount(pointAfter, i, j, hamiltonian_J, magnetic_B, hamiltonian_D) - energyCount(data[i][j], i, j, hamiltonian_J, magnetic_B, hamiltonian_D);
			auto dE = energyCount(pointAfter - data[i][j], i, j, hamiltonian_J, magnetic_B, hamiltonian_D);
	
			//Flip:
			if (randomReal(0, 1) < possibilityOfFlip(dE, temperature))
			{
				data[i][j] = pointAfter;
				//physicalQuantity.energy += dE;
				//physicalQuantity.magneticDipole += data[i][j];
			}
		}

	//Calculate final physical quantities:
	physicalQuantity.energy = calculateEnergy(hamiltonian_J, magnetic_B, hamiltonian_D);
	physicalQuantity.magneticDipole = calculateMagneticDipole();
	physicalQuantity.heatCapacity = calculateHeatCapacity(hamiltonian_J, magnetic_B, hamiltonian_D);
	physicalQuantity.magneticSusceptibility = calculateMagneticSusceptibility();
	physicalQuantity.skyrmionDensity = calculateSkyrmionDensity();
}

double MyLattice::calculateEnergy(const double& hamiltonian_J, const double& magnetic_B, const double& hamiltonian_D)
{
	double E = 0.0;
	for (auto i = 0; i != X_LENGTH; ++i)
		for (auto j = 0; j != Y_LENGTH; ++j)
			E += energyCount(data[i][j], i, j, hamiltonian_J, magnetic_B, hamiltonian_D);
	return E;
}

MyVector MyLattice::calculateMagneticDipole()
{
	MyVector M;
	for (auto i = 0; i != X_LENGTH; ++i)
		for (auto j = 0; j != Y_LENGTH; ++j)
			M += data[i][j];
	return M;
}

double MyLattice::calculateHeatCapacity(const double& hamiltonian_J, const double& magnetic_B, const double& hamiltonian_D)
{
	double E = 0.0, E_square = 0.0;
	const int size = X_LENGTH * Y_LENGTH;

	for (auto i = 0; i != X_LENGTH; ++i)
		for (auto j = 0; j != Y_LENGTH; ++j)
		{
			double E_temp = energyCount(data[i][j], i, j, hamiltonian_J, magnetic_B, hamiltonian_D);
			E += E_temp;
			E_square += E_temp * E_temp;
		}
	return E_square / size - (E / size) * (E / size);
}

double MyLattice::calculateMagneticSusceptibility()
{
	MyVector M;
	double M_square = 0.0;
	const int size = X_LENGTH * Y_LENGTH;

	for (auto i = 0; i != X_LENGTH; ++i)
		for (auto j = 0; j != Y_LENGTH; ++j)
		{
			auto M_temp = data[i][j];
			M += M_temp;
			M_square += M_temp.dot(M_temp);
		}
	return M_square / size - M.dot(M) / (size * size);
}

double MyLattice::calculateSkyrmionDensity()
{
	double SD = 0.0;
	for (auto i = 0; i != X_LENGTH; ++i)
		for (auto j = 0; j != Y_LENGTH; ++j)
		{
			//auto dx = data[x_plus_1(i)][j] - data[x_minus_1(i)][j];
			//auto dy = data[i][y_plus_1(j)] - data[i][y_minus_1(j)];
			SD += data[i][j].dot(
				(data[i][y_plus_1(j)] - data[i][y_minus_1(j)]).cross(data[x_plus_1(i)][j] - data[x_minus_1(i)][j])
			);
		}
	return SD;
}
