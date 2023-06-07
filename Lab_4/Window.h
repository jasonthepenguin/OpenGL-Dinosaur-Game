#pragma once


#include <GLFW/glfw3.h>
#include <iostream>

/******************************************


 ******************************************/
class Window
{
public:
	void init();

	void createWindow(int width, int height, const char* title);

	void processInput();


	void swapBuffers();

	static Window* getWindow();

	bool shouldClose();


		/***********************************************************
		 * @brief : pollEvents
		 * @brief : used to poll window Events 
		 **********************************************************/

	void pollEvents();



		/***********************************************************
		 * @brief : close
		 * @brief : used to close the window
		 **********************************************************/
	
	void close();


		/***********************************************************
		 * @brief  : getTime
		 * @brief  : gets the duration the game engine has been running 
		 * @return : float 
		 **********************************************************/
	
	float getTime();


		/***********************************************************
		 * @brief : toggleMouse
		 * @brief : used to toggle the mouse between being locked and able to move freely and visible
		 **********************************************************/

	void toggleMouse();

	GLFWwindow* m_PixelsGLFWWindow;




private:

	static bool keys[]; // state of each key on keyboard
	static Window* staticWindow;

	int m_width;
	int m_height;

	bool m_IsMouseLocked = true;

	static void frameBufferSizeCallback(GLFWwindow* window, int width, int height);
};

