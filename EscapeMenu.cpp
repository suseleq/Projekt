#include "EscapeMenu.h"

void EscapeMenu::initMenuOptions()
{
	this->menuText[0].setFont(this->fontMenu);
	this->menuText[0].setFillColor(sf::Color::Red);
	this->menuText[0].setPosition(sf::Vector2f(740.f, 300.f));
	this->menuText[0].setScale(2.f, 2.f);

	this->menuText[1].setFont(this->fontMenu);
	this->menuText[1].setFillColor(sf::Color::White);
	this->menuText[1].setPosition(sf::Vector2f(740.f, 600.f));
	this->menuText[1].setScale(2.f, 2.f);

	this->menuText[0].setString("Return game");
	this->menuText[1].setString("Return to menu");
}

void EscapeMenu::checkCanChangeOption()
{
	if (this->delayMenu.getElapsedTime().asSeconds() >= 0.25f) {
		this->canChangeOption = true;
		this->delayMenu.restart();
	}
}

EscapeMenu::EscapeMenu()
{
	this->canChangeOption = true;
	this->setFont();
	this->menuText = new sf::Text[2];
	this->currentMenuOption = 0;
	this->initMenuOptions();
	this->delayMenu.restart();
}

EscapeMenu::~EscapeMenu()
{
	delete[] this->menuText;
}


void EscapeMenu::setCurrentOption(int option)
{
	this->currentMenuOption = option;
	this->menuText[this->currentMenuOption].setFillColor(sf::Color::Red);
	if(this->currentMenuOption == 0)
		this->menuText[1].setFillColor(sf::Color::White);
	else
		this->menuText[0].setFillColor(sf::Color::White);

}

void EscapeMenu::setFont()
{
	this->fontMenu.loadFromFile("fonts/PixellettersFull.ttf");
}

int EscapeMenu::getPressedOption()
{
	return this->currentMenuOption;
}

void EscapeMenu::moveUp()
{
	this->checkCanChangeOption();

	std::cout << this->currentMenuOption << "\n";

	if (this->currentMenuOption - 1 >= 0 && this->canChangeOption) {
		this->menuText[this->currentMenuOption].setFillColor(sf::Color::White);
		this->currentMenuOption--;
		this->menuText[this->currentMenuOption].setFillColor(sf::Color::Red);
		this->canChangeOption = false;
	}
}

void EscapeMenu::moveDown()
{
	this->checkCanChangeOption();
	std::cout << this->currentMenuOption << "\n";



	if (this->currentMenuOption + 1 < 2 && this->canChangeOption) {
		this->menuText[this->currentMenuOption].setFillColor(sf::Color::White);
		this->currentMenuOption++;
		this->menuText[this->currentMenuOption].setFillColor(sf::Color::Red);
		this->canChangeOption = false;
	}
}

void EscapeMenu::render(sf::RenderTarget& target)
{
	for (int i = 0; i < 2; i++) {
		target.draw(this->menuText[i]);
	}
}
