#pragma once
#include "ClassCharacter.h"

class ChooseCharacterMenu
{
private:
	sf::Texture knightTexture;
	sf::Texture mageTexture;

	sf::Sprite knightSprite;
	sf::Sprite mageSprite;

	sf::IntRect currentFrame;
	sf::Clock clock;

	sf::Clock delayMenu;
	bool canChangeOption;

	int currentMenuOption;

	sf::Font fontMenu;
	sf::Text* menuText;

	void initTextures();
	void setTextures();
	void initMenuOptions();

public:
	ChooseCharacterMenu();
	~ChooseCharacterMenu();

	int getPressedOption();
	bool checkCanChangeOption();
	void moveLeft();
	void moveRight();
	void uptadeAnim();
	void uptade();
	void render(sf::RenderTarget& target);
};

