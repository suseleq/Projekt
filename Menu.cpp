#include "Menu.h"

void Menu::initMenuOptions()
{
	for (int i = 0; i < 3; i++) {
		this->menuText[i].setFont(this->fontMenu);
		this->menuText[i].setFillColor(sf::Color::White);
		this->menuText[i].setPosition(sf::Vector2f(200.f, 200.f + (i * 100.f)));
		this->menuText[i].setScale(2.f, 2.f);
	}
	this->menuText[0].setString("Play");
	this->menuText[1].setString("Options");
	this->menuText[2].setString("Close");
	this->menuText[currentMenuOption].setFillColor(sf::Color::Red);
}

void Menu::checkCanChangeOption()
{
	if (this->delayMenu.getElapsedTime().asSeconds() >= 0.25f) {
		this->canChangeOption = true;
		this->delayMenu.restart();
	}
}

Menu::Menu()
{
	this->canChangeOption = true;
	this->setFont();
	this->menuText = new sf::Text[3];
	this->currentMenuOption = 0;
	this->initMenuOptions();
	this->delayMenu.restart();
}

Menu::~Menu()
{
	delete[] this->menuText;
}

void Menu::setDelay()
{
	this->canChangeOption = false;
	this->delayMenu.restart();
	while (this->delayMenu.getElapsedTime().asSeconds() <= 0.25f)
	{

	}
}

void Menu::setFont()
{
	this->fontMenu.loadFromFile("fonts/PixellettersFull.ttf");
}

int Menu::getPressedOption()
{
	return this->currentMenuOption;
}

void Menu::moveUp()
{
	this->checkCanChangeOption();

	if (this->currentMenuOption - 1 >= 0 && this->canChangeOption) {
		this->menuText[this->currentMenuOption].setFillColor(sf::Color::White);
		this->currentMenuOption--;
		this->menuText[this->currentMenuOption].setFillColor(sf::Color::Red);
		this->canChangeOption = false;
	}
}

void Menu::moveDown()
{
	this->checkCanChangeOption();

	if (this->currentMenuOption + 1 < 3 && this->canChangeOption) {
		this->menuText[this->currentMenuOption].setFillColor(sf::Color::White);
		this->currentMenuOption++;
		this->menuText[this->currentMenuOption].setFillColor(sf::Color::Red);
		this->canChangeOption = false;
	}
	
}


void Menu::render(sf::RenderTarget &target)
{
	for (int i = 0; i < 3; i++) {
		target.draw(this->menuText[i]);
	}
}
