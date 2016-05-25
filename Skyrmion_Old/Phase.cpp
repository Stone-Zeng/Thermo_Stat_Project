#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "simulation.h"

using namespace std;

//for any (t, h):
//calculate M different objects
//record N data for one object

const int M = 10; //10
const int N = 100; //100
void output(simulation &model, double t, double h) {
	ostringstream fn;
	fn << static_cast<int>(t * 100) << "-" << static_cast<int>(h *
		100) << ".s";
	ostringstream fnx;
	fnx << fn.str() << "x";
	ofstream fx(fnx.str().c_str());
	ostringstream fny;
	fny << fn.str() << "y";
	ofstream fy(fny.str().c_str());
	ostringstream fnz;
	fnz << fn.str() << "z";
	ofstream fz(fnz.str().c_str());
	model.output(fx, fy, fz);
	fx.close();
	fy.close();
	fz.close();
}
void calc(double t, double h, ofstream &fp) {
	//lowest T = 0.01
	if (t < 0.01)
		t = 0.01;
	cout << setprecision(3)
		<< "(T=" << t << ", H=" << h << ") Calculating ";
	cout.flush();
	long start_time = time(NULL);
	double magnetization = 0, skyrmion_density = 0, energy = 0;
	double m_fluctuation = 0, s_fluctuation = 0, e_fluctuation = 0;
	double Mtot = 0, Stot = 0, Etot = 0,
		M2tot = 0, S2tot = 0, E2tot = 0;
	double m, s, e;
	for (int i = 0; i < M; i++) {
		simulation *obj = new simulation(t, h);
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < 5; k++)
				obj->MCS();
			m = obj->magnetization();
			s = obj->skyrmion_density();
			e = obj->energy();
			Mtot += m; M2tot += m * m;
			Stot += s; S2tot += s * s;
			Etot += e; E2tot += e * e;
			magnetization += m;
			skyrmion_density += s;
			energy += e;
		}
		if (i == 0)
			output(*obj, t, h);
		delete obj;
		cout << ".";
		cout.flush();
	}
	magnetization /= M * N;
	skyrmion_density /= M * N;
	energy /= M * N;
	Mtot /= M * N; M2tot /= M * N;
	Stot /= M * N; S2tot /= M * N;
	Etot /= M * N; E2tot /= M * N;
	m_fluctuation = M2tot - Mtot * Mtot;
	s_fluctuation = S2tot - Stot * Stot;
	e_fluctuation = E2tot - Etot * Etot;
	cout << " Done (" << time(NULL) - start_time << "s)" << endl
		<< endl << setprecision(8)
		<< "Magnetization: " << setw(12) << magnetization
		<< " (Fluctuation: " << sqrt(m_fluctuation) << ")" << endl
		<< "Skyrmion density: " << setw(12) << skyrmion_density
		<< " (Fluctuation: " << sqrt(s_fluctuation) << ")" << endl
		<< "Energy: " << setw(12) << energy
		<< " (Fluctuation: " << sqrt(e_fluctuation) << ")" << endl
		<< endl;
	fp << t << "\t" << h << "\t"
		<< magnetization << "\t" << skyrmion_density << "\t" << energy
		<< "\t"
		<< m_fluctuation << "\t" << s_fluctuation << "\t" <<
		e_fluctuation << "\n";
	fp.flush();
}
int main() {
	//SkX (0.1, 2.00)
	//H (0.03, 0)
	//FM (0.1, 4.0)
	//Sweep:
	//T from 0.0 to 2.0, step 0.1
	//H from 0.0 to 4.0, step 0.1
	double T_begin, T_end, T_step;
	double H_begin, H_end, H_step;
	cout << "[Enter the range of sweep (begin, end, step)]" << endl
		<< endl;
	cout << "Temperature (e.g. 0.0 2.0 0.1) : ? ";
	cout.flush();
	cin >> T_begin >> T_end >> T_step;
	cout << "Magnetic Field (e.g. 0.0 4.0 0.1) : ? ";
	cout.flush();
	cin >> H_begin >> H_end >> H_step;
	cout << endl
		<< "===================================================" <<
		endl
		<< endl
		<< "Wavelength: " << WAVELENGTH << endl
		<< "Lattice Size: " << SIZE << "*" << SIZE << endl
		<< "DM Interaction Const: " << K << endl
		<< endl
		<< "[Sweeping...]" << endl
		<< endl << fixed << setprecision(3)
		<< "T from " << T_begin << " to " << T_end << ", step " <<
		T_step << endl
		<< "H from " << H_begin << " to " << H_end << ", step " <<
		H_step << endl
		<< endl;
	ofstream fphase("all.phase", ios::app);
	srand(static_cast<unsigned>(time(NULL)));
	int T_sign = T_step > 0 ? 1 : -1;
	int H_sign = H_step > 0 ? 1 : -1;
	for (double t = T_begin; t * T_sign <= T_end * T_sign; t +=
		T_step)
		for (double h = H_begin; h * H_sign <= H_end * H_sign; h +=
			H_step)
			calc(t, h, fphase);
	fphase << "\n";
	fphase.close();
	cout << endl << ">> Sweep Complete!" << endl << endl;
	return 0;
}