#ifndef __AA_EVENT__
#define __AA_EVENT__

#include <iostream>
#include <unordered_map>
//#include <string>
#include <functional>

#include "cross\define.h"




// 提取出EventData概念，每个可触发事件对象，都必须对应一个XXXXEventData，封装包括可触发和侦听的事件类型

class QueueForListener;



class AA_DLL AEvent {

public:


	AEvent( const char* type );
	virtual ~AEvent();

	const char* getType() const;
	void* getTarget() const;
	virtual const char* AEvent::toString() const;

	void doSetType(char* type);
	void doSetTarget( void* target );

protected:

	const char* m_type;
	void* m_target;
};


// 一个Listener是对一个function对象的次级封装

class AA_DLL Listener {

public:
	Listener(int priority);

	std::function<void(AEvent*)> m_callback;
	int m_priority;
	bool m_delayed;
	Listener* m_prev;
	Listener* m_next;
	
};



// 1. 每一个callback产生一个Listener，可通过保存Listener的对象指针来对指定的Listener进行删除
// 2. callback可能包含function对象和target指针，所以不会对callback进行重复检测，也就是说相同的callback可重复生成Listener而不会"覆盖"

class AA_DLL EventDispatcher {

public:

	EventDispatcher();
	EventDispatcher( void* target );
	~EventDispatcher();

	Listener* addEventListener(const char* type, std::function<void(AEvent*)> callback);
	Listener* addEventListener(const char* type, std::function<void(AEvent*)> callback, int priority);
	void removeEventListener(Listener* listener);
	bool hasEventListener(const char* type);
	void dispatchEvent(AEvent* event);
	void dispatch(const char* type);

protected:

	void* m_target;
	std::unordered_map<const char*, QueueForListener*> m_lqList{};

};



////////////////////////
// internal
////////////////////////

class AA_DLL QueueForListener {

public:

	QueueForListener();
	~QueueForListener();

	void doAddListener(Listener* listener);
	void doRemoveListener(Listener* listener);
	void doExecute(AEvent* event);
	void doStopPropagation();
	void doDispose();

private:

	Listener* m_begin;
	Listener* m_end;
	Listener* m_curr;
};





#endif // !__AA_AEVENT__
