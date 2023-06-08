#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Camera.h"
#include "EngGUI.h"
#include "md2_test.h"
#include "ModelController.h"
#include "LabEngine.h"

#include <unordered_map>

/**
 * @class SpecialKeys
 * @brief Represents special keys used in the game engine.
 */
class SpecialKeys
{
public:
    /**
     * @brief Constructs an object of SpecialKeys for use in the game engine.
     */
    SpecialKeys();

    /**
     * @brief Destructor used to delete a SpecialKeys object.
     */
    ~SpecialKeys();

    /**
     * @brief Handles the entered key event.
     *
     * @param m_PixelsGLFWWindow - Pointer to the GLFW window.
     * @param key - The key code.
     * @param keyState - Reference to the key state.
     * @param action - Pointer to the member function to be called.
     */
    void handleKeyEntered(GLFWwindow* m_PixelsGLFWWindow, int key, bool& keyState, void (SpecialKeys::* action)() = nullptr);

    // LETTERS
    /**
     * @brief Handles the F key entered event.
     *
     * @param m_PixelsGLFWWindow - Pointer to the GLFW window.
     */
    void F_KeyEntered(GLFWwindow* m_PixelsGLFWWindow);

    /**
     * @brief Handles the K key entered event.
     *
     * @param m_PixelsGLFWWindow - Pointer to the GLFW window.
     */
    void K_KeyEntered(GLFWwindow* m_PixelsGLFWWindow);

    /**
     * @brief Handles the L key entered event.
     *
     * @param m_PixelsGLFWWindow - Pointer to the GLFW window.
     */
    void L_KeyEntered(GLFWwindow* m_PixelsGLFWWindow);

    /**
     * @brief Handles the M key entered event.
     *
     * @param m_PixelsGLFWWindow - Pointer to the GLFW window.
     */
    void M_KeyEntered(GLFWwindow* m_PixelsGLFWWindow);

    /**
     * @brief Handles the X key entered event.
     *
     * @param m_PixelsGLFWWindow - Pointer to the GLFW window.
     */
    void X_KeyEntered(GLFWwindow* m_PixelsGLFWWindow);

    /**
     * @brief Handles the Space key entered event.
     *
     * @param m_PixelsGLFWWindow - Pointer to the GLFW window.
     */
    void Space_KeyEntered(GLFWwindow* m_PixelsGLFWWindow);

    /**
     * @brief Handles the U key entered event.
     *
     * @param m_PixelsGLFWWindow - Pointer to the GLFW window.
     */
    void U_KeyEntered(GLFWwindow* m_PixelsGLFWWindow);

    // ARROWS
    /**
     * @brief Handles the left arrow key entered event.
     *
     * @param m_PixelsGLFWWindow - Pointer to the GLFW window.
     */
    void left_KeyEntered(GLFWwindow* m_PixelsGLFWWindow);

    /**
     * @brief Handles the right arrow key entered event.
     *
     * @param m_PixelsGLFWWindow - Pointer to the GLFW window.
     */
    void right_KeyEntered(GLFWwindow* m_PixelsGLFWWindow);

    /**
     * @brief Handles the up arrow key entered event.
     *
     * @param m_PixelsGLFWWindow - Pointer to the GLFW window.
     */
    void up_KeyEntered(GLFWwindow* m_PixelsGLFWWindow);

    /**
     * @brief Handles the down arrow key entered event.
     *
     * @param m_PixelsGLFWWindow - Pointer to the GLFW window.
     */
    void down_KeyEntered(GLFWwindow* m_PixelsGLFWWindow);

    /**
     * @brief Toggles the wireframe mode for displaying objects.
     */
    void toggleWireframeMode();

    /**
     * @brief Toggles the lighting state.
     */
    void toggleLighting();

    /**
     * @brief Triggers the flying state.
     */
    void triggerFlying();

    /**
     * @brief Displays the demo game window.
     */
    void displayDemoWindow();

    /**
     * @brief Displays the group photo.
     */
    void displayGroupPhoto();

    /**
     * @brief Reads input for keys other than those used to manipulate the model.
     *
     * @param m_PixelsGLFWWindow - Pointer to the GLFW window.
     * @param deltaT - The time difference.
     */
    void readTaskInput(GLFWwindow* m_PixelsGLFWWindow, float deltaT);

    /**
     * @brief Reads model command inputs for moving the model and playing the next animation.
     *
     * @param m_PixelsGLFWWindow - Pointer to the GLFW window.
     * @param deltaT - The time difference.
     * @param modelController - Reference to the model controller.
     */
     // void readModelInput(GLFWwindow* m_PixelsGLFWWindow, float deltaT, ModelController& modelController);

     /**
      * @brief Reads input keys other than W, A, S, D.
      *
      * @param m_PixelsGLFWWindow - Pointer to the GLFW window.
      * @param deltaT - The time difference.
      */
      // void readInput(GLFWwindow* m_PixelsGLFWWindow, float deltaT, ModelController& modelController, Camera& camera);
    void readInput(GLFWwindow* m_PixelsGLFWWindow, float deltaT);

    /**
     * @brief Toggles the state of the mouse cursor between locked and free.
     *
     * When the cursor is locked, it is hidden and its movement is limited to the window.
     * When the cursor is free, it is visible and can move anywhere on the screen.
     * This function changes the cursor state each time it is called, alternating between locked and free.
     */
    void toggleMouseAction();

    bool isFlying; // Probably should be a variable of a player class?

private:
    EngGUI* gui;
    bool wireframe;
    std::vector<MD2_TEST*> MD2models;
    // ModelController& modelController; // Having it like this means it has to be initialized in the constructor. Since I just want the project to compile, I'm going to make it a pointer for now.
    // ModelController* modelController;
    GLFWwindow* m_PixelsGLFWWindow;

    std::unordered_map<int, bool> keyStates;
};
