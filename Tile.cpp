#include "Tile.h"

Tile::Tile()
{
}

Tile::Tile(float x, float y, sf::Texture& texture, sf::IntRect& textureRect)
{
	this->sprite.setTexture(texture);
	this->sprite.setTextureRect(textureRect);
	this->sprite.setScale(3.f, 3.f);
	this->sprite.setPosition(x, y);
}

Tile::~Tile()
{
}

void Tile::setTexture(sf::Texture &texture, sf::IntRect textureRect)
{
	//this->sprite.setTexture(texture, false);
	//std::cout << this->sprite.getPosition().x << this->sprite.getPosition().y << "\n";
	this->sprite.setTextureRect(textureRect);
}

void Tile::uptade()
{
}

void Tile::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
