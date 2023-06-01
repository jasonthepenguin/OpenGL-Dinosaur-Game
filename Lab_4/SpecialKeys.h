#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Camera.h"
#include "EngGUI.h"
#include "md2_test.h"
#include "LabEngine.h"


#include <unordered_map>
#include "InputObserver_DPattern.h"


class SpecialKeys : public InputObserver_DPattern
{
    public:

		enum class SpecialActions
		{
			FLY,
			WIREFRAME,
			LIGHTING,
			DEMO,
			PHOTO
		};

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
        void executeAction(SpecialActions action);


        // LETTERS
        void F_KeyEntered(GLFWwindow* m_PixelsGLFWWindow);
        void K_KeyEntered(GLFWwindow* m_PixelsGLFWWindow);
        void L_KeyEntered(GLFWwindow* m_PixelsGLFWWindow);
        void M_KeyEntered(GLFWwindow* m_PixelsGLFWWindow);
        void X_KeyEntered(GLFWwindow* m_PixelsGLFWWindow);
        void Space_KeyEntered(GLFWwindow* m_PixelsGLFWWindow);

        // ARROWS
        void left_KeyEntered(GLFWwindow* m_PixelsGLFWWindow);
        void right_KeyEntered(GLFWwindow* m_PixelsGLFWWindow);
        void up_KeyEntered(GLFWwindow* m_PixelsGLFWWindow);
        void down_KeyEntered(GLFWwindow* m_PixelsGLFWWindow);


       


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


            /***********************************************************************************************************************************************************************
             * @brief readInput()
             * @brief this function is used to read input keys other than W,A,S,D
             *
             * @param m_PixelsGLFWWindow  - GLFWwindow provides access to the game window
             * @param deltaT              - float track of time
             ***********************************************************************************************************************************************************************/

     
        void readInput(GLFWwindow* m_PixelsGLFWWindow, float deltaT);



        void onKeyInput(GLFWwindow* window, int key, int action, int mods) override;


        bool isFlying; // probably should be a variable of a player class?

    private:
        
        EngGUI*                gui;
        bool                   wireframe;
        
        GLFWwindow*            m_PixelsGLFWWindow;
        std::vector<MD2_TEST*> MD2models;
        std::unordered_map<int, bool> keyStates;
        std::unordered_map<int, SpecialActions> keyToActionMap;
};
