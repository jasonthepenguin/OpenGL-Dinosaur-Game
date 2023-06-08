#pragma once

#include <iostream>
#include <sol/sol.hpp>

/**
 * @brief Generic state machine class template.
 *
 * @tparam entity_type The type of the owner entity that uses the state machine.
 */
template<class entity_type>
class StateMachine {
private:
    entity_type* owner;             /**< Pointer to the owner entity. */
    sol::table previousState;       /**< Previous state of the state machine. */
    sol::table currentState;        /**< Current state of the state machine. */
    sol::table globalState;         /**< Global state of the state machine. */
    sol::state& lua;                /**< Reference to the Lua state. */

public:
    /**
     * @brief Constructs a new StateMachine object.
     *
     * @param FSMowner Pointer to the owner entity that uses the state machine.
     * @param lua_state Reference to the Lua state.
     */
    StateMachine(entity_type* FSMowner, sol::state& lua_state)
        : owner(FSMowner), lua(lua_state) {}

    /**
     * @brief Sets the previous state of the state machine.
     *
     * @param state_name The name of the previous state.
     */
    void setPreviousState(const std::string& state_name) {
        previousState = lua[state_name];
    }

    /**
     * @brief Sets the current state of the state machine.
     *
     * @param state_name The name of the current state.
     */
    void setCurrentState(const std::string& state_name) {
        currentState = lua[state_name];
        //currentState["Enter"](owner);
    }

    /**
     * @brief Sets the global state of the state machine.
     *
     * @param state_name The name of the global state.
     */
    void setGlobalState(const std::string& state_name) {
        globalState = lua[state_name];
    }

    /**
     * @brief Updates the state machine.
     *
     * Executes the global state and the current state if they are valid.
     */
    void update() {
        if (globalState.valid()) {
            globalState["Execute"](owner);
        }
        if (currentState.valid()) {
            currentState["Execute"](owner);
        }
    }

    /**
     * @brief Changes the state of the state machine.
     *
     * @param new_state_name The name of the new state to change to.
     */
    void changeState(const std::string& new_state_name) {
        previousState = currentState;

        //std::cout << "We are now in state: " << new_state_name << std::endl;

        if (currentState.valid()) {
            currentState["Exit"](owner);
        }

        currentState = lua[new_state_name];

        if (currentState.valid()) {
            currentState["Enter"](owner);
        }
    }

    /**
     * @brief Reverts to the previous state of the state machine.
     */
    void revertToPreviousState() {
        changeState(previousState);
    }

    /**
     * @brief Handles a message sent to the state machine.
     *
     * @param msg The message to handle.
     * @return True if the current state handles the message, false otherwise.
     */
    bool handleMessage(const telegram& msg) {
        /*
        if (currentState.valid() && currentState->onMessage(owner, msg))
        {
            return true;
        }
        */
        if (currentState.valid()) {
            currentState["onMessage"](owner, msg);
            return true;
        }
        return false;
    }

    /**
     * @brief Gets the previous state of the state machine.
     *
     * @return sol::table The previous state.
     */
    sol::table getPreviousState() { return previousState; }

    /**
     * @brief Gets the current state of the state machine.
     *
     * @return sol::table The current state.
     */
    sol::table getCurrentState() { return currentState; }

    /**
     * @brief Gets the global state of the state machine.
     *
     * @return sol::table The global state.
     */
    sol::table getGlobalState() { return globalState; }

    /**
     * @brief Destroys the StateMachine object.
     */
    virtual ~StateMachine() {}

private:
    // Private member variables and functions
};
