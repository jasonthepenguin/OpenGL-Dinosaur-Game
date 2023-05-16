#pragma once
#include <GLFW/glfw3.h>

class Mouse_Input
{
	public:

		void mouse_callback(GLFWwindow* m_PixelsGLFWWindow, double xposIn, double yposIn);

	private:

		GLFWwindow* m_PixelsGLFWWindow;
};

