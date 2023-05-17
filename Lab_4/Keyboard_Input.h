#pragma once

#include <memory>



//#include "Camera.h"
//#include "SpecialKeys.h"
//#include "MovementKeys.h"

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


/**
#pragma once
#include <GLFW/glfw3.h>
#include <memory>
#include "PlayerCamera.h"

class KeyboardInput {
public:
    KeyboardInput(std::shared_ptr<PlayerCamera> playerCamera);

    void readInput(GLFWwindow* window, float deltaT);

private:
    std::shared_ptr<PlayerCamera> m_PlayerCamera;
};

class MovementKeys {
public:
    enum class PlayerMovement {
        MOVE_FORWARD,
        MOVE_BACKWARDS,
        MOVE_LEFT,
        MOVE_RIGHT
    };

    MovementKeys(std::shared_ptr<PlayerCamera> playerCamera);

    PlayerMovement getMovementDirection() const;
    float getPlayerSpeed() const;
    void setPlayerSpeed(float speed);

    void moveForward(float deltaT);
    void moveBackward(float deltaT);
    void moveLeft(float deltaT);
    void moveRight(float deltaT);

private:
    std::shared_ptr<PlayerCamera> m_PlayerCamera;
    float m_PlayerSpeed;
    PlayerMovement m_CurrentMovement;
};
**/