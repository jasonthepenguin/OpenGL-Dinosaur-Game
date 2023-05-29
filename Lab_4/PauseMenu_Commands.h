#pragma once

#include <memory>
#include <functional>
#include <unordered_map>

/***************************************************************************************************************
 * @brief : PauseMenu_Commands
 * @brief : 
 *
 *
 * @date    : May 2023
 * @author  : William Halling
 * @version : 1.0
 ******************************************************************************************************************/

class PauseMenu_Commands
{
    public:

		    /***************************************************************************************************************
             * @brief : PauseMenu_Commands() 
             * @brief : Destructor of the PauseMenu_Commands object
             ***************************************************************************************************************/

		virtual ~PauseMenu_Commands() = default;


            /***************************************************************************************************************
		     * @brief : executeTask()
             * @brief : used to execute commands of the pause system 
		     ***************************************************************************************************************/

        virtual void executeTask()  = 0;
};


