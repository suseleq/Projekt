#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <cmath>
#include <random>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>


class ClassCharacter
{
protected:
	//Sprite/Textures
	sf::Sprite character;
	sf::Texture idleTextures;
	sf::Texture runTextures;
	sf::IntRect currentFrame;
	sf::Clock clock;
	
	//Class Stats
	float dexterity;
	float cooldownAttack;
	float maxCooldownAttack;
	float attackRange;

	float cooldownAbility;
	float maxCooldownAbility;

	//Movement
	float movementSpeed;
	bool canDodge;
	sf::Clock dodgeDelay;

	//Boolean
	bool isMoving;


	//Private functions
	virtual void initStats() = 0;
	virtual void initSprite() = 0;
	
	virtual void initTexture() = 0;
	void Animations();
	
	bool checkBounds(const float dirX, const float dirY);

public:
	ClassCharacter();
	virtual ~ClassCharacter();

	//Functions
	void uptadeAnimation();
	virtual void uptade();
	void render(sf::RenderTarget& target);

	sf::Vector2f getPosition();
	void move(const float dirX, const float dirY);

	const bool getIsMoving() const;
	void setIsMoving(const bool isMovingPar);

	float getAttackDistance();

	const bool canAttack();
	void uptadeAttack();

	bool checkCanDodge();
	void dodge(const float dirX, const float dirY);

	void setPosition(float posX, float posY);
		
	bool coolisionBullet(sf::Sprite &bullet);
};

