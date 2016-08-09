#include <iostream>



enum Enum_A
{
	_1,
	_2,
	_3
};

enum Enum_AA
{
	_a,
	_b,
	_c
};


enum class Enum_B
{
	_11,
	_22,
	_33
};

enum class Enum_BB : unsigned char
{
	_111 = 'A',
	_222,
	_333 = 'a'
};


class TypeA {

public:

	enum class Enum_C {
		_aa,
		_bb,
		_cc
	};

};

void testEnum() {

	// enum

	// 1. 向整形的隐式转换: 可比较，可转换
	// 2. 无法指定数据类型: 导致我们无法明确枚举类型所占的内存大小。这种麻烦在结构体当中尤为突出，特别是当我们需要内存对齐和填充处理的时候。
	// 3. enum的作用域: 外部可以直接访问，而不需要使用域运算符

	// 有时候因为enum而削弱了程序的可移植性....

	std::cout << Enum_A::_3 << std::endl;
	std::cout << (Enum_A::_2 == _b) << std::endl;
	std::cout << (Enum_A::_1 == Enum_AA::_c) << std::endl;


	// enum class

	// enum class 和 enum struct 是等价的
	// 1. 与整形之间不会发生隐式类型转换，但是可以强转
	// 2. 指定底层数据类型，但基础类型必须是整形(int/uint)
	// 3. 引入了域，要通过域运算符访问

	std::cout << "==========================" << std::endl;
	std::cout << static_cast<int>(TypeA::Enum_C::_cc) << std::endl; // 2
	std::cout << static_cast<int>(Enum_BB::_222) << static_cast<int>(Enum_BB::_333) << std::endl; // 66, 97
	//std::cout << (Enum_B::_1 == Enum_AA::_c) << std::endl; // false

}