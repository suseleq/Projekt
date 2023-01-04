#pragma once
#include "ClassCharacter.h"


class Tile
{
private:

protected:
	sf::Sprite sprite;
public:
	Tile();
	Tile(float x, float y, sf::Texture& texture, sf::IntRect& textureRect);
	~Tile();

	void setTexture(sf::Texture &textur, sf::IntRect textureRect);

	void uptade();
	void render(sf::RenderTarget &target);
};

