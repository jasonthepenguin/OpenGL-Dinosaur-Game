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

	/**
	 * @brief Calculates the Frames Per Second (FPS)
	 *
	 * This function is used to calculate the FPS by measuring the number of frames
	 * that have been drawn within one second intervals. The FPS is then stored in
	 * the m_fps member variable. This function should be called in your main loop.
	 */
	void calculateFPS();

	/**
	 * @brief Returns the current Frames Per Second (FPS)
	 *
	 * This function is used to return the current FPS which is calculated by the
	 * calculateFPS function. The FPS is calculated as the total number of frames
	 * drawn within one second intervals.
	 *
	 * @return The current FPS as a double.
	 */
	double getFPS() const;

	GLFWwindow* m_PixelsGLFWWindow;




private:

	static bool keys[]; // state of each key on keyboard
	static Window* staticWindow;

	int m_width;
	int m_height;

	int m_nbFrames = 0;
	double m_lastTime = glfwGetTime(), m_currentTime;
	double m_fps = 0.0; // Variable to store the FPS

	bool m_IsMouseLocked = true;

	static void frameBufferSizeCallback(GLFWwindow* window, int width, int height);
};

