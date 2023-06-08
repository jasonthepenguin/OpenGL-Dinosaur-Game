/**
 * @file Mouse_Input.h
 * @brief Defines the Mouse_Input class.
 */

#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "LabEngine.h"

 /**
  * @class Mouse_Input
  * @brief Handles mouse input and movement.
  */
class Mouse_Input
{
public:
    /**
     * @brief Constructs a Mouse_Input object.
     */
    Mouse_Input();

    /**
     * @brief Callback function for mouse movement.
     * @param m_PixelsGLFWWindow The GLFW window.
     * @param xposIn The x-coordinate of the mouse position.
     * @param yposIn The y-coordinate of the mouse position.
     */
    void mouse_callback(GLFWwindow* m_PixelsGLFWWindow, double xposIn, double yposIn);

    /**
     * @brief Static callback function for mouse movement.
     * @param m_PixelsGLFWWindow The GLFW window.
     * @param xposIn The x-coordinate of the mouse position.
     * @param yposIn The y-coordinate of the mouse position.
     */
    static void static_mouse_callback(GLFWwindow* m_PixelsGLFWWindow, double xposIn, double yposIn);

    /**
     * @brief Reads mouse input.
     * @param GLFWWindow The GLFW window.
     * @param deltaT The time difference between frames.
     */
    void readInput(GLFWwindow* GLFWWindow, float deltaT);

private:
    GLFWwindow* m_PixelsGLFWWindow; /**< The GLFW window for mouse input. */
};
