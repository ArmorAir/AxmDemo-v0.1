#ifndef __AA_EVENT__
#define __AA_EVENT__

#include <iostream>
#include <functional>

#include "cross\define.h"


class Listener;

// �¼����󣬿ɶ��䴴�������������䴥��

class AA_DLL AEvent {

public:

	AEvent(void* target);
	AEvent();
	virtual ~AEvent();

	// ����������
	Listener* createListener(std::function<void(AEvent*)> callback, int priority);
	Listener* createListener(std::function<void(AEvent*)> callback);

	// ����
	void trigger();

	// Ŀ��
	void* getTarget() const;

	// �û�����
	void* getUserData() const;
	void setUserData(void* v);

	// ��ǩ
	const char* getTag() const;
	void setTag(const char* v);

	// ֹͣ����
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

// һ��Listener�Ƕ�һ��function����Ĵμ���װ

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
