#pragma once
#include "ClassCharacter.h"

class Mage : public ClassCharacter
{
private:
	void initStats();
	void initSprite();
	void initTexture();

public:

	Mage();
	~Mage();
};

