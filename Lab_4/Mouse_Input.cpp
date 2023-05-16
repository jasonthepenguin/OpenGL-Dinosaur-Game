#include "Mouse_Input.h"



void Mouse_Input::mouse_callback(GLFWwindow* m_PixelsGLFWWindow, double xposIn, double yposIn)
{
	auto& app = LabEngine::getInstance();

	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (app.firstMouse)
	{
		app.lastX = xpos;
		app.lastY = ypos;
		app.firstMouse = false;
	}

	float xoffset = xpos - app.lastX;
	float yoffset = app.lastY - ypos; // reversed since y-coordinates go from bottom to top

	app.lastX = xpos;
	app.lastY = ypos;

	app.m_camera->ProcessMouseMovement(xoffset, yoffset);
}