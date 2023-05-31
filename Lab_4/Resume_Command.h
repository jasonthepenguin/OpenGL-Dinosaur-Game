#pragma once

#include <iostream>

#include "imgui.h"
#include "Menu_Command.h"
#include "imgui_impl_glfw.h"
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

class Resume_Command : public Menu_Command
{
    public:
        Resume_Command() = default;
        void executeTask() override;
};
