#pragma once


#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include "LabEngine.h"

class Mouse_Input
{
	public:

		void mouse_callback(GLFWwindow* m_PixelsGLFWWindow, double xposIn, double yposIn);

	private:

		GLFWwindow* m_PixelsGLFWWindow;
};

