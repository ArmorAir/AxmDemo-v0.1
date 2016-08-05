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

using namespace std;

// http://blog.csdn.net/daoyuly/article/details/3947900

int main() {
	
	cout << "AA" << endl;
	
	
	//GetSystemTimeAsFileTime
	//GetLocalTime()
	//GetTickCount()

	LARGE_INTEGER v;
	double t;
	double elapsedT;

	QueryPerformanceCounter(&v);
	t = 1.0 / v.QuadPart;
	for (size_t i = 0; i < 100; i++) {
		QueryPerformanceCounter(&v);

		elapsedT = t * v.QuadPart;

		cout.precision(6);

		cout << fixed << showpoint << elapsedT << endl;

	}


	system("PAUSE");

	return 0;
}