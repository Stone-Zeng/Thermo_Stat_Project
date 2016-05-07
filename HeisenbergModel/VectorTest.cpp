////Only used for test.
////Must be commented out after test for I have used main() here.
//
//#include "Function.h"
//#include "MyVector.h"
//#include <iostream>
//#include <cstdlib>
//#include <ctime>
//using namespace std;
//
//const long leng = 5000000;
//MyVector vecA[leng], vecB[leng], vecC[leng], vecD[leng];
//double r1[leng], r2[leng];
//
//int main()
//{
//	//srand((unsigned int) time(NULL));
//
//	MyVector v1, v2, v3;
//	cout << "v1= " << v1 << endl
//		<< "v2= " << v2 << endl
//		<< "v3= " << v3 << endl << endl;
//	
//	v1.initialize();
//	v2.initialize();
//	v3.initialize();
//	
//	cout << "v1= " << v1 << endl
//		<< "v2= " << v2 << endl
//		<< "v3= " << v3 << endl << endl;
//	
//	//cout << "v1+v2= " << v1.plus(v2) << endl
//	//	<< "v2-v3= " << v2.minus(v3) << endl
//	//	<< "v1*10.4= " << v1.times(10.4) << endl
//	//	<< "v2/-6=" << v2.divide(-6) << endl << endl;
//	
//	cout << v1.dot(v1) << endl
//		<< v2.dot(v2) << endl
//		<< v3.dot(v3) << endl << endl;
//	
//	cout << v1.cross(v2) << endl
//		<< v2.cross(v1) << endl
//		<< v3.cross(v3) << endl << endl;
//
//	for (auto i = 0; i != leng; ++i)
//	{
//		//vecA[i].initialize();
//		//vecB[i].initialize();
//		vecC[i] = vecA[i].cross(vecB[i]);
//		r1[i] = vecA[i].dot(vecB[i]);
//	}
//	return 0;
//}