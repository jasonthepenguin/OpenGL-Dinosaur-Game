#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Camera.h"
#include "EngGUI.h"
#include "md2_test.h"
#include "ModelController.h"
#include "LabEngine.h"


#include <unordered_map>

class SpecialKeys 
{
    public:

            /***********************************************************************************************************************************************************************
             * @brief SpecialKeys()
             * @brief constructs an object of special keys for use in the game engine
             ***********************************************************************************************************************************************************************/

        SpecialKeys();


            /***********************************************************************************************************************************************************************
             * @brief SpecialKeys()
             * @brief Destructor used to delete a SpecialKeys object
             ***********************************************************************************************************************************************************************/

        ~SpecialKeys();
        void handleKeyEntered(GLFWwindow* m_PixelsGLFWWindow, int key, bool& keyState, void (SpecialKeys::* action)());


        void F_KeyEntered(GLFWwindow* m_PixelsGLFWWindow);
        void K_KeyEntered(GLFWwindow* m_PixelsGLFWWindow);
        void L_KeyEntered(GLFWwindow* m_PixelsGLFWWindow);
        void M_KeyEntered(GLFWwindow* m_PixelsGLFWWindow);
        void X_KeyEntered(GLFWwindow* m_PixelsGLFWWindow);


            /***********************************************************************************************************************************************************************
             * @brief toggleWireframeMode()
             * @brief this function is used to display the wireframe on all objects
             ***********************************************************************************************************************************************************************/

        void toggleWireframeMode();


            /***********************************************************************************************************************************************************************
             * @brief triggerFlying()
             * @brief this function is used to trigger Flying
             ***********************************************************************************************************************************************************************/

        void toggleLighting();


            /***********************************************************************************************************************************************************************
             * @brief triggerFlying()
             * @brief this function is used to trigger Flying
             ***********************************************************************************************************************************************************************/

        void triggerFlying();


            /***********************************************************************************************************************************************************************
             * @brief displayDemo()
             * @brief this function is used to display a demo game window
             ***********************************************************************************************************************************************************************/

        void displayDemoWindow();


            /***********************************************************************************************************************************************************************
             * @brief displayPhoto()
             * @brief this function is used to display the group photo
             ***********************************************************************************************************************************************************************/

        void displayGroupPhoto();


            /***********************************************************************************************************************************************************************
             * @brief readTaskInput()
             * @brief this function is used to read input for keys other than those used to manipulate the model
             * 
             * @param m_PixelsWindow - GLFWWindow*
             * @param deltaT         - float
             ***********************************************************************************************************************************************************************/

        void readTaskInput(GLFWwindow* m_PixelsGLFWWindow, float deltaT);


            /***********************************************************************************************************************************************************************
             * @brief readModelInput()
             * @brief this function is used to read model command inputs for moving the model and playing the next animation
             * 
             * @param m_Pixels
             ***********************************************************************************************************************************************************************/

       // void readModelInput(GLFWwindow* m_PixelsGLFWWindow, float deltaT, ModelController& modelController);


            /***********************************************************************************************************************************************************************
             * @brief readInput()
             * @brief this function is used to read input keys other than W,A,S,D
             *
             * @param m_PixelsGLFWWindow  - GLFWwindow provides access to the game window
             * @param deltaT              - float track of time
             ***********************************************************************************************************************************************************************/

       // void readInput(GLFWwindow* m_PixelsGLFWWindow, float deltaT, ModelController& modelController, Camera& camera);
        void readInput(GLFWwindow* m_PixelsGLFWWindow, float deltaT);


        bool isFlying; // probably should be a variable of a player class?

    private:
        
        EngGUI*                gui;
        bool                   wireframe;
        std::vector<MD2_TEST*> MD2models;
       // ModelController&       modelController;                 // having it like this means it has to be initialised in the constructor, since I just want the project to compile I'm going to make it a pointer for now
       // ModelController* modelController;
        GLFWwindow*            m_PixelsGLFWWindow;

        std::unordered_map<int, bool> keyStates;

};
