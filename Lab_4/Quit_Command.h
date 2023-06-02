#pragma once

#include <GLFW/glfw3.h>
#include "imgui.h"
#include "Menu_Command.h"

class Quit_Command : public Menu_Command
{
public:
	Quit_Command();
	Quit_Command(GLFWwindow* window);
	~Quit_Command() override = default;
	void quitGame(GLFWwindow* m_PixelsGLFWWindow);
	void executeTask() override;

private:
	GLFWwindow* m_PixelsGLFWWindow;
	bool m_QuitConfirmationOpen;
};