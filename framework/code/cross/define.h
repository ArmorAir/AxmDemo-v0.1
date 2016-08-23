#ifndef AM_DEFINE
#define AM_DEFINE



#if defined(_USRDLL)
	#define AM_DLL __declspec(dllexport)
#else
	#define AM_DLL __declspec(dllimport)
#endif








#endif
