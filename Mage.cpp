#include "Mage.h"

void Mage::initStats()
{
	/*
		@void return void
		initialize stats of Class
	*/

	this->dexterity = 1.f;
	this->cooldownAttack = 1.f;
	this->maxCooldownAttack = 40.f;
	this->movementSpeed = 3.f;
	this->maxCooldownAbility = 1.f;
	this->maxCooldownAbility = 1.f;
	this->attackRange = 4.5f;
	this->clock.restart();
}

void Mage::initSprite()
{
	/*
		@void return void
		initialize sprite and scalling
	*/
	this->character.setTexture(this->idleTextures);
	this->currentFrame = sf::IntRect(0 , 0, 16, 28);
	this->character.setTextureRect(currentFrame);
	this->character.scale(3.f, 3.f);
}

void Mage::initTexture()
{
	if (!this->idleTextures.loadFromFile("Textures/mage_idle.png"))
		std::cout << "ERROR::MAGE::Could not load idle texture";
	if (!this->runTextures.loadFromFile("Textures/mage_run.png"))
		std::cout << "ERROR::MAGE::Could not load run texture";

}

Mage::Mage()
{
	this->initStats();
	this->initTexture();
	this->initSprite();
}

Mage::~Mage()
{
}
