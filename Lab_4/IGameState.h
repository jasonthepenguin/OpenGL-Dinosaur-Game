#pragma once
class IGameState 
{
    public:

        virtual void handlePlayerInput() = 0;
        virtual void Enter()  = 0;
        virtual void Exit()   = 0;
        virtual void Update() = 0;
        virtual void generate() = 0;
};