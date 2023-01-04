#include "ChooseCharacterMenu.h"

bool ChooseCharacterMenu::checkCanChangeOption()
{
	if (this->delayMenu.getElapsedTime().asSeconds() >= 0.2f) {
		this->canChangeOption = true;
		this->delayMenu.restart();
	}
	return this->canChangeOption;
}


void ChooseCharacterMenu::initTextures()
{
	this->knightTexture.loadFromFile("Textures/knight_idle.png");
	this->mageTexture.loadFromFile("Textures/mage_idle.png");

	this->currentFrame = sf::IntRect(0, 0, 16, 28);
}

void ChooseCharacterMenu::setTextures()
{
	this->mageSprite.setTexture(this->mageTexture);
	this->mageSprite.setTextureRect(currentFrame);
	this->mageSprite.scale(6.f, 6.f);

	this->knightSprite.setTexture(this->knightTexture);
	this->knightSprite.setTextureRect(currentFrame);
	this->knightSprite.scale(6.f, 6.f);

	this->knightSprite.setPosition(200.f, 350.f);
	this->mageSprite.setPosition(400.f, 350.f);

}

void ChooseCharacterMenu::initMenuOptions()
{
	this->fontMenu.loadFromFile("fonts/PixellettersFull.ttf");

	this->menuText[0].setFont(this->fontMenu);
	this->menuText[0].setFillColor(sf::Color::Red);
	this->menuText[0].setPosition(sf::Vector2f(200.f, 600.f));
	this->menuText[0].setScale(2.f, 2.f);

	this->menuText[1].setFont(this->fontMenu);
	this->menuText[1].setFillColor(sf::Color::White);
	this->menuText[1].setPosition(sf::Vector2f(400.f, 600.f));
	this->menuText[1].setScale(2.f, 2.f);

	this->menuText[0].setString("Knight");
	this->menuText[1].setString("Mage");


}

ChooseCharacterMenu::ChooseCharacterMenu()
{
	this->canChangeOption = true;
	this->menuText = new sf::Text[2];
	this->currentMenuOption = 0;

	this->initTextures();
	this->setTextures();

	this->initMenuOptions();

	this->clock.restart();
	this->delayMenu.restart();
}

ChooseCharacterMenu::~ChooseCharacterMenu()
{
	delete[] this->menuText;
}

int ChooseCharacterMenu::getPressedOption()
{
	return this->currentMenuOption;
}

void ChooseCharacterMenu::moveLeft()
{
	this->checkCanChangeOption();

	if (this->currentMenuOption - 1 >= 0 && this->canChangeOption) {

		this->menuText[this->currentMenuOption].setFillColor(sf::Color::White);
		this->currentMenuOption--;
		this->menuText[this->currentMenuOption].setFillColor(sf::Color::Red);
		this->canChangeOption = false;
	}
}

void ChooseCharacterMenu::moveRight()
{
	this->checkCanChangeOption();

	if (this->currentMenuOption + 1 < 2 && this->canChangeOption) {
		this->menuText[this->currentMenuOption].setFillColor(sf::Color::White);
		this->currentMenuOption++;
		this->menuText[this->currentMenuOption].setFillColor(sf::Color::Red);
		this->canChangeOption = false;
	}
}

void ChooseCharacterMenu::uptadeAnim()
{
	if (this->clock.getElapsedTime().asSeconds() >= 0.25f) {

		this->currentFrame.left += 16.f;
		if (currentFrame.left >= 64.f)
			this->currentFrame.left = 0;

		this->clock.restart();
		this->mageSprite.setTextureRect(this->currentFrame);
		this->knightSprite.setTextureRect(this->currentFrame);

	}
}

void ChooseCharacterMenu::uptade()
{
	this->uptadeAnim();
}

void ChooseCharacterMenu::render(sf::RenderTarget& target)
{
	target.draw(this->menuText[0]);
	target.draw(this->menuText[1]);
	target.draw(this->mageSprite);
	target.draw(this->knightSprite);
}
