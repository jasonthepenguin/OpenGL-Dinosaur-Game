#pragma once

/***************************************************************************************************************
 * @brief : IGameState
 * @brief :
 *
 *
 *
 * @date    : May 2023
 * @author  : William Halling
 * @version : 1.0
 ******************************************************************************************************************/

class GameState 
{
    public:

        virtual void handlePlayerInput() = 0;
        virtual void Enter()  = 0;
        virtual void Exit()   = 0;
        virtual void update() = 0;
        virtual void generate() = 0;
};