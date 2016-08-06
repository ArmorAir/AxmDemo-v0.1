#include <iostream>
#include <chrono>
#include <iomanip>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <list>
#include <vector>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/timeb.h>
#include <time.h>
#include <Windows.h>
#include <time.h>
//#include ""

using namespace std;

// http://blog.csdn.net/daoyuly/article/details/3947900

int main() {
	
	cout << "AA" << endl;


	//gettimeof
	
	//GetSystemTimeAsFileTime
	//GetLocalTime()
	//GetTickCount()

	LARGE_INTEGER l;
	LARGE_INTEGER s;
	LARGE_INTEGER v;
	LARGE_INTEGER f;
	double elapsedT;
	double t;
	long la;
	long lb;
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

		cout << "e: " << elapsedT << endl;

		l = v;
	}


	system("PAUSE");

	return 0;
}