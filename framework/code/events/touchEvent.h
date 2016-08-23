#ifndef __AA_TOUCH_EVENT__
#define __AA_TOUCH_EVENT__

#include "event.h"
#include "cross\define.h"
#include "window\touch.h"

class AA_DLL ATouchEvent : public AEvent {

public:

	Touch* getTouch() const;


private:

	Touch* m_touch;



};







#endif