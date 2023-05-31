#pragma once

#include <memory>

#include "Pause_Menu.h"


class Menu_Manager
{
	public:
		void generate();
		void pushMenu();
		void popMenu();

	private:
		std::stack<std::shared_ptr<Pause_Menu>> pauseMenuStack;
};
