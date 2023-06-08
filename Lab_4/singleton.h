#pragma once

// Topic 8 lecture notes, Singleton class

template<class T>
class singleton
{
public:
	static T& Instance() {
		static T _instance;
		return _instance;
	}


private:
	singleton();
	~singleton();
	singleton(singleton const&);
	singleton& operator=(singleton const&);
};


#include "dynamicEnum.h"
#include "entityManager.h"
#include "messageDispatcher.h"

#include "TimerManager.h"

typedef singleton<dynamicEnum> message;
typedef singleton<entityManager> entityMan;
typedef singleton<messageDispatcher> messageMan;
typedef singleton<TimerManager> timeMan;

#define fsmMessage message::Instance()
#define entityMgr entityMan::Instance()
#define messageMgr messageMan::Instance()
#define timeMgr timeMan::Instance()