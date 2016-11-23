#ifndef __AM_AXIME__
#define __AM_AXIME__


#include "Lv_1\logging\log.h"
#include "Lv_1\window\window.h"
#include "Lv_1\window\keyboard.h"
#include "Lv_1\window\touch.h"


// 最常用ui组件
// - button
// - check
// - radio

// - progress
// - slider

// 



class Axime {

public:


	static void startup();

	static LogMachine* getLog();

	static AWindow* getWindow();
	static KeyboardManager* getKeyboard();
	static TouchManager* getTouch();





private:






};



#endif