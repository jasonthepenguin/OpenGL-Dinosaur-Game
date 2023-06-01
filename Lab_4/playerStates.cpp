


#include "playerStates.h"
#include <iostream>



#include "NPC.h"
#include <cstdlib>
#include <ctime>


// idle
void idle::Enter(NPC* npc)
{
	npc->playAnimation("idle");   // setting the animation once
}

void idle::Execute(NPC* npc)
{
	//npc->rotation = glm::mat4(1.0);
	npc->ForwardLook();

	// check if close to player THEN DO BELOW
	if (npc->distanceToPlayer() <= 10)
	{
		npc->npcFSM->changeState(&chase_state::Instance());
	}
	else if (npc->cooldown == false)
	{
		npc->npcFSM->changeState(&wander_state::Instance());
	}
	
}

void idle::Exit(NPC* npc)
{

}

//----------------------------------------------
// chase

void chase::Enter(NPC* npc)
{
	npc->playAnimation("run");
}

void chase::Execute(NPC* npc)
{
	// look at player
	// move towards player
	// if distance is FAR
		// npc->npcFSM->changeState(idle_state);

	npc->lookAtplayer();
	
	if (npc->distanceToPlayer() <= 5) {
		npc->npcFSM->changeState(&attack_state::Instance());
	}
	else if (npc->distanceToPlayer() >= 10)
	{
		npc->npcFSM->changeState(&idle_state::Instance());
	}
	else {
	//	npc->lookAtplayer();
		npc->moveToPlayer();
	}
	//npc->npcFSM->changeState(&attack_state::Instance());

	// if distance is CLOSE
		// npc->getFSM()->changeState(&attack_state::Instance());
}

void chase::Exit(NPC* npc)
{

}


//----------------------------------------------
// attack
void attack::Enter(NPC* npc)
{
	npc->playAnimation("attack");
}

void attack::Execute(NPC* npc)
{
	// DONT MOVE ( so just dont call move towards player )
	// just attack ( npc function to attack or do damage to the player or whatever called here )
	npc->lookAtplayer();
	
	// check if close to player THEN DO BELOW
	if (npc->distanceToPlayer() >= 5)
	{
		npc->npcFSM->changeState(&chase_state::Instance());
	}
	else {
		//npc->lookAtplayer();
	}
	

}

void attack::Exit(NPC* npc)
{

}


// ----------------------
// Wander


void wander::Enter(NPC* npc)
{
	npc->playAnimation("run");
	npc->chooseRandomDirection();
}

void wander::Execute(NPC* npc)
{
	// IF cooldown is true, then swap state back to idle 
	if (npc->cooldown)
	{
		npc->npcFSM->changeState(&idle_state::Instance());
	}
	else {
		npc->wander();
	}
	// else keep on moving in this wander direction

}

void wander::Exit(NPC* npc)
{

}