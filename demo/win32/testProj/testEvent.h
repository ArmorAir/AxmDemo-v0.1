#include <iostream>
#include "events\event.h"
#include "events\touchEvent.h"

class ObjA {

public:

	int i = 33;

	void func_m(AEvent* evt) {
		std::cout << "A::func_m::(i)"<< i << std::endl;
	}

	static void func_s(AEvent* evt) {
		
		std::cout << "A::func_s" << std::endl;
	}
};

void testEvent() {
	ObjA* a = new ObjA;

	AEvent* evt = new AEvent();
	
	evt->createListener([](AEvent* v)->void {
		std::cout << "lambda::" << v->getTag() << std::endl;
		//v->stopPropagation();
	});
	evt->createListener(std::bind(&ObjA::func_m, a, std::placeholders::_1), 1);
	evt->createListener(&ObjA::func_s);
	evt->setTag("AAA");
	evt->trigger();
	
	ATouchEvent* touchEvt = new ATouchEvent;
	auto lamb_A = [](AEvent* v)-> void {
		std::cout << v->getTag() << std::endl;
		std::cout << "lamb: " << typeid(v).name() << std::endl;
	};
	touchEvt->createListener(lamb_A);
	touchEvt->setTag("TTT");
	touchEvt->trigger();





}