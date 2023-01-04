#pragma once
#include "Enemies.h"

class Slime : public Enemies
{
private:

	void initTexture();
	void initSprite();


public:
	Slime();
	~Slime();

	void move(float dirX, float dirY);
};

