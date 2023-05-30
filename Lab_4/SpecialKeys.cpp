#include "SpecialKeys.h"

SpecialKeys::SpecialKeys() : wireframe(false), isFlying(false){ }

SpecialKeys::~SpecialKeys() { }

void SpecialKeys::executeAction(SpecialActions action)
{
	switch (action)
	{
	case SpecialActions::FLY:
		triggerFlying();
		break;
	case SpecialActions::WIREFRAME:
		toggleWireframeMode();
		break;
	case SpecialActions::LIGHTING:
		toggleLighting();
		break;
	case SpecialActions::DEMO:
		displayDemoWindow();
		break;
	case SpecialActions::PHOTO:
		displayGroupPhoto();
		break;
	default:
		break;
	}
}



void SpecialKeys::toggleWireframeMode()
{
	wireframe = !wireframe;

	if (wireframe)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}



void SpecialKeys::triggerFlying()
{
	isFlying = !isFlying;

	auto m_camera = LabEngine::getInstance().m_camera;
	m_camera->canFly = !m_camera->canFly;

	std::cout << isFlying << std::endl;
}



void SpecialKeys::handleKeyEntered(GLFWwindow* m_PixelsGLFWWindow, int key, bool& keyState, void (SpecialKeys::* action)())
{
	if (glfwGetKey(m_PixelsGLFWWindow, key) == GLFW_PRESS && !keyState)
	{
		(this->*action)();

		keyState = true;
	}
	else if (glfwGetKey(m_PixelsGLFWWindow, key) == GLFW_RELEASE)
	{
		keyState = false;
	}
}


// The other functions for handling specific keys entered, for instance F_KeyEntered, K_KeyEntered, etc, go here...



void SpecialKeys::readInput(GLFWwindow* m_PixelsGLFWWindow, float deltaT)
{
	// letters
	F_KeyEntered(m_PixelsGLFWWindow);
	K_KeyEntered(m_PixelsGLFWWindow);
	L_KeyEntered(m_PixelsGLFWWindow);
	M_KeyEntered(m_PixelsGLFWWindow);
	X_KeyEntered(m_PixelsGLFWWindow);

	// arrows
	left_KeyEntered(m_PixelsGLFWWindow);
	// right_KeyEntered(m_PixelsGLFWWindow); // You can uncomment this when you've implemented it
	up_KeyEntered(m_PixelsGLFWWindow);
	down_KeyEntered(m_PixelsGLFWWindow);

	if (glfwGetKey(m_PixelsGLFWWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(m_PixelsGLFWWindow, true);
	}
}


void SpecialKeys::onKeyInput(GLFWwindow* window, int key, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		case GLFW_KEY_F:
			triggerFlying();
			break;

		case GLFW_KEY_K:
			toggleWireframeMode();
			break;

		case GLFW_KEY_L:
			toggleLighting();
			break;

		case GLFW_KEY_M:
			displayDemoWindow();
			break;


		case GLFW_KEY_X:
			displayGroupPhoto();
			break;
		default:
			break;
		}
	}
}
