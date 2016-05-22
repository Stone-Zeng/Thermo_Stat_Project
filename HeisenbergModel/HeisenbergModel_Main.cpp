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

#ifdef NORMAL_RUN

using namespace std;

int main()
{
	srand((unsigned int) time(NULL));
	MyTiming timingFlag;

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

	//double hamiltonian_J = 1.0, magnetic_B = 0.0, hamiltonian_D = 2.4494897427831780981972840747059;

	//cout << "Input B:" << endl;
	//cin >> magnetic_B;// >> hamiltonian_D;

#ifdef INPUT_PARAMETERS_ON
	cout << "Step (must be larger than 10):" << endl;
	cin >> step;
	cout << "minT, maxT:" << endl;
	cin >> min_T >> max_T;
	cout << "How many T?" << endl;
	cin >> T_n;
#endif
	double dT = (T_n == 1) ? 0.0 : (max_T - min_T) / (double) (T_n - 1);

	//Lattices, data and results:
	SingleSimulation tempSimulation(min_J, min_B, min_D);
	vector<SingleSimulation> lattices(T_n, tempSimulation);
	vector<double> T_array(T_n, 0.0);
	for (auto i = 0; i != T_n; ++i)
		T_array[i] = min_T + dT * i;

	//Simulation:
	timingFlag.timingStart();

#pragma omp parallel for
	for (auto i = 0; i < T_n; ++i) //Must use "<" instead of "!=" in order to use omp
		lattices[i].completeFlip(step, T_array[i], min_J, min_B, min_D);

	timingFlag.timingEnd();
	cout << "Simulation Time: " << timingFlag.runTime() << "s." << endl;

	//Output:
	ofstream outfile_Result;
	string filename_Result = "Result_Step=" + to_string(step)
		+ "_T=" + doubleToString(min_T) + "~" + doubleToString(max_T)
		+ ".csv";
	outfile_Result.open(filename_Result);
	outfile_Result << "T, J, B, D, " << PHYSICS_LIST << endl; //Head

	timingFlag.timingStart();
	for (auto i = 0; i != T_n; ++i)
		lattices[i].output(outfile_Result, step, T_array[i], min_J, min_B, min_D);
	timingFlag.timingEnd();
	cout << "Output Time: " << timingFlag.runTime() << "s" << endl;

	outfile_Result.close();
}

#endif