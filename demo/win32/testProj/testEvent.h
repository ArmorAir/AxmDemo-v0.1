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
	Listener* LA = nullptr;
	Listener* LB = nullptr;
	AEvent* tmpEvt = nullptr;

	ObjA* a = new ObjA;

	AEvent* evt = new AEvent();
	
	LA = evt->createListener([](AEvent* v)->void {
		std::cout << "lambda::" << static_cast<const char*>(v->getUserData()) << std::endl;
		//v->stopPropagation();
	});
	evt->createListener(std::bind(&ObjA::func_m, a, std::placeholders::_1), 1);
	evt->createListener(&ObjA::func_s);
	evt->setUserData("AAA");
	evt->trigger();


	std::cout << "===============================" << std::endl;
	

	ATouchEvent* touchEvt = new ATouchEvent;
	auto lamb_A = [](AEvent* v)-> void {
		std::cout << static_cast<const char*>(v->getUserData()) << std::endl;

		std::cout << "lambda: " << typeid(v).name() << std::endl;
		std::cout << "lambda: " << typeid(static_cast<ATouchEvent*>(v)).name() << std::endl;
	};
	LB = touchEvt->createListener(lamb_A);
	touchEvt->setUserData("TTT");
 	touchEvt->trigger();

	tmpEvt = LA->getEvent();

	LA->kill();

	evt->kill();
	//evt->trigger();


	//LA->kill();

}