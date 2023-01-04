#pragma once
#include "ClassCharacter.h"


class EscapeMenu
{
private:
	sf::Clock delayMenu;
	bool canChangeOption;
	int currentMenuOption;
	sf::Font fontMenu;
	sf::Text* menuText;

	void initMenuOptions();
	void checkCanChangeOption();

public:
	EscapeMenu();
	~EscapeMenu();

	

	void setCurrentOption(int option);
	void setFont();
	
	int getPressedOption();
	
	void moveUp();
	void moveDown();
	
	void render(sf::RenderTarget& target);
};

