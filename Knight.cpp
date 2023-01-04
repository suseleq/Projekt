#include "Knight.h"

void Knight::initStats()
{
	/*
		@void return void
		initialize stats of Class
	*/
	this->dexterity = 1.f;
	this->cooldownAttack = 1.f;
	this->maxCooldownAttack = 10.f;
	this->movementSpeed = 4.f;
	this->maxCooldownAbility = 1.f;
	this->maxCooldownAbility = 1.f;
	this->attackRange = 2.5f;
	this->clock.restart();
}

void Knight::initSprite()
{
	/*
		@void return void
		initialize sprite and scalling
	*/

	this->character.setTexture(this->idleTextures);
	this->currentFrame = sf::IntRect(0, 0, 16, 28);
	this->character.setTextureRect(currentFrame);
	this->character.scale(3.f, 3.f);
}

void Knight::initTexture()
{
	if (!this->idleTextures.loadFromFile("Textures/knight_idle.png"))
		std::cout << "ERROR::KNIGHT::Could not load idle texture";
	if (!this->runTextures.loadFromFile("Textures/knight_run.png"))
		std::cout << "ERROR::KNIGHT::Could not load run texture";
}

Knight::Knight()
{
	this->initStats();
	this->initTexture();
	this->initSprite();
}

Knight::~Knight()
{
}
