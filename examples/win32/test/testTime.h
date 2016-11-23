#include <iostream>
#include <Windows.h>



void testTime() {




	LARGE_INTEGER l;
	LARGE_INTEGER s;
	LARGE_INTEGER v;
	LARGE_INTEGER f;
	double elapsedT;
	//cout << elapsedT << endl;
	//Sleep(100);

	QueryPerformanceFrequency(&f);
	QueryPerformanceCounter(&l);
	s = l;


	//cout << l.QuadPart / 365 / 12 / 24 / 60 << endl;
	//t = 1.0 / f.QuadPart;

	for (size_t i = 0; i < 15; i++) {

		Sleep(10);

		QueryPerformanceCounter(&v);
		elapsedT = (double)(v.QuadPart - l.QuadPart) / f.QuadPart;

		//cout.precision(6);

		std::cout << "e: " << elapsedT << std::endl;

		l = v;
	}



}