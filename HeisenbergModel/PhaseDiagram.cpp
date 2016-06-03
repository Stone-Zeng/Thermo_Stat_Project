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
#include "SingleSimulation.h"
#include "MyTiming.h"

#ifdef PHASE_DIAGRAM_ON

using namespace std;

//Flip parameters:
//step must be larger than 10.
int step = 10;

//Temperature:
double min_T = 0.1, max_T = 1.0;
int T_n = 10;

//Hamiltonian J:
double min_J = 0.1, max_J = 1.0;
int J_n = 10;

//Magnetic B:
double min_B = 0.1, max_B = 1.0;
int B_n = 10;

//Hamiltonian D:
double min_D = 0.1, max_D = 1.0;
int D_n = 10;

int main()
{
	srand((unsigned int) time(NULL));
	MyTiming timingFlag;

	cout << endl;
#ifdef FLIP_DATA_OUTPUT_ON
	cout << "\tFLIP_DATA_OUTPUT_ON" << endl;
#else
	cout << "\tFLIP_DATA_OUTPUT_OFF" << endl;
#endif
#ifdef VECTOR_PLOT_OUTPUT_ON
	cout << "\tVECTOR_PLOT_OUTPUT_ON" << endl;
#else
	cout << "\tVECTOR_PLOT_OUTPUT_OFF" << endl;
#endif

	cout << endl << "Step (must be larger than 10):" << endl;
	cin >> step;
	cout << "minT, maxT, T number" << endl;
	cin >> min_T >> max_T >> T_n;
	cout << "minB, maxB, B number" << endl;
	cin >> min_B >> max_B >> B_n;
	cout << "J, D" << endl;
	cin >> min_J >> min_D;

	double dT = (T_n == 1) ? 0.0 : (max_T - min_T) / (double) (T_n - 1);
	double dB = (B_n == 1) ? 0.0 : (max_B - min_B) / (double) (B_n - 1);

	int totalN = T_n * B_n;
	vector<SingleSimulation> lattices;
	vector<double> T_array(T_n, 0.0);
	vector<double> B_array(B_n, 0.0);

	for (auto i = 0; i != T_n; ++i)
		T_array[i] = min_T + dT * i;
	for (auto i = 0; i != B_n; ++i)
		B_array[i] = min_B + dB * i;

	for (auto i = 0; i != T_n; ++i)
		for (auto j = 0; j != B_n; ++j)
		{
			SingleSimulation tempSimulation(min_J, B_array[j], min_D);
			lattices.push_back(tempSimulation);
		}

	//Simulation:
	timingFlag.timingStart();

#pragma omp parallel for $PARALLEL_CORES
	for (auto i = 0; i < totalN; ++i)
		lattices[i].completeFlip(step, T_array[i / B_n], min_J, B_array[i % B_n], min_D);

	timingFlag.timingEnd();
	cout << "Simulation Time: " << timingFlag.runTime() << "s." << endl;

	//Output:
	PHYSICS_LIST;
	ofstream outfile_Result[PHYSICS_NUMBER];
	string filename_Public = "_Step=" + to_string(step)
		+ "_T=" + doubleToString(min_T) + "~" + doubleToString(max_T)
		+ "_B=" + doubleToString(min_B) + "~" + doubleToString(max_B)
		+ ".csv";
	outfile_Result[0].open("Result_E" + filename_Public);
	outfile_Result[1].open("Result_Mx" + filename_Public);
	outfile_Result[2].open("Result_My" + filename_Public);
	outfile_Result[3].open("Result_Mz" + filename_Public);
	outfile_Result[4].open("Result_C" + filename_Public);
	outfile_Result[5].open("Result_X" + filename_Public);
	outfile_Result[6].open("Result_SD" + filename_Public);

	MyVector ex(1, 0, 0), ey(0, 1, 0), ez(0, 0, 1);
	timingFlag.timingStart();
	for (auto i = 0; i != T_n - 1; ++i)
	{
		for (auto j = 0; j != B_n - 1; ++j)
		{
			outfile_Result[0] << lattices[i * B_n + j].result.energy << ",";
			outfile_Result[1] << lattices[i * B_n + j].result.magneticDipole.dot(ex) << ",";
			outfile_Result[2] << lattices[i * B_n + j].result.magneticDipole.dot(ey) << ",";
			outfile_Result[3] << lattices[i * B_n + j].result.magneticDipole.dot(ez) << ",";
			outfile_Result[4] << lattices[i * B_n + j].result.heatCapacity << ",";
			outfile_Result[5] << lattices[i * B_n + j].result.magneticSusceptibility << ",";
			outfile_Result[6] << lattices[i * B_n + j].result.skyrmionDensity << ",";
		}
		outfile_Result[0] << lattices[i * B_n + B_n - 1].result.energy << endl;
		outfile_Result[1] << lattices[i * B_n + B_n - 1].result.magneticDipole.dot(ex) << endl;
		outfile_Result[2] << lattices[i * B_n + B_n - 1].result.magneticDipole.dot(ey) << endl;
		outfile_Result[3] << lattices[i * B_n + B_n - 1].result.magneticDipole.dot(ez) << endl;
		outfile_Result[4] << lattices[i * B_n + B_n - 1].result.heatCapacity << endl;
		outfile_Result[5] << lattices[i * B_n + B_n - 1].result.magneticSusceptibility << endl;
		outfile_Result[6] << lattices[i * B_n + B_n - 1].result.skyrmionDensity << endl;
	}
	for (auto j = 0; j != B_n - 1; ++j)
	{
		outfile_Result[0] << lattices[(T_n - 1) * B_n + j].result.energy << ",";
		outfile_Result[1] << lattices[(T_n - 1) * B_n + j].result.magneticDipole.dot(ex) << ",";
		outfile_Result[2] << lattices[(T_n - 1) * B_n + j].result.magneticDipole.dot(ey) << ",";
		outfile_Result[3] << lattices[(T_n - 1) * B_n + j].result.magneticDipole.dot(ez) << ",";
		outfile_Result[4] << lattices[(T_n - 1) * B_n + j].result.heatCapacity << ",";
		outfile_Result[5] << lattices[(T_n - 1) * B_n + j].result.magneticSusceptibility << ",";
		outfile_Result[6] << lattices[(T_n - 1) * B_n + j].result.skyrmionDensity << ",";
	}
	outfile_Result[0] << lattices[(T_n - 1) * B_n + B_n - 1].result.energy;
	outfile_Result[1] << lattices[(T_n - 1) * B_n + B_n - 1].result.magneticDipole.dot(ex);
	outfile_Result[2] << lattices[(T_n - 1) * B_n + B_n - 1].result.magneticDipole.dot(ey);
	outfile_Result[3] << lattices[(T_n - 1) * B_n + B_n - 1].result.magneticDipole.dot(ez);
	outfile_Result[4] << lattices[(T_n - 1) * B_n + B_n - 1].result.heatCapacity;
	outfile_Result[5] << lattices[(T_n - 1) * B_n + B_n - 1].result.magneticSusceptibility;
	outfile_Result[6] << lattices[(T_n - 1) * B_n + B_n - 1].result.skyrmionDensity;


	timingFlag.timingEnd();
	cout << "Output Time: " << timingFlag.runTime() << "s" << endl;

	for (auto i = 0; i != PHYSICS_NUMBER; ++i)
		outfile_Result[i].close();
}
#endif