//#include "Head.h"
//#include "MyLattice.h"
//using namespace std;
//
//int main(int argc, char* argv[])
//{
//	double arg_temprature = atof(argv[1]);
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
//	MyLattice lattice(LENGTH_X, LENGTH_Y, LENGTH_Z);
//
//	ofstream outfile;
//	outfile.open($FILENAME_CSV);
//
//	output(outfile, 0, lattice.totalEnergy, lattice.totalMagneticDipole);
//
//	//Flip...
//	for (int index_step = 0; index_step != arg_step; ++index_step)
//	{
//		lattice.flipOnePoint(arg_temprature);
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
//				result[2][index] = lattice.calculateHeatCapacity() / pow(arg_temprature, 2);
//				//Calculate magnetic susceptibility:
//				result[3][index] = lattice.calculateMagneticSusceptibility() / arg_temprature;
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
//		<< "\tLattice size: X = " << LENGTH_X << ", Y = " << LENGTH_Y << ", Z = " << LENGTH_Z << endl
//		<< "\tTemperature: " << arg_temprature << endl
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

