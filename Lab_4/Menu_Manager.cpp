#include "Menu_Manager.h"


class MenuManager
{
public:
	void draw()
	{
		if (!menuStack.empty())
		{
			menuStack.top()->draw();
		}
	}

	void pushMenu(std::shared_ptr<Menu> menu)
	{
		menuStack.push(menu);
	}

	void popMenu()
	{
		if (!menuStack.empty())
		{
			menuStack.pop();
		}
	}

private:
	std::stack<std::shared_ptr<Menu>> menuStack;
};

void generateMenu(std::shared_ptr<Menu> menu)
{
	menu->generate();
}