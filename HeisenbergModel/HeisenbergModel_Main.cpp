#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <omp.h>
#include "Head.h"
#include "Function.h"
#include "MyLattice.h"
#include "Physics.h"
#include "SingleLattice.h"
#include "MyTiming.h"

#ifdef NORMAL_RUN

using namespace std;

int main()
{
	srand((unsigned int) time(NULL));
	MyTiming timingFlag;

	//Flip parameters:
	int step = 1000;
	double temperature = 0, minTemperature = 0.01, maxTemperature = 0.01;
	int temperatureN = 1;
	double hamiltonian_J = 1.0, magnetic_B = 0.0, hamiltonian_D = 2.4494897427831780981972840747059;

	cout << "Input B:" << endl;
	cin >> magnetic_B;// >> hamiltonian_D;

#ifdef INPUT_PARAMETERS_ON
	cout << "Step: *10000" << endl;
	cin >> step;
	//step *= 10000;
	cout << "minT, maxT:" << endl;
	cin >> minTemperature >> maxTemperature;
	cout << "How many T?" << endl;
	cin >> temperatureN;
#endif
	double dTemperature = ((temperatureN == 1) ? 0.0 : (maxTemperature - minTemperature) / (double) (temperatureN - 1));

	//Lattices, data and results:
	SingleLattice temp(hamiltonian_J, magnetic_B, hamiltonian_D);
	vector<SingleLattice> lattices{ temp };
	vector<double> T_array(temperatureN, 0);
	for (auto i = 0; i != temperatureN; ++i)
		T_array[i] = minTemperature + dTemperature * i;

	//Flip:
	timingFlag.timingStart();

	//parallel_for_each(
	//	lattices_AMP.extent,
	//	[=](index<1> idx) restrict(amp)
	//	//TODO: add resrict(amp).
	//{lattices_AMP[idx].completeFlip(step, T_array_AMP[idx]); }
	//);

//#pragma omp parallel for
	for (auto i = 0; i < temperatureN; ++i) //Must use "<" instead of "!=" in order to use omp
		lattices[i].completeFlip(step, T_array[i], hamiltonian_J, magnetic_B, hamiltonian_D);

	timingFlag.timingEnd();
	cout << "Time: " << timingFlag.runTime() << "s" << endl;

	////Output:
	//ofstream outfile_Result;
	//string filename_Result = "Result Step=" + to_string(step / 1000) + "K "
	//	+ "T=" + doubleToString(minTemperature) + "~" + doubleToString(maxTemperature)
	//	+ ".csv";
	//outfile_Result.open(filename_Result);
	//outfile_Result << "T, " << PHYSICS_LIST << endl; //Head

	//timingFlag.timingStart();
	//for (auto i = 0; i != temperatureN; ++i)
	//	lattices[i].output(outfile_Result, step, T_array[i]);
	//timingFlag.timingEnd();
	//cout << "Output Time: " << timingFlag.runTime() << "s" << endl;

	//outfile_Result.close();
}

#endif