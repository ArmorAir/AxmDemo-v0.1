#ifndef __AM_EVENT__
#define __AM_EVENT__

#include <iostream>
#include <functional>

#include "cross\define.h"



class Listener;

// �¼����󣬿ɶ��䴴���������ݻ������������䴥��
class AM_DLL AEvent {

friend class Listener;

public:

	AEvent(void* target);
	AEvent();

	// ����������
	Listener* createListener(std::function<void(AEvent*)> callback, int priority);
	Listener* createListener(std::function<void(AEvent*)> callback);

	// ����
	void trigger();

	// �¼�Ŀ��
	void* getTarget() const;
	void setTarget(void* v);

	// �û�����
	void* getUserData() const;
	void setUserData(void* v);

	// ֹͣ����
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

// һ��Listener�Ƕ�һ��function����Ĵμ���װ
class AM_DLL Listener {

friend class AEvent;

public:

	// ��ȡ�¼�
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
