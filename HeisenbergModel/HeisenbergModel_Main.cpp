#include "Head.h"
#include "MyLattice.h"
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include <omp.h>
using namespace std;

int main()
{
	srand((unsigned int) time(NULL));
	auto step = 0;
	double temperature = 0, minTemperature = 0, maxTemperature = 0;
	int temperatureN = 0;
	cout << "Step: *10000" << endl;
	cin >> step;
	step *= 10000;
	cout << "minT, maxT:" << endl;
	cin >> minTemperature >> maxTemperature;
	cout << "How many T?" << endl;
	cin >> temperatureN;
	//minTemperature = 0.1;
	//maxTemperature = 10;
	//temperatureN = 100;
	double dTemperature = (maxTemperature - minTemperature) / (double) (temperatureN - 1);


	double result[4][11] = { 0 }; //The 11th element is for the total value

	ofstream outfile;
	string filename = "Output_step=" + to_string(step / 1000) +
		"k_T=" + to_string(minTemperature) + "--" + to_string(maxTemperature) + ".csv";
	outfile.open(filename);

	//outfile << lattice.totalEnergy << endl;

	auto index_T = minTemperature;
	LARGE_INTEGER m_nFreq;
	LARGE_INTEGER m_nBeginTime;
	LARGE_INTEGER nEndTime;
	QueryPerformanceFrequency(&m_nFreq); // 获取时钟周期  
	QueryPerformanceCounter(&m_nBeginTime);
#pragma omp parallel for
	for (auto i = 0; i < temperatureN; ++i)
	{
		MyLattice lattice;

		ofstream outfile_flip;
		string filename_flip = "OutputFlip_step=" + to_string(step / 100) +
			"k_T=" + to_string(index_T) + ".csv";
		outfile_flip.open(filename_flip);

		for (auto index_step = 0; index_step != step; ++index_step)
		{
			lattice.flipOnePoint(index_T);

			if ((index_step + 1) % (step / 10000) == 0)
				outfile_flip << index_step + 1 << "," << lattice.totalEnergy << endl;

			//For "the last 10" steps:
			for (auto i = 0; i != 10; ++i)
				if (index_step == (step / (10 * $LAST_10_PERCENT))*((10 * $LAST_10_PERCENT - 10) + i))
				{
					//Calculate energy:
					result[0][i] = lattice.totalEnergy;
					////Calculate magnetic dipole:
					//result[1][i] = lattice.totalMagneticDipole;
					////Calculate heat capacity:
					//result[2][i] = lattice.calculateHeatCapacity() / pow(temperature, 2);
					////Calculate magnetic susceptibility:
					//result[3][i] = lattice.calculateMagneticSusceptibility() / arg_temperature;
				}
			//if (index_step % (step / $DATA_NUMBER) == 0)
			//	output(outfile, index_step, lattice.totalEnergy, lattice.totalMagneticDipole);
		}

		for (auto j = 0; j != 10; ++j)
			result[0][10] += result[0][j];

		outfile_flip.close();
		string r = to_string(index_T) + "," + to_string(result[0][10] / 10) + "\n";
		outfile << r;

		for (auto j = 0; j != 11; ++j)
			result[0][j] = 0;

		index_T += dTemperature;
	}
	QueryPerformanceCounter(&nEndTime);
	cout << "Time: " << (double) (nEndTime.QuadPart - m_nBeginTime.QuadPart) / m_nFreq.QuadPart << "s" << endl;
}



//int main(int argc, char* argv[])
//{
//	double arg_temperature = atof(argv[1]);
//#ifdef USING_ARG_STEP
//	int arg_step = atoi(argv[2]) * 10000;
//#else
//	int arg_step = STEP;
//#endif
//	double result[4][11] = { 0 }; //The 11th element is for the total value
//
//#ifndef CPP11_RANDOM
//	srand((unsigned int) time(NULL));
//#endif
//	MyLattice lattice(X_LENGTH, Y_LENGTH, LENGTH_Z);
//
//	ofstream outfile;
//	outfile.open($FILENAME_CSV);
//
//	output(outfile, 0, lattice.totalEnergy, lattice.totalMagneticDipole);
//
//	//Flip...
//	for (int index_step = 0; index_step != arg_step; ++index_step)
//	{
//		lattice.flipOnePoint(arg_temperature);
//
//		//For "the last 10" steps:
//		for (auto index = 0; index != 10; ++index)
//			if (index_step == (arg_step / (10 * $LAST_10_PERCENT))*((10 * $LAST_10_PERCENT - 10) + index))
//			{
//				//Calculate energy:
//				result[0][index] = lattice.totalEnergy;
//				//Calculate magnetic dipole:
//				result[1][index] = lattice.totalMagneticDipole;
//				//Calculate heat capacity:
//				result[2][index] = lattice.calculateHeatCapacity() / pow(arg_temperature, 2);
//				//Calculate magnetic susceptibility:
//				result[3][index] = lattice.calculateMagneticSusceptibility() / arg_temperature;
//			}
//		if (index_step % (arg_step / $DATA_NUMBER) == 0)
//			output(outfile, index_step, lattice.totalEnergy, lattice.totalMagneticDipole);
//		
//		//Display progress:
//		if (index_step % (arg_step / $DISPLAY_NUMBER) == 0)
//			cout << "Complete " << 100 * index_step / arg_step << "%" << endl;
//	}
//
//	outfile.close();
//#ifdef OUTPUT_DATA
//	outfile_data.close();
//#endif
//
//	cout << endl << "Complete!" << endl;
//
//	//Display information:
//	cout << "Information:" << endl
//		<< "\tLattice size: X = " << X_LENGTH << ", Y = " << Y_LENGTH << ", Z = " << LENGTH_Z << endl
//		<< "\tTemperature: " << arg_temperature << endl
//		<< "\tSteps: 10e" << log10(arg_step) << endl << endl;
//	for (auto i = 0; i != 4; ++i)
//		for (auto j = 0; j != 10; ++j)
//			result[i][10] += result[i][j];
//
//	cout << "Results:" << endl
//		<< "\tEnergy: " << result[0][10] / 10 << endl
//		<< "\tMagnetic dipole: " << abs(result[1][10]) / 10 << endl
//		<< "\tHeat capacity: " << result[2][10] / 10 << endl
//		<< "\tMagnetic susceptibility: " << result[3][10] / 10 << endl;
//	return 0;
//}

