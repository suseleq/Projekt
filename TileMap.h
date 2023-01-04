#pragma once
#include "Tile.h"


class TileMap
{
private:
    sf::Texture floorTextures;
    sf::Texture wallTextures;
    sf::Texture leftWall;
    sf::Texture doorTexture;
    sf::IntRect currentTileTexture;
    
    std::random_device rd;
    std::uniform_int_distribution <int> dist;
    int randomNumber;

    bool doorOpen;

    float gridSizeF;
    unsigned gridSizeU;
    
    int layers;
    sf::Vector2i size;
    std::vector< std::vector< std::vector < Tile > > > map;

    void initTexture();

    void changeDoorTexture();
public:
   
    TileMap();
    ~TileMap();

    void openDoor();

    void uptade();
    void render(sf::RenderTarget& target);
};