#pragma once

// from topic 10 pdf notes

#include <set>
#include <string>


#include "LabEngine.h"
#include "telegram.h"
#include "NPC.h"

class messageDispatcher
{


private:
	std::set<telegram> PriorityQ;
	void discharge(NPC* pReceiver, const telegram& msg);

public:
	void dispatchMsg(double delay, int sender, int receiver, int msg,
		void* extraInfo = NULL);

	void dispatchDelayedMessages();
	


};

