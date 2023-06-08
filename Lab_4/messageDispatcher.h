/**
 * @file messageDispatcher.h
 * @brief Defines the messageDispatcher class responsible for dispatching messages to NPCs.
 */

#pragma once

#include <set>  ///< Required for using std::set
#include <string>  ///< Required for using std::string

#include "LabEngine.h"  ///< Required for using LabEngine class
#include "telegram.h"  ///< Required for using telegram class
#include "NPC.h"  ///< Required for using NPC class

 /**
  * @class messageDispatcher
  * @brief Handles the dispatching of messages to NPCs.
  */
class messageDispatcher
{
private:
    std::set<telegram> PriorityQ;  ///< Priority queue to store the messages to be dispatched

    /**
     * @brief Discharges a message to the specified receiver NPC.
     * @param pReceiver Pointer to the receiver NPC.
     * @param msg The telegram message to be discharged.
     */
    void discharge(NPC* pReceiver, const telegram& msg);

public:
    /**
     * @brief Dispatches a message with optional delay to the specified receiver.
     * @param delay The delay in seconds before the message is dispatched.
     * @param sender The ID of the sending entity.
     * @param receiver The ID of the receiving entity.
     * @param msg The ID of the message.
     * @param additionalInfo Additional information related to the message.
     */
    void dispatchMsg(double delay, int sender, int receiver, int msg,
        sol::object additionalInfo);

    /**
     * @brief Dispatches any delayed messages that are due.
     */
    void dispatchDelayedMessages();
};
