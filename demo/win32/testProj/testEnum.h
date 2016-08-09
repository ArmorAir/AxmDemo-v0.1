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

	// 1. �����ε���ʽת��: �ɱȽϣ���ת��
	// 2. �޷�ָ����������: ���������޷���ȷö��������ռ���ڴ��С�������鷳�ڽṹ�嵱����Ϊͻ�����ر��ǵ�������Ҫ�ڴ�������䴦���ʱ��
	// 3. enum��������: �ⲿ����ֱ�ӷ��ʣ�������Ҫʹ���������

	// ��ʱ����Ϊenum�������˳���Ŀ���ֲ��....

	std::cout << Enum_A::_3 << std::endl;
	std::cout << (Enum_A::_2 == _b) << std::endl;
	std::cout << (Enum_A::_1 == Enum_AA::_c) << std::endl;


	// enum class

	// enum class �� enum struct �ǵȼ۵�
	// 1. ������֮�䲻�ᷢ����ʽ����ת�������ǿ���ǿת
	// 2. ָ���ײ��������ͣ����������ͱ���������(int/uint)
	// 3. ��������Ҫͨ�������������

	std::cout << "==========================" << std::endl;
	std::cout << static_cast<int>(TypeA::Enum_C::_cc) << std::endl; // 2
	std::cout << static_cast<int>(Enum_BB::_222) << static_cast<int>(Enum_BB::_333) << std::endl; // 66, 97
	//std::cout << (Enum_B::_1 == Enum_AA::_c) << std::endl; // false

}