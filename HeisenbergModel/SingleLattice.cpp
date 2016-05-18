#include <iostream>
#include <fstream>
#include "Head.h"
#include "Function.h"
#include "SingleLattice.h"
using namespace std;

void SingleLattice::completeFlip(const int& step, const double& temperature)
{
	for (auto step_index = 0; step_index != step; ++step_index)
	{
		//Output data for "each" flip:
#ifdef FLIP_DATA_OUTPUT_ON
		if ((step_index + 1) % (step / $DATA_NUMBER) == 0)
		{
			auto stepNumber = (step_index + 1) / (step / $DATA_NUMBER) - 1;
			auto iter = flipData.begin() + stepNumber;
			*iter = lattice.physicalQuantity;
		}
#endif

		//TODO: Figure:
#ifdef VECTOR_PLOT_OUTPUT_ON
		if ((step_index + 1) % (step / 20) == 0)
		{
			auto stepNumber = (step_index + 1) / (step / $DATA_NUMBER) - 1;
		
			ofstream out;
			string filename = "VEC" + to_string(step_index + 1);
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

		lattice.flipOnePoint(temperature);

		//For "the last 10" steps:
		for (auto i = 0; i != 10; ++i)
			if (step_index == (step / (10 * $LAST_10_PERCENT)) * (10 * ($LAST_10_PERCENT - 1) + i))
				//Now "result" is the total value.
				result += lattice.physicalQuantity;
	}
}

void SingleLattice::output(std::ostream& out_Result, const int& step, const double& temperature)
{
#ifdef FLIP_DATA_OUTPUT_ON
	//Output data:
	ofstream out_Data;
	string filename_Data = "Data Step=" + to_string(step / 1000) +
		"k T=" + doubleToString(temperature) + ".csv";
	out_Data.open(filename_Data);
	out_Data << "Step, " << PHYSICS_LIST << endl;

	auto step_N = 0;
	for (auto i : flipData)
	{
		out_Data << step_N << "," << i << endl;
		step_N += step / $DATA_NUMBER;
	}

	out_Data.close();
#endif

	//Output result:
	out_Result << temperature << ","
		<< result / 10 << endl;
}