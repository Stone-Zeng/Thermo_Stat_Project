#include <iostream>
#include <fstream>
#include "Head.h"
#include "Function.h"
#include "SingleSimulation.h"
using namespace std;

SingleSimulation::SingleSimulation(const double & hamiltonian_J, const double & magnetic_B, const double & hamiltonian_D) :lattice(hamiltonian_J, magnetic_B, hamiltonian_D)
{}

void SingleSimulation::completeFlip(const int& step, const double& temperature, const double& hamiltonian_J, const double& magnetic_B, const double& hamiltonian_D)
{
	result *= 0;

	for (auto step_index = 0; step_index != step; ++step_index)
	{
		//Output data for each MCS:
#ifdef FLIP_DATA_OUTPUT_ON
		flipData.push_back(lattice.physicalQuantity);
#endif

		//TODO: Figure:
#ifdef VECTOR_PLOT_OUTPUT_ON
		if ((step_index + 1) % (step / 20) == 0)
		{
			auto stepNumber = (step_index + 1) / (step / $DATA_NUMBER) - 1;
		
			ofstream out;
			string filename = "B=" + doubleToString(magnetic_B) + "_D=" + doubleToString(hamiltonian_D) + "_Step_" + to_string(step_index + 1) + ".vector";
			out.open(filename);
		
			out << "{";
			for (auto i = 0; i != X_LENGTH - 1; ++i)
			{
				out << "{";
				for (auto j = 0; j != Y_LENGTH - 1; ++j)
				{
					out << "{" << lattice.data[i][j] << "},";
				}
				out << "{" << lattice.data[i][Y_LENGTH - 1] << "}},";
			}
			out << "{";
			for (auto j = 0; j != Y_LENGTH - 1; ++j)
			{
				out << "{" << lattice.data[X_LENGTH - 1][j] << "},";
			}
			out << "{" << lattice.data[X_LENGTH - 1][Y_LENGTH - 1] << "}}}";
		
			out.close();
		}
#endif

		lattice.oneMonteCarloStep(temperature, hamiltonian_J, magnetic_B, hamiltonian_D);

		//For "the last 10" steps:
		for (auto i = 0; i != $AVERAGE_NUMBER; ++i)
			if (step_index == step - $AVERAGE_NUMBER + i)
				//Now "result" is the total value.
				result += lattice.physicalQuantity;
	}

	//Get the average value.
	result *= 1 / (double) $AVERAGE_NUMBER;

	//Finishing information:
	cout << "T=" + doubleToString(temperature)
		+ "  J=" + doubleToString(hamiltonian_J)
		+ "  B=" + doubleToString(magnetic_B)
		+ "  D=" + doubleToString(hamiltonian_D)
		+ "  Complete!\n";
}

void SingleSimulation::output(std::ostream& out_Result, const int& step, const double& temperature, const double& hamiltonian_J, const double& magnetic_B, const double& hamiltonian_D)
{
#ifdef FLIP_DATA_OUTPUT_ON
	//Output data:
	ofstream out_Data;
	string filename_Data = "Data_Step=" + to_string(step) +
		"_T=" + doubleToString(temperature) +
		"_J=" + doubleToString(hamiltonian_J) +
		"_B=" + doubleToString(magnetic_B) +
		"_D=" + doubleToString(hamiltonian_D) + 
		".csv";
	out_Data.open(filename_Data);
	out_Data << "Step, " << PHYSICS_LIST << endl;

	int step_N = 0;
	for (auto i : flipData)
	{
		out_Data << step_N << "," << i << endl;
		++step_N;
	}

	out_Data.close();
#endif

	//Output result:
	out_Result << temperature << "," << hamiltonian_J << "," << magnetic_B << "," << hamiltonian_D << ","
		<< result << endl;
}