#pragma once





#include <memory>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include "Camera.h"
#include "LabEngine.h"



class MovementKeys 
{
    public:

        enum class Directions
        {
            FORWARD,
            BACK,
            LEFT,
            RIGHT
        };


        explicit MovementKeys();

            /***********************************************************************************************************************************************************************
             * @brief Enum defining movement directions.
             ***********************************************************************************************************************************************************************/

        ~MovementKeys();


            /************************************************************************************************************************************************************************
             * @brief MovementKeys() 
             * @brief used to construct a movemnetkeys object 
             * @param playerCamera The player camera associated with the movement.
             ***********************************************************************************************************************************************************************/

        MovementKeys(std::shared_ptr<Camera> playerCamera);


            /***********************************************************************************************************************************************************************
             * @brief  getMDirections()
             * @brief  used to get the current direction the player wishes to move in.
             * @return The current movement direction.
             ***********************************************************************************************************************************************************************/

        Directions getDirections() const;


            /***********************************************************************************************************************************************************************
             * @brief  getPlayerSpeed() 
             * @brief  used to get the players movement speed
             * @return The players movment speed.
             ***********************************************************************************************************************************************************************/
        
        float getPlayerSpeed() const;
    

            /***********************************************************************************************************************************************************************
             * @brief setPlayerSpeed()
             * @brief used to set the speed of the player 
             * @param speed float
             ***********************************************************************************************************************************************************************/
        
        void setPlayerSpeed(float speed);



            /***********************************************************************************************************************************************************************
             * @brief movePlayer()
             * @brief used to move a player in a given direction
             * 
             * @param 
             * @param
             * @param
             ***********************************************************************************************************************************************************************/

        void movePlayer(Directions direction, float deltaT);


        void onKeyInput(GLFWwindow* window, int key, int action, int mods, float deltaT);


private:
    
    float m_PlayerSpeed;
    Directions m_CurrentDirection;
    std::shared_ptr<Camera> m_PlayerCamera;
};
