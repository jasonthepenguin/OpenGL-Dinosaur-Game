#include "messageDispatcher.h"

#include "singleton.h"

void messageDispatcher::discharge(NPC* pReceiver, const telegram& msg) {

	// make sure GameObject has a "handleMessage" function, Lua?
	if (!pReceiver->handleMessage(msg))
		std::cerr << "Message not handled" << std::endl;
}

void messageDispatcher::dispatchMsg(double delay, int sender, int receiver,
	int msg, sol::object additionalInfo) {
	NPC* pReceiver = entityMgr.getEntityFromID(receiver);
	if (pReceiver == NULL) {
		std::cerr << "\nWarning! No Receiver with ID of " << receiver << " found" << std::endl;
		return;
	}
	telegram message(0.0, sender, receiver, msg, additionalInfo);
	if (delay <= 0.0) {
		discharge(pReceiver, message);
	}
	else {
		//double currentTime = timer.getTime();
		double currentTime = LabEngine::getInstance().m_window->getTime();

		message.dispatchTime = currentTime + delay;
		PriorityQ.insert(message);
	}
}


void messageDispatcher::dispatchDelayedMessages() {
	//double currentTime = timer.getTime();
	double currentTime = LabEngine::getInstance().m_window->getTime();


	while (!PriorityQ.empty()
		&& (PriorityQ.begin()->dispatchTime < currentTime)
		&& (PriorityQ.begin()->dispatchTime > 0)) {
		const telegram& message = *PriorityQ.begin();
		NPC* pReceiver = entityMgr.getEntityFromID(message.receiver);
		discharge(pReceiver, message);
		PriorityQ.erase(PriorityQ.begin());
	}
}