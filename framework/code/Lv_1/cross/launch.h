#ifndef __AM_LAUNCH__
#define __AM_LAUNCH__

#include "c-define.h"
#include "Lv_2\geom\size.h"


class AM_DLL ILauncher {

public:

	virtual ASize normalizedSize() = 0;

	virtual void onLaunch() = 0;
	


}





#endif