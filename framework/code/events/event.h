#ifndef __AM_AEVENT__
#define __AM_AEVENT__

#if defined(_USRDLL)
	#define AA_DLL     __declspec(dllexport)
#else         /* use a DLL library */
	#define AA_DLL     __declspec(dllimport)
#endif

class AA_DLL AEvent {

public:

	AEvent();
	~AEvent();


	const char* getType();


};





#endif // !__AM_AEVENT__
