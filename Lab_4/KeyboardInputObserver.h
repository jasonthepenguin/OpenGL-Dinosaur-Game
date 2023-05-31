#pragma once

#include <memory>
#include <iostream>
#include <GLFW/glfw3.h>
#include <unordered_set>



class KeyboardInputObserver
{
public:
	virtual ~KeyboardInputObserver() {}

	virtual void onKeyInput(GLFWwindow* window, int key, int action, int mods) = 0;
};