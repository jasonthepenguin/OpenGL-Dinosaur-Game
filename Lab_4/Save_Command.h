#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "PauseMenu_Commands.h"
#include "imgui_impl_opengl3.h"



#include <fstream>
#include <iostream>



/***************************************************************************************************************
 * @brief : SaveCommand
 * @brief : 
 *
 *
 * @date    : May 2023
 * @author  : William Halling
 * @version : 1.0
 ******************************************************************************************************************/

class Save_Command : public PauseMenu_Commands
{
    public:
        void executeTask() override;
        void saveGame(const std::string& saveFile);

    private://create a player class for these and call the getters
		//int playerScore;
		//int playerLocation;
};

