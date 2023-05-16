#pragma once
#include "Keyboard_Input.h"
#include "Mouse_Input.h"
#include <memory>


class UI_Manager
{
    public:


            /**********************************************************************************************************************************************************************
             * @brief Constructs a UI_Manager object.
             **********************************************************************************************************************************************************************/

        UI_Manager();


            /**********************************************************************************************************************************************************************
             * @brief Destroys the UI_Manager object.
             **********************************************************************************************************************************************************************/

        ~UI_Manager();


            /**********************************************************************************************************************************************************************
             * @brief Set the observer for MouseInput.
             * @param observer The observer to set.
             **********************************************************************************************************************************************************************/

        void setPlayerKeyboard(std::shared_ptr<Keyboard_Input> keyboard);


            /**********************************************************************************************************************************************************************
             * @brief Get the Mouse_Input object.
             * @return The Mouse_Input object.
             **********************************************************************************************************************************************************************/

        void setPlayerMouse(std::shared_ptr<Mouse_Input> mouse);


            /**********************************************************************************************************************************************************************
             * @brief Manages user input by processing keyboard and mouse input.
             * @brief This function is to be called once per frame during the games runtime as it will process player input
             *        This function does this by calling either the keyboard or mouse class
             * 
             * @param window The GLFW window.
             * @param deltaT The time elapsed since the last frame.
             ***********************************************************************************************************************************************************************/
        
        void readUserInput(GLFWwindow* window, float deltaT);

    private:
        std::shared_ptr<Keyboard_Input> m_PlayerKeyboard;
        std::shared_ptr<Mouse_Input> m_PlayerMouse;
        
};

