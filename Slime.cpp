#include "Slime.h"

void Slime::initTexture()
{
	if (!this->idleTexture.loadFromFile("Textures/slime_idle.png"))
		std::cout << "ERROR::Slime::Couldn't set idle textures";
	if (!this->runTexture.loadFromFile("Textures/slime_run.png"))
		std::cout << "ERROR::Slime::Couldn't set run textures";
}

void Slime::initSprite()
{
	this->sprite.setTexture(this->idleTexture);
	this->currentFrame = sf::IntRect(0, 0, 16, 16);
	this->sprite.setTextureRect(currentFrame);
	this->sprite.scale(3.f, 3.f);
}

Slime::Slime()
{
	this->life = 3;

	this->initTexture();
	this->initSprite();
	this->clock.restart();
}

Slime::~Slime()
{
}

void Slime::move(float dirX, float dirY)
{
	this->sprite.move(dirX, dirY);
}
