#include <iostream>
#include "events\event.h"


template<typename T>
void func(T v) {
	
	std::cout << typeid(T).name() << std::endl;
}

void testTemplate() {


	func(AEvent("A"));
	func(ATouchEvent("AA"));




}