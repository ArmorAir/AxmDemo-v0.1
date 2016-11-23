#ifndef __AM_EVENT__
#define __AM_EVENT__

#include <iostream>
#include <functional>

#include "Lv_1\cross\c-define.h"



class Listener;

typedef unsigned int ListenerID;

// 事件对象，可创建侦听，以及自我触发
class AM_DLL AEvent {

friend class Listener;

public:

	AEvent(void* target, const char* name);
	
	ListenerID addListener(std::function<void(AEvent*)> callback, int priority);
	ListenerID addListener(std::function<void(AEvent*)> callback);

	void removeListener(ListenerID lid);

	void* getTarget() const;

	const char* getName() const;
	
	void* getUserData() const;
	void setUserData(void* v);
	
	void stopPropagation();

	// letgo
	void kill();

	void doTrigger();
	
	void doReset();

	void doDispose();


protected:
	
	void doDestroyListener(Listener* LA);

	Listener* m_begin;
	Listener* m_end;
	Listener* m_curr;
	void* m_target;
	const char* m_name;
	void* m_userData;
	int m_count;
	
};

// 一个Listener是对一个function对象的次级封装
class AM_DLL Listener {

friend class AEvent;

public:
	
	// letgo
	void kill();

protected:

	Listener(std::function<void(AEvent*)> callback, int priority, ListenerID lid);

	std::function<void(AEvent*)> m_callback;
	int m_priority;
	ListenerID m_id;
	bool m_delayed;
	Listener* m_prev;
	Listener* m_next;
	
};



#endif
