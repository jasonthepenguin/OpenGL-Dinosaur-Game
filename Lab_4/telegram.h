#pragma once

/**
 * @file telegram.h
 * @brief Defines the telegram struct and related operators.
 */

#include <iostream>
#include <cmath>
#include <sol/sol.hpp>

 /**
  * @brief Struct representing a telegram.
  */
struct telegram
{
    double dispatchTime; ///< The time at which the telegram should be dispatched.
    int sender; ///< The entity that sent this telegram.
    int receiver; ///< The entity that is intended to receive this telegram.
    int msg; ///< The message itself, enumerated in "MessageTypes.h".
    sol::object extraInfo; ///< Additional information accompanying the message.

    /**
     * @brief Default constructor for telegram.
     */
    telegram() : dispatchTime(-1), sender(-1), receiver(-1), msg(-1) {}

    /**
     * @brief Constructor for telegram.
     * @param time The dispatch time of the telegram.
     * @param sender The entity that sent the telegram.
     * @param receiver The entity that should receive the telegram.
     * @param msg The message type.
     * @param info Additional information accompanying the message.
     */
    telegram(double time, int sender, int receiver, int msg, sol::object info) :
        dispatchTime(time), sender(sender), receiver(receiver),
        msg(msg), extraInfo(info) {}

    /**
     * @brief Overloaded equality operator for telegrams.
     * @param t1 The first telegram to compare.
     * @param t2 The second telegram to compare.
     * @return True if the telegrams are equal, false otherwise.
     */
    friend bool operator==(const telegram& t1, const telegram& t2)
    {
        return (std::fabs(t1.dispatchTime - t2.dispatchTime) < telegram::smallestDelay)
            && (t1.sender == t2.sender)
            && (t1.receiver == t2.receiver)
            && (t1.msg == t2.msg);
    }

    /**
     * @brief Overloaded less-than operator for telegrams.
     * @param t1 The first telegram to compare.
     * @param t2 The second telegram to compare.
     * @return True if t1 is less than t2, false otherwise.
     */
    friend bool operator<(const telegram& t1, const telegram& t2)
    {
        if (t1 == t2)
        {
            return false;
        }
        else
        {
            return (t1.dispatchTime < t2.dispatchTime);
        }
    }

    static constexpr double smallestDelay = 0.25; ///< The smallest delay between two telegrams to be considered the same.
};
