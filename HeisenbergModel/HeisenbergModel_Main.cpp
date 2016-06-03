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

void simulationWithT()
{
	MyTiming timingFlag;

#ifdef INPUT_PARAMETERS_ON
	cout << "minT, maxT:" << endl;
	cin >> min_T >> max_T;
	cout << "How many T?" << endl;
	cin >> T_n;
	cout << "Input J, B, D:" << endl;
	cin >> min_J >> min_B >> min_D;
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

#pragma omp parallel for $PARALLEL_CORES
	for (auto i = 0; i < T_n; ++i)
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

void simulationWithJ()
{
	MyTiming timingFlag;

#ifdef INPUT_PARAMETERS_ON
	cout << "minJ, maxJ:" << endl;
	cin >> min_J >> max_J;
	cout << "How many J?" << endl;
	cin >> J_n;
	cout << "Input T, B, D:" << endl;
	cin >> min_T >> min_B >> min_D;
#endif
	double dJ = (J_n == 1) ? 0.0 : (max_J - min_J) / (double) (J_n - 1);

	//Lattices, data and results:
	vector<SingleSimulation> lattices;
	vector<double> J_array(J_n, 0.0);
	for (auto i = 0; i != J_n; ++i)
	{
		J_array[i] = min_J + dJ * i;
		SingleSimulation tempSimulation(J_array[i], min_B, min_D);
		lattices.push_back(tempSimulation);
	}

	//Simulation:
	timingFlag.timingStart();

#pragma omp parallel for $PARALLEL_CORES
	for (auto i = 0; i < J_n; ++i)
		lattices[i].completeFlip(step, min_T, J_array[i], min_B, min_D);

	timingFlag.timingEnd();
	cout << "Simulation Time: " << timingFlag.runTime() << "s." << endl;

	//Output:
	ofstream outfile_Result;
	string filename_Result = "Result_Step=" + to_string(step)
		+ "_J=" + doubleToString(min_J) + "~" + doubleToString(max_J)
		+ ".csv";
	outfile_Result.open(filename_Result);
	outfile_Result << "T, J, B, D, " << PHYSICS_LIST << endl; //Head

	timingFlag.timingStart();
	for (auto i = 0; i != J_n; ++i)
		lattices[i].output(outfile_Result, step, min_T, J_array[i], min_B, min_D);
	timingFlag.timingEnd();
	cout << "Output Time: " << timingFlag.runTime() << "s" << endl;

	outfile_Result.close();
}

void simulationWithB()
{
	MyTiming timingFlag;

#ifdef INPUT_PARAMETERS_ON
	cout << "minB, maxB:" << endl;
	cin >> min_B >> max_B;
	cout << "How many B?" << endl;
	cin >> B_n;
	cout << "Input T, J, D:" << endl;
	cin >> min_T >> min_J >> min_D;
#endif
	double dB = (B_n == 1) ? 0.0 : (max_B - min_B) / (double) (B_n - 1);

	//Lattices, data and results:
	vector<SingleSimulation> lattices;
	vector<double> B_array(B_n, 0.0);
	for (auto i = 0; i != B_n; ++i)
	{
		B_array[i] = min_B + dB * i;
		SingleSimulation tempSimulation(min_J, B_array[i], min_D);
		lattices.push_back(tempSimulation);
	}

	//Simulation:
	timingFlag.timingStart();

#pragma omp parallel for $PARALLEL_CORES
	for (auto i = 0; i < B_n; ++i)
		lattices[i].completeFlip(step, min_T, min_J, B_array[i], min_D);

	timingFlag.timingEnd();
	cout << "Simulation Time: " << timingFlag.runTime() << "s." << endl;

	//Output:
	ofstream outfile_Result;
	string filename_Result = "Result_Step=" + to_string(step)
		+ "_B=" + doubleToString(min_B) + "~" + doubleToString(max_B)
		+ ".csv";
	outfile_Result.open(filename_Result);
	outfile_Result << "T, J, B, D, " << PHYSICS_LIST << endl; //Head

	timingFlag.timingStart();
	for (auto i = 0; i != B_n; ++i)
		lattices[i].output(outfile_Result, step, min_T, min_J, B_array[i], min_D);
	timingFlag.timingEnd();
	cout << "Output Time: " << timingFlag.runTime() << "s" << endl;

	outfile_Result.close();
}

void simulationWithD()
{
	MyTiming timingFlag;

#ifdef INPUT_PARAMETERS_ON
	cout << "minD, maxD:" << endl;
	cin >> min_D >> max_D;
	cout << "How many D?" << endl;
	cin >> D_n;
	cout << "Input T, J, B:" << endl;
	cin >> min_T >> min_J >> min_B;
#endif
	double dD = (D_n == 1) ? 0.0 : (max_D - min_D) / (double) (D_n - 1);

	//Lattices, data and results:
	vector<SingleSimulation> lattices;
	vector<double> D_array(D_n, 0.0);
	for (auto i = 0; i != D_n; ++i)
	{
		D_array[i] = min_D + dD * i;
		SingleSimulation tempSimulation(min_J, min_B, D_array[i]);
		lattices.push_back(tempSimulation);
	}

	//Simulation:
	timingFlag.timingStart();

#pragma omp parallel for $PARALLEL_CORES
	for (auto i = 0; i < D_n; ++i)
		lattices[i].completeFlip(step, min_T, min_J, min_B, D_array[i]);

	timingFlag.timingEnd();
	cout << "Simulation Time: " << timingFlag.runTime() << "s." << endl;

	//Output:
	ofstream outfile_Result;
	string filename_Result = "Result_Step=" + to_string(step)
		+ "_D=" + doubleToString(min_D) + "~" + doubleToString(max_D)
		+ ".csv";
	outfile_Result.open(filename_Result);
	outfile_Result << "T, J, B, D, " << PHYSICS_LIST << endl; //Head

	timingFlag.timingStart();
	for (auto i = 0; i != D_n; ++i)
		lattices[i].output(outfile_Result, step, min_T, min_J, min_B, D_array[i]);
	timingFlag.timingEnd();
	cout << "Output Time: " << timingFlag.runTime() << "s" << endl;

	outfile_Result.close();
}

int main()
{
	srand((unsigned int) time(NULL));

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
	int variableFlag = 0;
	cout << "Variable:" << endl
		<< "  1.T  2.J  3.B  4.D" << endl;
	cin >> variableFlag;

	switch (variableFlag)
	{
		case 1:
			simulationWithT();
			break;
		case 2:
			simulationWithJ();
			break;
		case 3:
			simulationWithB();
			break;
		case 4:
			simulationWithD();
			break;
		default:
			break;
	}

	return 0;
}

#endif