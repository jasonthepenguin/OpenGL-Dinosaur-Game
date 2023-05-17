#pragma once


#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include "LabEngine.h"

class Mouse_Input
{
	public:



		Mouse_Input(); // constructor maybe needs to take GLFW window and then sets the callback function for mouse movement

		void mouse_callback(GLFWwindow* m_PixelsGLFWWindow, double xposIn, double yposIn);

		static void static_mouse_callback(GLFWwindow* m_PixelsGLFWWindow, double xposIn, double yposIn);


		void readInput(GLFWwindow* GLFWWindow, float deltaT);

		/*
		bool firstMouse;

		float lastX;
		float lastY;

		float xoffset;
		float yoffset;

		float Yaw;
		float Pitch;


		bool constrainPitch;

		float MouseSensitivity;
		*/

	private:

		GLFWwindow* m_PixelsGLFWWindow;



};

