#pragma once


#include <GLFW/glfw3.h>
#include <iostream>

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

	GLFWwindow* m_PixelsGLFWWindow;




private:

	static bool keys[]; // state of each key on keyboard
	static Window* staticWindow;

	int m_width;
	int m_height;

	static void frameBufferSizeCallback(GLFWwindow* window, int width, int height);

	

};

