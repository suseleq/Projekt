#pragma once
#include "ClassCharacter.h"
#include <sstream>

class Menu
{
private:
	sf::Clock delayMenu;
	bool canChangeOption;
	int currentMenuOption;
	sf::Font fontMenu;
	sf::Text *menuText;

	void initMenuOptions();
	void checkCanChangeOption();

public:
	Menu();
	~Menu();

	void setDelay();

	void setFont();
	int getPressedOption();
	void moveUp();
	void moveDown();
	void render(sf::RenderTarget &target);
};

