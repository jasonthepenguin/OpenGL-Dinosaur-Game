#include "Pause_Command.h"
bool gameIsPaused = false;




///GAME LOOP

while (!glfwWindowShouldClose(window))
{
	// Process input
	processInput(window);

	// Update
	if (!gameIsPaused)
	{
		updateGameObjects(); // Update game objects only when game is not paused
	}

	// Render
	renderGameObjects();

	// Swap buffers and poll IO events
	glfwSwapBuffers(window);
	glfwPollEvents();
}




void Pause_Command::executeTask()
{
	// Bring up the menu
	auto& menu = Menu::getInstance();
	menu.displayMenu();
}