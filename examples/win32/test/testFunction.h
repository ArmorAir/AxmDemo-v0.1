#include <iostream>
#include <functional>

void fu(int a) {
	std::cout << "A: " << a << std::endl;
}

class A {
public:
	
	static void sFuncA(int a) {
		std::cout << "sFuncA: " << std::endl;
	}

	void mFuncA(int a) {
		std::cout << "mFuncA: " << this << std::endl;
	}



};

void testFunction() {
	A a;

	std::function<void(int)> listener;
	std::function<void(int)> listener_A;

	listener = std::bind(&A::mFuncA, &a, std::placeholders::_1);
	listener(3);

	listener_A = std::bind(&A::mFuncA, &a, std::placeholders::_1);
	//std::cout << "func::: " << (listener. == listener_A) << std::endl;

	auto lam = [](int v)->void {
		std::cout << "lambda: " << v << std::endl;

	};

	listener = lam;

	listener(6);

	std::cout << &A::sFuncA << std::endl;
	std::cout << &A::mFuncA << std::endl;

	void* ptr_A = nullptr;
	void* ptr_B = &a;

	std::cout << (ptr_A == ptr_B) << std::endl;
}