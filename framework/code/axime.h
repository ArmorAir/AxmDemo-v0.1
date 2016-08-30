#ifndef __AM_AXIME__
#define __AM_AXIME__


#include "logging\log.h"
#include "window\window.h"
#include "window\keyboard.h"
#include "window\touch.h"


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