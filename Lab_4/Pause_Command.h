#pragma once

#include "Menu_Command.h"

class Pause_Command : public Menu_Command
{
public:
	Pause_Command();
	~Pause_Command() override = default;

	void executeTask() override;
};