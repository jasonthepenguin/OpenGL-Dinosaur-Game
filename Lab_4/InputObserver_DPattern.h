#pragma once

#include <memory>
#include <iostream>
#include <GLFW/glfw3.h>
#include <unordered_set>



class InputObserver_DPattern
{
public:
	virtual ~InputObserver_DPattern() {}

	virtual void onKeyInput(GLFWwindow* window, int key, int action, int mods) = 0;
	virtual void onMouseInput(GLFWwindow* window, double xPos, double yPos) = 0;
};