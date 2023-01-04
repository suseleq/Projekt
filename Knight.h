#pragma once
#include "ClassCharacter.h"

class Knight : public ClassCharacter
{
private:
	void initStats();
	void initSprite();
	void initTexture();

public:
	Knight();
	~Knight();

};

