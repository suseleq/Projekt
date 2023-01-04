#pragma once
#include "Enemies.h"

class Goblin : public Enemies
{
private:
	void initTexture();
	void initSprite();

public:
	Goblin();
	~Goblin();
	
};

