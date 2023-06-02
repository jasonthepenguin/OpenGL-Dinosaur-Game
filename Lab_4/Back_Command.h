#pragma once

#include <string>
#include <vector>
#include <iostream>
#include "imgui.h"

class Back_Command
{
public:
	virtual ~Back_Command() {}
	virtual void executeTask() = 0;
};