#pragma once
#include "GameState.h"
#include "UI_Manager.h"


class GameRunning_State : public GameState
{
    public:
        GameRunning_State(std::shared_ptr<UI_Manager> tempPlayerUI);
        ~GameRunning_State();
        void handlePlayerInput() override;
		void Enter() override;
		void generate()  override;
		void update()  override;
		void Exit() override;

    private:
        std::shared_ptr<UI_Manager> m_UIManager;
};