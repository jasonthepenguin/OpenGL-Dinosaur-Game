#pragma once



#include "singleton.h"
#include "State.h"


class NPC;

class idle : public State<NPC>
{
public:
	void Enter(NPC* dude);
	void Execute(NPC* dude);
	void Exit(NPC* dude);

};


class chase : public State<NPC>
{
public:
	void Enter(NPC* dude);
	void Execute(NPC* dude);
	void Exit(NPC* dude);

};

class attack : public State<NPC>
{
public:
	void Enter(NPC* dude);
	void Execute(NPC* dude);
	void Exit(NPC* dude);

};


typedef singleton<idle> idle_state;
typedef singleton<chase> chase_state;
typedef singleton<attack> attack_state;


