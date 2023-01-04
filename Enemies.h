#pragma once
#include "ClassCharacter.h"

class Enemies
{
protected:
	sf::Texture idleTexture;
	sf::Texture runTexture;
	sf::IntRect currentFrame;
	sf::Sprite sprite;
	sf::Clock clock;

	float movementSpedd;

	int life;
	
	bool isMoving;

	virtual void initTexture() = 0;
	virtual void initSprite() = 0;

	void animation();

public:
	Enemies();
	~Enemies();
	
	bool collisionBullet(sf::Sprite sprite);
	void takeDamage();
	int getLife();

	virtual void move(float dirX, float dirY) = 0;
	void setPostion(float x, float y);
	sf::Vector2f getPosition();

	void uptade();
	void render(sf::RenderTarget& target);
};

