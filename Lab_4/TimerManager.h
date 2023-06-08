#pragma once



#include <GLFW/glfw3.h>
#include <iostream>
#include <map>
#include <string>
#include <memory>

class Timer {
public:

    /**
     * @brief Constructs a Timer object.
     * @param name The name of the timer.
     * @param seconds The duration of the timer in seconds.
     */
    Timer(const std::string& name, int seconds) : name(name), secondsLeft(seconds), expired(false) {}

    /**
     * @brief Updates the timer based on the current time.
     * @param currentTime The current time.
     */
    void update(double currentTime) {
        if (!expired) {
            double elapsedTime = currentTime - initialTime;
            if (elapsedTime >= secondsLeft) {
                expired = true;
            }
        }
    }

    /**
     * @brief Starts the timer.
     */
    void start() {
        initialTime = glfwGetTime();
    }

    /**
    * @brief Ends the timer.
    */
    void end() {
        expired = true;
    }


    void disable() {
        disabled = true;
    }

    bool isDisabled() {
        return disabled;
    }

    /**
     * @brief Resets the timer.
     */
    void reset() {
        initialTime = glfwGetTime();
        expired = false;
    }

    /**
   * @brief Changes the duration of the timer.
   * @param seconds The new duration in seconds.
   */
    void changeDuration(int seconds) {
        secondsLeft = seconds;
    }

    /**
    * @brief Checks if the timer has expired.
    * @return True if the timer has expired, false otherwise.
    */
    bool isExpired() const {
        return expired;
    }

    /**
    * @brief Gets the name of the timer.
    * @return The name of the timer.
    */
    const std::string& getName() const {
        return name;
    }



    /**
     * @brief Gets the number of seconds remaining in the timer.
     * @return The number of seconds remaining.
     */
    int getSecondsRemaining() const {
        if (expired) {
            return 0.0;
        }
        double currentTime = glfwGetTime();
        double elapsedTime = currentTime - initialTime;
        double remainingTime = secondsLeft - elapsedTime;
        return remainingTime > 0 ? remainingTime : 0.0;
    }

private:
    std::string name;
    double initialTime;
    int secondsLeft;
    bool expired;
    bool disabled = false;
};

/**
 * @brief A class representing a timer manager.
 */
class TimerManager {
public:

    /**
     * @brief Creates a new timer with the specified name and duration.
     * @param name The name of the timer.
     * @param seconds The duration of the timer in seconds.
     */
    void createTimer(const std::string& name, int seconds) {
        timers[name] = std::make_shared<Timer>(name, seconds);
    }

    /**
     * @brief Gets the timer with the specified name.
     * @param name The name of the timer.
     * @return A shared pointer to the timer if found, nullptr otherwise.
     */
    std::shared_ptr<Timer> getTimer(const std::string& name) {
        auto it = timers.find(name);
        if (it != timers.end()) {
            return it->second;
        }
        return nullptr;
    }

    /**
     * @brief Updates all timers based on the current time.
     */
    void updateAll() {
        double currentTime = glfwGetTime();
        for (auto& timer : timers) {
            timer.second->update(currentTime);
        }
    }

private:
    std::map<std::string, std::shared_ptr<Timer>> timers;
};