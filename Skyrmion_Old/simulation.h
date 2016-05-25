#ifndef SIMULATION_H_INCLUDED
#define SIMULATION_H_INCLUDED
#include <cmath>
#include <fstream>
using namespace std;
const double PI = 3.1415926535897932385;
const unsigned int WAVELENGTH = 6;
const unsigned int SIZE = 36;
//k = 2 * PI / WAVELENGTH
//K = sqrt(2) * tan(k)
const double K = sqrt(2) * tan(2 * PI / WAVELENGTH);
//do STEP MCS to reach equilibrium
const unsigned int STEP = 20000;
//opening angle of cone in STS
const double ANGLE = PI / 3;
//a spin vector
typedef struct {
	//x^2 + y^2 + z^2 == 1
	double x; //x = sin(theta) * cos(phi)
	double y; //y = sin(theta) * sin(phi)
	double z; //z = cos(theta)
}spin_t;
class simulation {
public:
	//initialize spin states
	simulation(double temperature, double magnetic_field);
	//change T or H
	void set_parameter(double temperature, double magnetic_field);
	//to reach equilibrium
	void equilibrium();
	//do one Monte Carlo Step
	void MCS();
	//output to file
	void output(ofstream &fx, ofstream &fy, ofstream &fz) const;
	//calculate skyrmion density
	double skyrmion_density() const;
	//calculate magnetic moment per site
	double magnetization() const;
	//calculate energy per site
	double energy() const;
private:
	//times of single-flip
	unsigned long times;
	//temperature
	double T;
	//magnetic field
	double H;
	//array to store spin states
	spin_t spin[SIZE][SIZE];
	//get spin state of (i,j)
	inline spin_t getSpin(int i, int j) const;
	//calculate energy change of substitute (i,j) -> trial spin
	inline double energy_change(spin_t ts, unsigned int i, unsigned
		int j) const;
	//try to flip a spin
	inline void single_flip();
};
#endif // SIMULATION_H_INCLUDED