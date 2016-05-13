#include <amp.h>
#include <iostream>
using namespace concurrency;

const int size = 5;

void CppAmpMethod() {
	int aCPP[] = { 1, 2, 3, 4, 5 };
	int bCPP[] = { 6, 7, 8, 9, 10 };
	int sumCPP[size] = {0};

	// Create C++ AMP objects.
	array_view<const int, 1> a(size, aCPP);
	array_view<const int, 1> b(size, bCPP);
	array_view<int, 1> sum(size, sumCPP);
	sum.discard_data();

	parallel_for_each(
		// Define the compute domain, which is the set of threads that are created.
		sum.extent,
		// Define the code to run on each thread on the accelerator.
		[=](index<1> idx) restrict(amp)
	{
		sum[idx] = a[idx] + b[idx];
	}
	);

	// Print the results. The expected output is "7, 9, 11, 13, 15".
	for (int i = 0; i < size; i++) {
		std::cout << sum[i] << "\n";
	}
}

int main()
{
	CppAmpMethod();
}

//#include <iostream>  
//#include <amp.h>  
//#include <WinBase.h>  
//#include "Head.h"
//
//#ifdef AMP_TEST_OPEN
//
//#define COUNT 10000
//
//float nickName_GPU[COUNT];
//float nickName_CPU[COUNT];
//
//int main()
//{
//	LARGE_INTEGER freq;
//	LARGE_INTEGER strt;
//	LARGE_INTEGER ed;
//	QueryPerformanceFrequency(&freq);
//	QueryPerformanceCounter(&strt);
//
//	concurrency::array_view<float> myView(COUNT, nickName_GPU); //将数据打入显存  
//	concurrency::parallel_for_each(myView.extent, [=](concurrency::index<1> idx) restrict(amp)
//	{
//		for (int i = 0; i < 40000; i++)
//		{
//			myView[idx] = (myView[idx] + 0.1f) / 2.3f;
//		}
//	});
//
//	myView.synchronize();//显式等待GPU计算完成并将数据打回内存  
//
//	QueryPerformanceCounter(&ed);
//	printf("GPU耗时: %d 毫秒\r\n", (ed.QuadPart - strt.QuadPart) * 1000 / freq.QuadPart);
//	QueryPerformanceCounter(&strt);
//
//#pragma omp parallel  
//	for (int idx = 0; idx < COUNT; idx++)
//	{
//		for (int i = 0; i < 40000; i++)
//		{
//			nickName_CPU[idx] = (nickName_CPU[idx] + 0.1f) / 2.3f;
//		}
//	}
//	QueryPerformanceCounter(&ed);
//	printf("CPU耗时: %d 毫秒\r\n", (ed.QuadPart - strt.QuadPart) * 1000 / freq.QuadPart);
//	for (int idx = 0; idx < COUNT; idx++)
//	{
//		if (nickName_CPU[idx] != nickName_GPU[idx])
//		{
//			puts("CPU和GPU的计算结果不相符！");
//			getchar();
//			return 0;
//		}
//	}
//	puts("测试结束");
//	getchar();
//	return 0;
//}
//
//#endif