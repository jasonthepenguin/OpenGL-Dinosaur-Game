#pragma once



#include <GLFW/glfw3.h>
#include <iostream>
#include <map>
#include <string>
#include <memory>

class Timer {
public:
    Timer(const std::string& name, int seconds) : name(name), secondsLeft(seconds), expired(false) {}

    void update(double currentTime) {
        if (!expired) {
            double elapsedTime = currentTime - initialTime;
            if (elapsedTime >= secondsLeft) {
                expired = true;
            }
        }
    }

    void start() {
        initialTime = glfwGetTime();
    }

    void end() {
        expired = true;
    }

    void reset() {
        initialTime = glfwGetTime();
        expired = false;
    }

    void changeDuration(int seconds) {
        secondsLeft = seconds;
    }

    bool isExpired() const {
        return expired;
    }

    const std::string& getName() const {
        return name;
    }

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
};

class TimerManager {
public:
    void createTimer(const std::string& name, int seconds) {
        timers[name] = std::make_shared<Timer>(name, seconds);
    }

    std::shared_ptr<Timer> getTimer(const std::string& name) {
        auto it = timers.find(name);
        if (it != timers.end()) {
            return it->second;
        }
        return nullptr;
    }

    void updateAll() {
        double currentTime = glfwGetTime();
        for (auto& timer : timers) {
            timer.second->update(currentTime);
        }
    }

private:
    std::map<std::string, std::shared_ptr<Timer>> timers;
};