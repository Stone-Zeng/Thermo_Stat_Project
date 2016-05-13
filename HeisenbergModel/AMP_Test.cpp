#include <iostream>  
#include <amp.h>  
#include <WinBase.h>  
#include "Head.h"

#ifdef AMP_TEST_ON

#define COUNT 30000

float nickName_GPU[COUNT];
float nickName_CPU[COUNT];

int main()
{
	LARGE_INTEGER freq;
	LARGE_INTEGER strt;
	LARGE_INTEGER ed;
	QueryPerformanceFrequency(&freq);
	QueryPerformanceCounter(&strt);

	concurrency::array_view<float> myView(COUNT, nickName_GPU); //将数据打入显存  
	concurrency::parallel_for_each(myView.extent, [=](concurrency::index<1> idx) restrict(amp)
	{
		for (int i = 0; i < 40000; i++)
		{
			myView[idx] = (myView[idx] + 0.1f) / 2.3f;
		}
	});

	myView.synchronize();//显式等待GPU计算完成并将数据打回内存  

	QueryPerformanceCounter(&ed);
	printf("GPU耗时: %d 毫秒\r\n", (ed.QuadPart - strt.QuadPart) * 1000 / freq.QuadPart);
	QueryPerformanceCounter(&strt);

#pragma omp parallel  
	for (int idx = 0; idx < COUNT; idx++)
	{
		for (int i = 0; i < 40000; i++)
		{
			nickName_CPU[idx] = (nickName_CPU[idx] + 0.1f) / 2.3f;
		}
	}
	QueryPerformanceCounter(&ed);
	printf("CPU耗时: %d 毫秒\r\n", (ed.QuadPart - strt.QuadPart) * 1000 / freq.QuadPart);
	for (int idx = 0; idx < COUNT; idx++)
	{
		if (nickName_CPU[idx] != nickName_GPU[idx])
		{
			puts("CPU和GPU的计算结果不相符！");
			getchar();
			return 0;
		}
	}
	puts("测试结束");
	getchar();
	return 0;
}

#endif