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

inline double MyLattice::energyCount(const Point& p, const int& i, const int& j)
{
	return data[x_minus_1(i)][j].dot(p) + data[x_plus_1(i)][j].dot(p)
		+ data[y_minus_1(i)][j].dot(p) + data[y_plus_1(i)][j].dot(p);
}

//inline int MyLattice::energyOfChange(const int& x, const int& y, const int& z)
//{
//	return 2 * (energyCount(!(data[x][y][z]), x, y, z) - energyCount(data[x][y][z], x, y, z));
//}

MyLattice::MyLattice()
{
	for (auto &i : data)
		for (auto j : i)
			j.initialize();

	//Calculate the initial physical varibles:
	for (auto i = 0; i != X_LENGTH; ++i)
		for (auto j = 0; j != Y_LENGTH; ++j)
			{
				physicalQuantity.energy += energyCount(data[i][j], i, j);
				physicalQuantity.magneticDipole += data[i][j];
			}
}

void MyLattice::flipOnePoint(const double& temperature)
{
	auto i = randomInt(0, X_LENGTH - 1), j = randomInt(0, Y_LENGTH - 1);

	MyVector pointAfter;
	pointAfter.initialize();
	auto dE = energyCount(pointAfter, i, j) - energyCount(data[i][j], i, j);

	if (randomReal(0, 1) < possibilityOfFlip(dE, temperature))
	{
		data[i][j] = pointAfter;
		physicalQuantity.energy += dE;
		physicalQuantity.magneticDipole += data[i][j];
	}
}
//
//double MyLattice::calculateHeatCapacity()
//{
//	int E = 0, E_square = 0;
//	for (auto i = 0; i != X_LENGTH; ++i)
//		for (auto j = 0; j != Y_LENGTH; ++j)
//			for (auto k = 0; k != LENGTH_Z; ++k)
//			{
//				int E_temp = energyCount(data[i][j][k], i, j, k);
//				E += E_temp;
//				E_square += E_temp * E_temp;
//			}
//	return (double) E_square / (double) SIZE - pow(E / SIZE, 2);
//}
//
//double MyLattice::calculateMagneticSusceptibility()
//{
//	int M = 0, M_square = 0;
//	for (auto i = 0; i != X_LENGTH; ++i)
//		for (auto j = 0; j != Y_LENGTH; ++j)
//			for (auto k = 0; k != LENGTH_Z; ++k)
//			{
//				int M_temp = data[i][j][k] ? 1 : -1;
//				M += M_temp;
//				M_square += M_temp * M_temp;
//			}
//	return (double) M_square / (double) SIZE - pow(M / SIZE, 2);
//}
//
////void MyLattice::outputData(ofstream& file)
////{
////	file << "{";
////	for (int i = 0; i < x_Length - 1; ++i)
////	{
////		file << "{";
////		for (int j = 0; j < y_Length - 1; ++j)
////			file << data[i][j] << ",";
////		file << data[i][y_Length - 1] << "},";
////	}
////	file << "{";
////	for (int j = 0; j < y_Length - 1; ++j)
////		file << data[x_Length - 1][j] << ",";
////	file << data[x_Length - 1][y_Length - 1] << "}},";
////}