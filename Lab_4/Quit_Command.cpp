#include "Quit_Command.h"

Quit_Command::Quit_Command()
{

}


Quit_Command::Quit_Command(GLFWwindow* window)
	: m_PixelsGLFWWindow(window), m_QuitConfirmationOpen(false) // initialize members
{
}


void Quit_Command::quitGame(GLFWwindow* m_PixelsGLFWWindow)
{
	if (m_QuitConfirmationOpen)
	{
		if (ImGui::Begin("Quit Confirmation"))
		{
			ImGui::Text("Are you sure you want to quit?");

			if (ImGui::Button("Yes"))
			{
				glfwSetWindowShouldClose(m_PixelsGLFWWindow, GL_TRUE); // Quit game
			}

			if (ImGui::Button("Back"))
			{
				m_QuitConfirmationOpen = false; // Close confirmation dialog
			}

			ImGui::End();
		}
	}
}



void Quit_Command::executeTask()
{
	if (ImGui::Button("Quit Game"))
	{
		m_QuitConfirmationOpen = true; // Open confirmation dialog
		quitGame(m_PixelsGLFWWindow);
	}
}