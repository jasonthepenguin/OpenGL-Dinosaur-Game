#pragma once

#include <memory>


// Forward declarations
class Camera;
class SpecialKeys;
class MovementKeys;


#include <glad/glad.h>
#include <GLFW/glfw3.h>

    /***********************************************************************************************************************************************************************
     * @class KeyboardInput
     * @brief Class is used to handle a palyers keyboard input
     ***********************************************************************************************************************************************************************/

class Keyboard_Input
{
    public:

            /***********************************************************************************************************************************************************************
             * @brief Constructs a `KeyboardInput` object.
             * @param playerCamera The player camera object.
             ***********************************************************************************************************************************************************************/
       
        Keyboard_Input(std::shared_ptr<Camera> playerCamera);


            /***********************************************************************************************************************************************************************
             * @brief Reads keyboard input and performs corresponding actions.
             * @param window The GLFW window.
             * @param deltaT The time elapsed since the last frame.
             ***********************************************************************************************************************************************************************/
        
        void readInput(GLFWwindow* m_PixelsGLFWWindow, float deltaT);


    private:
        std::shared_ptr<Camera> m_PlayerCamera;
        std::shared_ptr<SpecialKeys>  m_SpecialKeys;
        std::shared_ptr<MovementKeys> m_MovementKeys;
};