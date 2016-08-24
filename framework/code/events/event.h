#ifndef __AM_EVENT__
#define __AM_EVENT__

#include <iostream>
#include <functional>

#include "cross\define.h"



class Listener;

// 事件对象，可对其创建侦听，摧毁侦听，及将其触发
class AM_DLL AEvent {

friend class Listener;

public:

	AEvent(void* target);
	AEvent();

	// 创建侦听器
	Listener* createListener(std::function<void(AEvent*)> callback, int priority);
	Listener* createListener(std::function<void(AEvent*)> callback);

	// 触发
	void trigger();

	// 事件目标
	void* getTarget() const;
	void setTarget(void* v);

	// 用户数据
	void* getUserData() const;
	void setUserData(void* v);

	// 停止传播
	void stopPropagation();

	// letgo
	void kill();

protected:
	
	void doDestroyListener(Listener* LA);

	Listener* m_begin;
	Listener* m_end;
	Listener* m_curr;
	void* m_target;
	void* m_userData;
	
};

// 一个Listener是对一个function对象的次级封装
class AM_DLL Listener {

friend class AEvent;

public:

	// 获取事件
	AEvent* getEvent();

	// letgo
	void kill();

protected:

	Listener(AEvent* evt, int priority);

	AEvent* m_event;
	int m_priority;
	Listener* m_prev;
	Listener* m_next;
	bool m_delayed;
	std::function<void(AEvent*)> m_callback;

};



#endif
