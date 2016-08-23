#ifndef __AA_EVENT__
#define __AA_EVENT__

#include <iostream>
#include <functional>

#include "cross\define.h"


class Listener;

// 事件对象，可对其创建侦听器，或将其触发

class AA_DLL AEvent {

public:

	AEvent(void* target);
	AEvent();
	virtual ~AEvent();

	// 创建侦听器
	Listener* createListener(std::function<void(AEvent*)> callback, int priority);
	Listener* createListener(std::function<void(AEvent*)> callback);

	// 触发
	void trigger();

	// 目标
	void* getTarget() const;

	// 用户数据
	void* getUserData() const;
	void setUserData(void* v);

	// 标签
	const char* getTag() const;
	void setTag(const char* v);

	// 停止传播
	void stopPropagation();
	void dispose();

protected:
	
	Listener* m_begin;
	Listener* m_end;
	Listener* m_curr;
	void* m_target;
	void* m_userData;
	const char* m_tag;

};

// 一个Listener是对一个function对象的次级封装

class AA_DLL Listener {

public:



private:

	friend class AEvent;

	Listener(int priority);

	std::function<void(AEvent*)> m_callback;
	int m_priority;
	bool m_delayed;
	Listener* m_prev;
	Listener* m_next;

};



#endif
