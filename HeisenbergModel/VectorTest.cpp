//Only used for test.
//Must be commented out after test for I have used main() here.

#include "Function.h"
#include "MyVector.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
	srand(time(NULL));

	MyVector v1, v2, v3;
	cout << "v1= " << v1 << endl
		<< "v2= " << v2 << endl
		<< "v3= " << v3 << endl << endl;

	v1.initialize();
	v2.initialize();
	v3.initialize();

	cout << "v1= " << v1 << endl
		<< "v2= " << v2 << endl
		<< "v3= " << v3 << endl << endl;

	cout << v1.dot(v1) << endl
		<< v2.dot(v2) << endl
		<< v3.dot(v3) << endl << endl;

	cout << v1.cross(v2) << endl
		<< v2.cross(v1) << endl
		<< v3.cross(v3) << endl << endl;

	MyVector vec[3];
	cout << vec[1] << endl;
	return 0;
}