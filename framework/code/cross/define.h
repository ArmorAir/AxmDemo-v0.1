#ifndef AA_DEFINE
#define AA_DEFINE



#if defined(_USRDLL)
	#define AA_DLL     __declspec(dllexport)
#else
	#define AA_DLL     __declspec(dllimport)
#endif








#endif // !AA_DEFINE
