#include <fstream>
#include <cstdlib>
#include <cmath>
#include "simulation.h"

using namespace std;

//p chance to return true
inline bool test(double p) {
	double ran = static_cast<double>(rand()) / RAND_MAX;
	return ran < p;
}
//get a random number between -range/2 and +range/2
inline double random(double range) {
	double ran = static_cast<double>(rand()) / RAND_MAX;
	return (ran - 0.5) * range;
}
//get arbitrary trial step (ATS)
inline spin_t ATS() {
	double theta, phi;
	theta = PI * static_cast<double>(rand()) / RAND_MAX;
	phi = 2.0 * PI * static_cast<double>(rand()) / RAND_MAX;
	spin_t rt;
	rt.x = sin(theta) * cos(phi);
	rt.y = sin(theta) * sin(phi);
	rt.z = cos(theta);
	return rt;
}
//get small trial step (STS)
inline spin_t STS(spin_t sp) {
	double theta, phi;
	theta = acos(sp.z);
	if (sp.z < 0.9)
		phi = atan(sp.y / sp.x) + random(ANGLE / sin(theta));
	else
		phi = random(2 * PI);
	theta += random(ANGLE);
	spin_t rt;
	rt.x = sin(theta) * cos(phi);
	rt.y = sin(theta) * sin(phi);
	rt.z = cos(theta);
	return rt;
}
//get a arbitrary rotation (in x-y plane) trial step (RTS)
inline spin_t RTS(spin_t sp) {
	spin_t rt;
	double phi, xy;
	phi = 2.0 * PI * static_cast<double>(rand()) / RAND_MAX;
	xy = sqrt(1 - sp.z * sp.z);
	rt.x = xy * cos(phi);
	rt.y = xy * sin(phi);
	rt.z = sp.z;
	return rt;
}
//////////////////////////////////////////////////////
// class simulation
//////////////////////////////////////////////////////
//initialize
simulation::simulation(double temperature, double magnetic_field)
	:times(0) {
	//set spin states randomly
	for (unsigned int i = 0; i < SIZE; i++)
		for (unsigned int j = 0; j < SIZE; j++)
			spin[i][j] = ATS();
	set_parameter(temperature, magnetic_field);
	equilibrium();
}
//change T or H
void simulation::set_parameter(double temperature, double
	magnetic_field) {
	T = temperature;
	H = magnetic_field;
}
//to reach equilibrium
void simulation::equilibrium() {
	for (unsigned int k = 0; k < STEP; k++)
		MCS();
}
//do one Monte Carlo Step
void simulation::MCS() {
	for (unsigned int k = 0; k < SIZE * SIZE; k++)
		single_flip();
}
//calculate skyrmion density
double simulation::skyrmion_density() const {
	//skyrmion density = S dot ( (partial S / partial x) cross (partial S / partial y) )
	double ans = 0;
	for (unsigned int i = 0; i < SIZE; i++) {
		for (unsigned int j = 0; j < SIZE; j++) {
			double Sx = spin[i][j].x, Sy = spin[i][j].y, Sz =
				spin[i][j].z,
				Lx = getSpin(i - 1, j).x, Ly = getSpin(i - 1, j).y, Lz =
				getSpin(i - 1, j).z,
				Rx = getSpin(i + 1, j).x, Ry = getSpin(i + 1, j).y, Rz =
				getSpin(i + 1, j).z,
				Ux = getSpin(i, j - 1).x, Uy = getSpin(i, j - 1).y, Uz =
				getSpin(i, j - 1).z,
				Dx = getSpin(i, j + 1).x, Dy = getSpin(i, j + 1).y, Dz =
				getSpin(i, j + 1).z;
			ans += Sz*((Ly - Ry)*(Dx - Ux) - (Lx - Rx)*(Dy - Uy)) +
				Sy*(-((Lz - Rz)*(Dx - Ux)) + (Lx - Rx)*(Dz - Uz)) +
				Sx*((Lz - Rz)*(Dy - Uy) - (Ly - Ry)*(Dz - Uz));
		}
	}
	ans /= 16 * PI;
	return -ans / (WAVELENGTH * WAVELENGTH); //skyrmion number per d ^ 2
}
//calculate magnetic moment per site
double simulation::magnetization() const {
	double ans = 0;
	for (unsigned int i = 0; i < SIZE; i++)
		for (unsigned int j = 0; j < SIZE; j++)
			ans += spin[i][j].z;
	return ans / (SIZE * SIZE);
}
//calculate energy per site
double simulation::energy() const {
	double ans = 0;
	for (unsigned int i = 0; i < SIZE; i++) {
		for (unsigned int j = 0; j < SIZE; j++) {
			double Sx = spin[i][j].x, Sy = spin[i][j].y, Sz =
				spin[i][j].z,
				Rx = getSpin(i + 1, j).x, Ry = getSpin(i + 1, j).y, Rz =
				getSpin(i + 1, j).z,
				Dx = getSpin(i, j + 1).x, Dy = getSpin(i, j + 1).y, Dz =
				getSpin(i, j + 1).z;
			ans += -(H * Sz)
				- Sx * (Rx + Dx) - Sy * (Ry + Dy) - Sz * (Rz + Dz)
				- K * (Sx * (-Dz) + Sy * (Rz) +Sz * (Dx - Ry));
		}
	}
	return ans / (SIZE * SIZE);
}
//output to file
void simulation::output(ofstream &fx, ofstream &fy, ofstream &fz)
const {
	for (unsigned int i = 0; i < SIZE; i++) {
		for (unsigned int j = 0; j < SIZE; j++) {
			spin_t sp = getSpin(i, j);
			fx << sp.x << "\t";
			fy << sp.y << "\t"; fz << sp.z << "\t";
		}
		fx << "\n";
		fy << "\n";
		fz << "\n";
	}
}
//get spin state of (i,j)
spin_t simulation::getSpin(int i, int j) const {
	//period boundary condition (PBC)
	i = i % SIZE, j = j % SIZE;
	return spin[i][j];
}
//calculate energy change of substitute (i,j) -> trial spin
double simulation::energy_change(spin_t ts, unsigned int i, unsigned
	int j) const {
	//H = - J * S dot S' - K * S cross S' dot direction(S,S') - H dot S
		double Sx = ts.x - spin[i][j].x, Sy = ts.y - spin[i][j].y, Sz =
		ts.z - spin[i][j].z,
		Lx = getSpin(i - 1, j).x, Ly = getSpin(i - 1, j).y, Lz =
		getSpin(i - 1, j).z,
		Rx = getSpin(i + 1, j).x, Ry = getSpin(i + 1, j).y, Rz =
		getSpin(i + 1, j).z,
		Ux = getSpin(i, j - 1).x, Uy = getSpin(i, j - 1).y, Uz =
		getSpin(i, j - 1).z,
		Dx = getSpin(i, j + 1).x, Dy = getSpin(i, j + 1).y, Dz =
		getSpin(i, j + 1).z;
	return -(H * Sz)
		- Sx * (Dx + Lx + Rx + Ux) - Sy * (Dy + Ly + Ry + Uy) - Sz *
		(Dz + Lz + Rz + Uz)
		- K * (Sx * (Uz - Dz) + Sy * (Rz - Lz) + Sz * (Dx + Ly - Ry
			- Ux));
}
//try to flip
void simulation::single_flip() {
	//choose a random lattice site (i,j)
	unsigned int i = rand() % SIZE;
	unsigned int j = rand() % SIZE;
	spin_t ts;
	switch (times++ % 3) {
		case 0:
			ts = ATS();
			break;
		case 1:
			ts = RTS(spin[i][j]);
			break;
		case 2:
			ts = STS(spin[i][j]);
			break;
	}
	double dE = energy_change(ts, i, j);
	if (dE > 0)
		if (test(exp(-dE / T)) == false)
			return; //rejection
	spin[i][j] = ts; //acception
}