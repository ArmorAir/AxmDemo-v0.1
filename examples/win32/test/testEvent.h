#include <iostream>
#include "Lv_0\events\event.h"
#include "Lv_1\events\touchEvent.h"

class ObjA {

public:

	ObjA() {
		m_evt->createListener(std::bind(&ObjA::funcSelf, this, std::placeholders::_1));
	}

	int i = 33;
	ATouchEvent* m_evt = new ATouchEvent;

	void func_m(AEvent* evt) {
		std::cout << "A::func_m::(i)"<< i << std::endl;
	}

	static void func_s(AEvent* evt) {
		
		std::cout << "A::func_s" << std::endl;
	}

	virtual void funcSelf(AEvent* evt) {
		std::cout << "self: " << typeid(m_evt).name() << std::endl;
	}
};

class ObjB : public ObjA {

public:

	static void func_s(AEvent* evt) {
		//ObjA::func_s(evt);

		std::cout << "B::func_s" << std::endl;
	}

	virtual void funcSelf(AEvent* evt) {
		

		ObjA::funcSelf(evt);

		ObjA::func_m(evt);
		
		std::cout << "ObjB..." << std::endl;
	}


};

void testEvent() {
	Listener* LA = nullptr;
	Listener* LB = nullptr;
	AEvent* tmpEvt = nullptr;

	ObjA* a = new ObjA;
	ObjB* b = new ObjB;

	AEvent* evt = new AEvent();
	
	LA = evt->createListener([](AEvent* v)->void {
		std::cout << "lambda::" << static_cast<const char*>(v->getUserData()) << std::endl;
		//v->stopPropagation();
	});
	evt->createListener(std::bind(&ObjA::func_m, a, std::placeholders::_1), 1);
	evt->createListener(&ObjB::func_s);
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
	touchEvt->setUserData("XXXXXXXXXXXXXXXXX");
 	touchEvt->trigger();

	tmpEvt = LA->getEvent();

	LA->kill();

	evt->kill();


	a->m_evt->trigger();

	//evt->trigger();

	std::cout << "===============================" << std::endl;

	b->i = 44;
	b->funcSelf(evt);


	

	//LA->kill();

}