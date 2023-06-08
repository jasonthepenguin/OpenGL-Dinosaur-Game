#pragma once



#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <fstream>
#include <string>



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
             * @brief : BeginFrame()
             * @brief : Displays a basic list of commands that the player can enter via keyboard to achieve x results
             ********************************************************************************************************/

        void BeginFrame();

        
            /********************************************************************************************************
             * @brief : EndFrame()
             * @brief : Used to end the current GUI 
             ********************************************************************************************************/

        void EndFrame();
        

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



        void save_game();

        void load_game();

        void setupUserInterfaceStyle();

        void demoWindow();
        void imageWindow();
        void callPauseMenu();
        void generatePauseMenu(bool men);

        void generateCustomerSupport();
        void backButton();


        bool show_demo_window = true; 
        bool show_image = false; 
        bool showPauseMenu = false;

        unsigned int image_texture_id;


        GLFWwindow* m_PixelsGLFWWindow;
};



