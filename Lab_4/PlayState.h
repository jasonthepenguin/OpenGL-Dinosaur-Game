#pragma once
#include "IGameState.h"
class PlayState : public IGameState
{
    void Enter() override;

    void Exit() override;

    void Update() override;

    void Render() override {
        // Code to render the game graphics
    }
};

