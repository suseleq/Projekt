#pragma once
#include "ClassCharacter.h"

class Bullet
{
private:
	sf::Sprite shape;
	sf::Vector2f directions;
	float angle;
	float movementSpeed;
	float distance;
	float maxDistance;
	//Private functions
	


public:
	Bullet();
	Bullet(sf::Texture* texture, sf::Vector2f position, sf::Vector2f directionPar, float movementSpeedPar, float maxDistancePar);
	~Bullet();

	const sf::FloatRect getBounds() const;
	bool checkBounds();
	sf::Sprite getSprite();

	bool checkMaxDistance();
	void uptade();
	void render(sf::RenderTarget* target);
	
};

