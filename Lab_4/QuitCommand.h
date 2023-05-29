#pragma once
#include "PauseMenu_Commands.h"

class Quit_Command : public PauseMenu_Commands
{
	virtual void executeTask() override;
};

