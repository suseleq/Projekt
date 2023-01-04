#include "Goblin.h"

void Goblin::initTexture()
{
	if (!this->idleTexture.loadFromFile("Textures/goblin_idle.png"))
		std::cout << "ERROR::GOBLIN::Couldn't set idle textures";
	if (!this->runTexture.loadFromFile("Textures/goblin_run.png"))
		std::cout << "ERROR::GOBLIN::Couldn't set run textures";
}

void Goblin::initSprite()
{
	this->sprite.setTexture(this->idleTexture);
	this->currentFrame = sf::IntRect(0, 0, 16, 16);
	this->sprite.setTextureRect(currentFrame);
	this->sprite.scale(3.f, 3.f);
}

Goblin::Goblin()
{
	this->life = 5;
	this->initTexture();
	this->initSprite();
	this->clock.restart();
}

Goblin::~Goblin()
{
}
