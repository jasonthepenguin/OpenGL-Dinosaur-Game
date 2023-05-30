#include "Keyboard_Input.h"




Keyboard_Input::Keyboard_Input(std::shared_ptr<Camera> playerCamera) :
    m_SpecialKeys(std::make_shared<SpecialKeys>()),
    m_MovementKeys(std::make_shared<MovementKeys>())
{
    // Initialize other members here if needed
}


void Keyboard_Input::readInput(GLFWwindow* m_PixelsGLFWWindow, float deltaT)
{

	glfwSetKeyCallback(m_PixelsGLFWWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
		observer->onKeyInput(window, key, action, mods);
		}
	);


	glfwSetCursorPosCallback(m_PixelsGLFWWindow, [](GLFWwindow* window, double xPos, double yPos)
		{
			observer->onMouseInput(window, xPos, yPos);
		}
    );
}


void Keyboard_Input::addObserver(std::shared_ptr<InputObserver_DPattern> observer)
{
	m_Observers.insert(observer);
}


void Keyboard_Input::removeObserver(std::shared_ptr<InputObserver_DPattern> observer)
{
	m_Observers.erase(observer);
}