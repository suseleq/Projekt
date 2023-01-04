#include "Enemies.h"

void Enemies::animation()
{
	if ((this->clock.getElapsedTime().asSeconds() >= 0.165f && !isMoving)
		|| (this->clock.getElapsedTime().asSeconds() >= 0.165f && isMoving)) {

		this->currentFrame.left += 16.f;
		if (currentFrame.left >= 96.f)
			this->currentFrame.left = 0;

		this->clock.restart();
		this->sprite.setTextureRect(this->currentFrame);

	}
}


Enemies::Enemies()
{
	this->isMoving = false;
	this->movementSpedd = 2.f;
}

Enemies::~Enemies()
{
}

bool Enemies::collisionBullet(sf::Sprite bullet)
{
	return this->sprite.getGlobalBounds().intersects(bullet.getGlobalBounds());
}

void Enemies::takeDamage()
{
	this->life--;
}

int Enemies::getLife()
{
	return this->life;
}

void Enemies::setPostion(float x, float y)
{
	this->isMoving = true;
	this->setPostion(x * this->movementSpedd, y * movementSpedd);
}

sf::Vector2f Enemies::getPosition()
{
	return this->sprite.getPosition();
}

void Enemies::uptade()
{
	this->animation();
}

void Enemies::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
