#pragma once

// From the Lecture 10 pdf notes

#include <iostream>
#include <cmath>

#include <sol/sol.hpp>

struct telegram
{
	// messages can be dispatched immediately (0.0) or delayed for a specific
	// amount of time. If a delay is neccessary this field is stamped 
	// with the time the message should be dispatched.
	double dispatchTime;
	int sender; //the entity that sent this telegram
	int receiver; //the entity that is to receive this telegram
	// the message itself. These are all enumerated 
	// in the file "MessageTypes.h"
	int msg;
	// any additional information that may accompany the message
	//void* extraInfo;
	sol::object extraInfo;

	telegram() : dispatchTime(-1), sender(-1), receiver(-1), msg(-1) {}


	telegram(double time, int sender, int receiver, int msg, sol::object info) :
		dispatchTime(time), sender(sender), receiver(receiver),
		msg(msg), extraInfo(info) {}
	
		
		
		// these telegrams will be stored in a priority queue. Therefore the >
		// operator needs to be overloaded so that the PQ can sort the telegrams by
		// time priority. Note how the times must be smaller than SmallestDelay
		// before two telegrams are considered the same.
		static constexpr double smallestDelay = 0.25;
	
};


inline bool operator==(const telegram& t1, const telegram& t2) {
	return (fabs(t1.dispatchTime - t2.dispatchTime) < telegram::smallestDelay)
		&& (t1.sender == t2.sender)
		&& (t1.receiver == t2.receiver)
		&& (t1.msg == t2.msg);
}

inline bool operator<(const telegram& t1, const telegram& t2) {
	if (t1 == t2) { return false; }
	else {
		return (t1.dispatchTime < t2.dispatchTime);
	}
}