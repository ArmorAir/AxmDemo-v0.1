
#include <string>


// char16_t��C++11�ĵ�������һ���¹ؼ��֣������洢unicode�ַ���������ר�õġ�


void testString() {

	// memchr

	using namespace std;

	string s("abcde");
	u16string sA(u"�ط�");
	s.reserve(10);
	char cArr[]("bbbbb");
	const char* cPtr_A = s.c_str();
	const char* cPtr_B = cArr;
	//const char cArr_B[] = cPtr_A;

	

	cout << sA.c_str() << endl;
	//int i = atoi(c);
	cout << cPtr_A << "..." << (cPtr_A[4] == '\0') << endl;

	s.begin(); s.cbegin();


	cout << typeid(cArr).name() << "..." << strlen(cArr) << "..." << cArr << "..." << &cArr << endl;
	cout << typeid(cPtr_A).name() << "..." << strlen(cPtr_A) << "..." << cPtr_A << "..." << &cPtr_A << endl;
	cout << typeid(cPtr_B).name() << "..." << strlen(cPtr_B) << "..." << cPtr_B << "..." << &cPtr_B << endl;

	cout << "==============================" << endl;

	//s[2] = 'b';
	cout << s.size() << "..." << s[2] << "..." << s.front() << endl;
	cout << (s.find('h') == -1) << endl;
	cout << s.find_first_not_of("adcd") << endl;
	

	/////////////////////////////////
	// c-str
	/////////////////////////////////

	//s.find()

	// memcmp

	//getline()




	//memcpy



		// memmove



		// memset






}
