#ifndef __AM_WIN32_DEFINE__
#define __AM_WIN32_DEFINE__



#if defined(_USRDLL)
	#define AM_DLL __declspec(dllexport)
#else
	#define AM_DLL __declspec(dllimport)
#endif










#endif