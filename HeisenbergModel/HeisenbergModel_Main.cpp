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
	int step = 1;
	double temperature = 0, minTemperature = 0.1, maxTemperature = 1;
	int temperatureN = 10;
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
	vector<SingleLattice> lattices(temperatureN);
	vector<double> T_array(temperatureN, 0);
	for (auto i = 0; i != temperatureN; ++i)
		T_array[i] = minTemperature + dTemperature * i;

	//Flip:
	timingFlag.timingStart();
#pragma omp parallel for
	for (auto i = 0; i < temperatureN; ++i) //Must use "<" instead of "!=" in order to use omp
		lattices[i].completeFlip(step, T_array[i]);
	timingFlag.timingEnd();
	cout << "Time: " << timingFlag.runTime() << "s" << endl;

	//Output:
	ofstream outfile_Result;
	string filename_Result = "Result Step=" + to_string(step / 1000) + "K "
		+ "T=" + doubleToString(minTemperature) + "~" + doubleToString(maxTemperature)
		+ ".csv";
	outfile_Result.open(filename_Result);
	outfile_Result << "T, " << PHYSICS_LIST << endl; //Head

	timingFlag.timingStart();
	for (auto i = 0; i != temperatureN; ++i)
		lattices[i].output(outfile_Result, step, T_array[i]);
	timingFlag.timingEnd();
	cout << "Output Time: " << timingFlag.runTime() << "s" << endl;

	outfile_Result.close();
}

#endif