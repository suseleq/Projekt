#include "ClassCharacter.h"

void ClassCharacter::Animations()
{
	if ((this->clock.getElapsedTime().asSeconds() >= 0.25f && !isMoving)
		|| (this->clock.getElapsedTime().asSeconds() >= 0.1f && isMoving)) {

		this->currentFrame.left += 16.f;
		if (currentFrame.left >= 64.f)
			this->currentFrame.left = 0;

		this->clock.restart();
		this->character.setTextureRect(this->currentFrame);

	}
}

bool ClassCharacter::checkBounds(const float dirX, const float dirY)
{
	sf::Vector2f position = this->getPosition();
	
	if (position.x - this->movementSpeed > 170.f && dirX == -1)
	{
		if (position.y < 140 && position.x - this->movementSpeed < 692.f)
			return false;
		else
			return true;
	}

	if (position.x + this->movementSpeed < 1284.f && dirX == 1) {
		if (position.y < 140 && position.x + this->movementSpeed > 760.f)
			return false;
		else
			return true;
	}
		

	if (position.y - this->movementSpeed > 80.f && dirY == -1) {
		if (position.x > 692.f && position.x < 760.f)
			return true;
		else if (position.y - this->movementSpeed > 140.f)
			return true;
		else
			return false;
	}

	if (position.y + this->movementSpeed < 730.f && dirY == 1)
		return true;
		
	return false;
}

ClassCharacter::ClassCharacter()  
{
	this->isMoving = false;
	this->canDodge = true;
}

ClassCharacter::~ClassCharacter()
{
	
}

void ClassCharacter::uptadeAnimation()
{
	if (!this->isMoving)
		this->character.setTexture(this->idleTextures);
	else
		this->character.setTexture(this->runTextures);

	this->Animations();
}

void ClassCharacter::uptade()
{
	this->uptadeAttack();
	this->uptadeAnimation();
}

void ClassCharacter::render(sf::RenderTarget& target)
{
	/*
		@void return void
		rendering character
	*/
	this->uptade();
	target.draw(this->character);
}

sf::Vector2f ClassCharacter::getPosition()
{
	//return Vector of position
	return sf::Vector2f(this->character.getPosition().x + 30.f,
		this->character.getPosition().y + 50.f);
}

void ClassCharacter::move(const float dirX, const float dirY)
{
	//Moving character
	if(this->checkBounds(dirX, dirY))
		this->character.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}

const bool ClassCharacter::getIsMoving() const
{
	return this->isMoving;
}

void ClassCharacter::setIsMoving(const bool isMovingPar)
{
	this->isMoving = isMovingPar;
}

float ClassCharacter::getAttackDistance()
{
	return this->attackRange;
}

const bool ClassCharacter::canAttack()
{
	if (this->cooldownAttack >= this->maxCooldownAttack) {
		this->cooldownAttack = 0.f;
		return true;
	}
	return false;
}

void ClassCharacter::uptadeAttack()
{
	if (this->cooldownAttack < this->maxCooldownAttack)
		this->cooldownAttack += 0.5f;
}

bool ClassCharacter::checkCanDodge()
{
	if (this->dodgeDelay.getElapsedTime().asSeconds() >= 5.f) {
		this->canDodge = true;
	}

	return this->canDodge;
}

void ClassCharacter::dodge(const float dirX, const float dirY)
{
	if (this->canDodge) {
		if (this->character.getPosition().x + dirX < 1284.f
			&& this->character.getPosition().x + dirX > 170.f
			&& this->character.getPosition().y + dirY < 730.f
			&& this->character.getPosition().y + dirY > 140.f)
		{
			this->character.move(dirX, dirY);
			this->canDodge = false;
			this->dodgeDelay.restart();
		}
	}
}

void ClassCharacter::setPosition(float posX, float posY)
{
	this->character.setPosition(posX, posY);
}

bool ClassCharacter::coolisionBullet(sf::Sprite& bullet)
{
	return this->character.getGlobalBounds().intersects(bullet.getGlobalBounds());
}
