#pragma once


#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "PauseMenu_Commands.h"
#include "imgui_impl_opengl3.h"


/***************************************************************************************************************
 * @brief : Resume_Command
 * @brief : 
 * 
 * 
 *
 * @date    : May 2023
 * @author  : William Halling
 * @version : 1.0
 ******************************************************************************************************************/

class Resume_Command : public PauseMenu_Commands
{
    public:
        Resume_Command();
        void executeTask() override;
};
