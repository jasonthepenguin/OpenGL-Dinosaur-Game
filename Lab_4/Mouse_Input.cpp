#include "Mouse_Input.h"



Mouse_Input::Mouse_Input()
{

}


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
	app.m_camera->readMouseMovement(xoffset, yoffset);
	// update the camera 
}



void Mouse_Input::static_mouse_callback(GLFWwindow * m_PixelsGLFWWindow, double xposIn, double yposIn)
{
	LabEngine::getInstance().userInput->m_PlayerMouse->mouse_callback(m_PixelsGLFWWindow, xposIn, yposIn);
}


void Mouse_Input::readInput(GLFWwindow* GLFWWindow, float deltaT)
{



}