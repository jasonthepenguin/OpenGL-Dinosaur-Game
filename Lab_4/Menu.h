#pragma once
class Menu
{
	public:
		virtual ~Menu() {}
		virtual void generate() = 0;
};