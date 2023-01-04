#include "Bullet.h"

Bullet::Bullet()
{
	
}

Bullet::Bullet(sf::Texture* texture, sf::Vector2f position, sf::Vector2f directionPar, float movementSpeedPar, float maxDistancePar)
{
	this->shape.setTexture(*texture);
	this->shape.scale(2.5f, 2.5f);

	this->shape.setPosition(position.x, position.y);
	
	this->directions = directionPar;
	
	this->angle = atan2f(this->directions.y, this->directions.x) * 180.f / 3.14f + 45.f;
	this->shape.setRotation(this->angle);

	this->maxDistance = maxDistancePar;
	this->distance = 0;
	this->movementSpeed = movementSpeedPar;
}

Bullet::~Bullet()
{
}

const sf::FloatRect Bullet::getBounds() const
{
	return this->shape.getGlobalBounds();
}

bool Bullet::checkBounds()
{
	sf::Vector2f position = this->shape.getPosition();
	if (position.x - this->movementSpeed < 170.f)
		return true;

	if (position.x + this->movementSpeed > 1242.f)
		return true;

	if (position.y - this->movementSpeed < 80.f)
		return true;

	if (position.y + this->movementSpeed > 730.f)
		return true;

	return false;
}

sf::Sprite Bullet::getSprite()
{
	return this->shape;
}

bool Bullet::checkMaxDistance()
{
	return this->distance >= this->maxDistance;
}

void Bullet::uptade()
{
	//Movement
	this->distance += 0.1f;
	this->shape.move(this->directions * this->movementSpeed);
}

void Bullet::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
