#include "Quit_Command.h"


Quit_Command::~Quit_Command()
{

}

void Quit_Command::executeTask()
{
	if (ImGui::Button("Quit Game"))
	{
		// Close the application
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

