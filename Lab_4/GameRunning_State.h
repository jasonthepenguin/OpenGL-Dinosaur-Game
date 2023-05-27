#pragma once
#include "IGameState.h"
#include "UI_Manager.h"


class GameRunning_State : public IGameState
{
    public:
        GameRunning_State(std::shared_ptr<UI_Manager> tempPlayerUI);

        void handlePlayerInput() override;
        void Update() override;
        void Generate() override;

    private:
        std::shared_ptr<UI_Manager> m_UIManager;
};


class GamePausedState : public GameState {
public:
    void handleInput() override;
    void update() override;
    void draw() override;
};

void GamePausedState::draw() {
    // Draw the game world in a "paused" state
    drawGameWorld();

    // Draw the pause menu
    ImGui::Begin("Paused");

    if (ImGui::Button("Resume")) {
        // Switch to the GameRunningState
    }

    if (ImGui::Button("Display photo")) {
        // Display the photo
    }

    // ...

    ImGui::End();
}

lass GameStateManager{
public:
    static GameStateManager & getInstance() {
        static GameStateManager instance;
        return instance;
    }

    void setState(std::unique_ptr<GameState> newState) {
        currentState = std::move(newState);
    }

    void handleInput() {
        currentState->handleInput();
    }

    void update() {
        currentState->update();
    }

    void draw() {
        currentState->draw();
    }

private:
    std::unique_ptr<GameState> currentState;
};