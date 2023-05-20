#include "Window.h"




Window* Window::staticWindow = nullptr;





Window* Window::getWindow()
{
	if (!staticWindow)
	{
		staticWindow = new Window();
	}

	return staticWindow;
}


void Window::createWindow(int width, int height, const char* title)
{
	m_width = width;
	m_height = height;

	m_PixelsGLFWWindow = glfwCreateWindow(width, height, title, NULL, NULL);
	if (m_PixelsGLFWWindow == NULL) {
		std::cout << "Window not created properly!" << std::endl; // maybe assert?
	}


	glfwSetFramebufferSizeCallback(m_PixelsGLFWWindow, frameBufferSizeCallback);

	glfwMakeContextCurrent(m_PixelsGLFWWindow);


	// additional settings just here for now ( eg center the cursor )
	glfwSetInputMode(m_PixelsGLFWWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


}

void Window::frameBufferSizeCallback(GLFWwindow* m_PixelsGLFWWindow, int width, int height)
{

	glViewport(0, 0, width, height);
}




void Window::init()
{

	glfwInit();

	// Set up window hints
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

}


bool Window::shouldClose()
{
	return glfwWindowShouldClose(m_PixelsGLFWWindow);
}

void Window::swapBuffers()
{
	glfwSwapBuffers(m_PixelsGLFWWindow);
}

void Window::pollEvents()
{
	glfwPollEvents();
}

void Window::close()
{
	glfwTerminate();

}

float Window::getTime() {
	return glfwGetTime();
}


void Window::processInput()
{
	// I'm thinking that this function would just update the keys array so other sections of the engine can check what keys are being pressed.
	// Except maybe just also check if you want to exit the program

}
