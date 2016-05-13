#include <algorithm>
#include <numeric>
#include <array>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
//#include <Windows.h>
#include <amp.h>
#include <omp.h>
#include "Head.h"
#include "MyLattice.h"
#include "Physics.h"
#include "SingleLattice.h"
#include "MyTiming.h"

#ifdef NORMAL_RUN

using namespace std;
using namespace concurrency;

int main()
{
	srand((unsigned int) time(NULL));
	MyTiming timingFlag;// , timingFlag_local;

	//Flip parameters:
	int step = 1;
	double temperature = 0, minTemperature = 0.1, maxTemperature = 1;
	int temperatureN = 10;

#ifdef INPUT_PARAMETERS_ON
	cout << "Step: *10000" << endl;
	cin >> step;
	step *= 10000;
	cout << "minT, maxT:" << endl;
	cin >> minTemperature >> maxTemperature;
	cout << "How many T?" << endl;
	cin >> temperatureN;
#endif

	double dTemperature = (maxTemperature - minTemperature) / (double) (temperatureN - 1);

	//TODO: Move to head.h
//#define $PHYSICAL_VARIBLE_NUMBER 4 //0:Energy; 1,2,3: MagneticDipole_x,y,z
//#define $AVERAGE_NUMBER 10

	//Lattices, data and results:
	vector<SingleLattice> lattices(temperatureN);
	vector<double> T_array(temperatureN, 0);
	for (auto i = 0; i != temperatureN; ++i)
		T_array[i] = minTemperature + dTemperature * i;

	array_view<SingleLattice, 1> lattices_AMP(temperatureN, lattices);
	array_view<double, 1> T_array_AMP(temperatureN, T_array);

	timingFlag.timingStart();

	parallel_for_each(
		lattices_AMP.extent,
		[=](index<1> idx) restrict(amp)
	//TODO: add resrict(amp).
	{lattices_AMP[idx].completeFlip(step, T_array_AMP[idx]); }
	);

	timingFlag.timingEnd();
	cout << "Time: " << timingFlag.runTime() << "s" << endl;

//	auto index_T = minTemperature;
//
//#pragma omp parallel for
//	for (auto index_T_N = 0; index_T_N < temperatureN; ++index_T_N)
//	{
//		MyLattice lattice;
//		std::array<Physics, $AVERAGE_NUMBER> result;
//
//		//Flip and save data:
//		timingFlag_local.timingStart();
//		for (auto index_step = 0; index_step != step; ++index_step)
//		{
//			lattice.flipOnePoint(index_T);
//
//			//Output data for "each" flip:
//			//TODO: This is for test only.
//			if ((index_step + 1) % (step / $DATA_NUMBER) == 0)
//			{
//				auto stepNumber = (index_step + 1) / (step / 10000) - 1;
//				flipData[index_T_N][stepNumber][0] = index_step + 1;
//				flipData[index_T_N][stepNumber][1] = lattice.totalEnergy;
//				for (auto i = 0; i != 3; ++i)
//					flipData[index_T_N][stepNumber][2 + i] = lattice.totalMagneticDipole[i];
//			}
//
//			//For "the last 10" steps:
//			for (auto i = 0; i != 10; ++i)
//				if (index_step == (step / (10 * $LAST_10_PERCENT))*((10 * $LAST_10_PERCENT - 10) + i))
//				{
//					//Calculate energy:
//					result[0][i] = lattice.totalEnergy;
//					//Calculate magnetic dipole:
//					for (auto j = 0; j != 3; ++j)
//						result[j + 1][i] = lattice.totalMagneticDipole[j];
//					////Calculate heat capacity:
//					//result[2][i] = lattice.calculateHeatCapacity() / pow(temperature, 2);
//					////Calculate magnetic susceptibility:
//					//result[3][i] = lattice.calculateMagneticSusceptibility() / arg_temperature;
//				}
//		}
//		timingFlag_local.timingEnd();
//		cout << "Time: " << timingFlag_local.runTime() << "s" << endl;
//		
//		//TODO: "result" should be changed into class.
//		for (auto i = 0; i != $PHYSICAL_VARIBLE_NUMBER; ++i)
//			averageResult[index_T_N][i] = accumulate(result[i].cbegin(), result[i].cend(), 0.0);
//		
//		for (auto i : result)
//			for (auto j : i)
//				j = 0;
//
//		index_T += dTemperature;
//	}
//	//Parallel end.
	//
	//QueryPerformanceCounter(&nEndTime);
	//cout << "Time: " << (double) (nEndTime.QuadPart - m_nBeginTime.QuadPart) / m_nFreq.QuadPart << "s" << endl;





	//index_T = minTemperature;

	//ofstream outfile_Result;
	//string filename_Result = "Result Step=" + to_string(step / 1000) +
	//	"k T=" + to_string((float) minTemperature) + ".csv";
	//outfile_Result.open(filename_Result);
	//outfile_Result << "T, E, M_x, M_y, M_z" << endl;

	//QueryPerformanceCounter(&m_nBeginTime);
	//for (auto i = 0; i != temperatureN; ++i)
	//{
	//	ofstream outfile_Data;
	//	string filename_Data = "Data Step=" + to_string(step / 1000) +
	//		"k T=" + to_string((float) index_T) + ".csv";
	//	
	//	outfile_Data.open(filename_Data);
	//	outfile_Data << "Step, E, M_x, M_y, M_z" << endl;
	//	for (auto j : flipData[i])
	//	{
	//		outfile_Data << (int) j[0] << "," //Step
	//			<< j[1] << "," //Energy
	//			<< j[2] << "," << j[3] << "," << j[4] //Magnetic dipole
	//			<< endl;
	//	}
	//	outfile_Data.close();

	//	outfile_Result << index_T << ",";
	//	for (auto j = 0; j != $PHYSICAL_VARIBLE_NUMBER - 1; ++j)
	//	{
	//		outfile_Result << averageResult[i][j] / $AVERAGE_NUMBER;
	//	}
	//	outfile_Result << averageResult[i][$PHYSICAL_VARIBLE_NUMBER - 1] / $AVERAGE_NUMBER << endl;
	//	index_T += dTemperature;
	//}
	//QueryPerformanceCounter(&nEndTime);
	//cout << "Output Time: " << (double) (nEndTime.QuadPart - m_nBeginTime.QuadPart) / m_nFreq.QuadPart << "s" << endl;

	//outfile_Result.close();
}

#endif