#pragma once



#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


#include "Texture.h"




    /********************************************************************************************************
     * @class   : EngGUI 
     * @brief   : A Graphical User Interface that is utilized to display a the welcome box to the player
     * 
     * @date    : April 2023
     * @author  : William Halling 322233703
     * @version : 1.0
     ********************************************************************************************************/


class EngGUI
{
    public:

            /********************************************************************************************************
             * @brief : EngGUI constructor
             * @brief : used to check the enggui version, change the colours, and utilize opengl
             ********************************************************************************************************/

        EngGUI();


            /********************************************************************************************************
             * @brief : EngGUI destructor
             * @brief : used to delete teh EngGUI object to free up resources
             ********************************************************************************************************/

        ~EngGUI();


            /********************************************************************************************************
             * @brief : beginFrame()
             * @brief : Displays a basic list of commands that the player can enter via keyboard to achieve x results
             ********************************************************************************************************/

        void beginFrame();

        
            /********************************************************************************************************
             * @brief : endFrame()
             * @brief : Used to end the current GUI 
             ********************************************************************************************************/

        void endFrame();
        

            /********************************************************************************************************
             * @brief : renderData()
             * @brief : Used to renders information to the players screen
             ********************************************************************************************************/

        void renderData();


            /********************************************************************************************************
             * @brief : MainMenu()
             * @brief : To be implemented updated and extended on
             ********************************************************************************************************/

        void MainMenu();


        bool show_demo_window = true; 
        bool show_image = false; 

        unsigned int image_texture_id;


        GLFWwindow* m_PixelsGLFWWindow;
};