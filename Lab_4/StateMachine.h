#pragma once



#include <iostream>
#include "State.h"

/*

template<class entity_type>
class StateMachine
{

private:
	entity_type* owner; //owner of the FSM
	State<entity_type>* previousState;
	State<entity_type>* currentState;
	State<entity_type>* globalState;

public:
	StateMachine(entity_type* FSMowner)
	{
		owner = FSMowner;
		previousState = NULL;
		currentState = NULL;
		globalState = NULL;
	}

	//use the following methods to intialise the FSM
	void setPreviousState(State<entity_type>* st) { previousState = st; }
	void setCurrentState(State<entity_type>* st) { currentState = st; }
	void setGlobalState(State<entity_type>* st) { globalState = st; }

	void update()const
	{
		if (globalState)
			globalState->Execute(owner);
		if (currentState)
			currentState->Execute(owner);
	}

	void changeState(State<entity_type>* newState)
	{
		previousState = currentState;
		currentState->Exit(owner);
		currentState = newState;
		currentState->Enter(owner);
	}

	void revertToPreviousState()
	{
		currentState = previousState;
	}

	//accessor methods
	State<entity_type>* getPreviousState() { return previousState; }
	State<entity_type>* getCurrentState() { return currentState; }
	State<entity_type>* getGlobalState() { return globalState; }

	//returns true if the current state's type is equal to the type of the
//class passed as a parameter. 
	bool isInState(const State<entity_type>& st)const
	{
		return typeid(*currentState) == typeid(st);
	}

	virtual ~StateMachine() {}


};

*/


#include <sol/sol.hpp>

template<class entity_type>
class StateMachine {
private:
	entity_type* owner;
	sol::table previousState;
	sol::table currentState;
	sol::table globalState;

public:
	StateMachine(entity_type* FSMowner, sol::state& lua_state)
		: owner(FSMowner), lua(lua_state) {}

	void setPreviousState(const std::string& state_name) {
		previousState = lua[state_name];
	}

	void setCurrentState(const std::string& state_name) {
		currentState = lua[state_name];
		currentState["Enter"](owner);

		
	}

	void setGlobalState(const std::string& state_name) {
		globalState = lua[state_name];
	}

	void update() {
		if (globalState.valid()) {
			globalState["Execute"](owner);
		}
		if (currentState.valid()) {
			currentState["Execute"](owner);
		}
	}

	void changeState(const std::string& new_state_name) {
		previousState = currentState;

		if (currentState.valid()) {
			currentState["Exit"](owner);
		}

		currentState = lua[new_state_name];

		if (currentState.valid()) {
			currentState["Enter"](owner);
		}
	}

	void revertToPreviousState() {
		changeState(previousState);
	}

	sol::table getPreviousState() { return previousState; }
	sol::table getCurrentState() { return currentState; }
	sol::table getGlobalState() { return globalState; }

	virtual ~StateMachine() {}

private:
	sol::state& lua;
};