#include "TileMap.h"

TileMap::TileMap()
{
	this->initTexture();
	this->gridSizeF = 48.f;
	this->layers = 1;
	this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
	this->size.x = 26;
	this->size.y = 16;
	this->currentTileTexture = sf::IntRect(0, 0, 16, 16);
	this->dist = std::uniform_int_distribution<int>(0, 7);
	

	this->map.resize(this->size.x);

	for (int x = 0; x < this->size.x; x++)
	{
		this->map.push_back(std::vector <std::vector <Tile>>());

		for (int y = 0; y < this->size.y; y++)
		{
			this->map[x].resize(this->size.y);

			this->map[x].push_back(std::vector<Tile>());
			
			for (int z = 0; z < this->layers; z++)
			{
				this->map[x][y].resize(this->layers);
				if (x == 0 || x == 25 || y == 0 || y == 1 || y == 15)
				{
					if (y == 0 && x == 12) 
						this->currentTileTexture = sf::IntRect(0, 0, 16, 16);
					else if(y == 0 && x == 13)
						this->currentTileTexture = sf::IntRect(16, 0, 16, 16);

					else if (y == 1 && x == 12)
						this->currentTileTexture = sf::IntRect(0, 16, 16, 16);

					else if (y == 1 && x == 13)
						this->currentTileTexture = sf::IntRect(16, 16, 16, 16);

					if((y == 0 || y == 1) && (x == 12 || x == 13))
						this->map[x][y].push_back(Tile(x * this->gridSizeF + 97.5f,
							y * this->gridSizeF + 40.f,
							this->doorTexture,
							this->currentTileTexture));

					if (y == 1 && x != 0 && x != 25)
						this->currentTileTexture = sf::IntRect(0, 0, 16, 16);
					else if (x == 25 && y != 0)
						this->currentTileTexture = sf::IntRect(48, 0, 16, 16);
					else if(y == 15 && x != 0 && x != 25)
						this->currentTileTexture = sf::IntRect(0, 0, 16, 16);
					else if(x == 0 && y != 0)
						this->currentTileTexture = sf::IntRect(32, 0, 16, 16);

					if (y != 0) {
						if (!(y == 1 && (x == 12 || x == 13)))
							this->map[x][y].push_back(Tile(x * this->gridSizeF + 97.5f,
								y * this->gridSizeF + 40.f,
								this->wallTextures,
								this->currentTileTexture));
					}
						

				}
				else
				{
					this->randomNumber = this->dist(rd);
					
					if (this->randomNumber < 4)
						this->currentTileTexture = sf::IntRect(16 * this->randomNumber, 0, 16, 16);
					else
						this->currentTileTexture = sf::IntRect(16 * (this->randomNumber - 4), 16, 16, 16);
					

					this->map[x][y].push_back(Tile(x * this->gridSizeF + 97.5f,
						y * this->gridSizeF + 40.f,
						this->floorTextures,
						this->currentTileTexture));
				}
			}
		}
	}
}

TileMap::~TileMap()
{
}

void TileMap::openDoor()
{
	this->doorOpen = true;
	this->changeDoorTexture();
}

void TileMap::initTexture()
{
	if (!this->floorTextures.loadFromFile("Textures/floor.png"))
		std::cout << "ERROR::TILEMAP::Could not load floor texture\n";

	if (!this->wallTextures.loadFromFile("Textures/wall.png"))
		std::cout << "ERROR::TILEMAP::Could not load wall texture\n";

	if (!this->leftWall.loadFromFile("Textures/wall_left.png"))
		std::cout << "ERROR::TILEMAP::Could not load wall texture\n";

	if (!this->doorTexture.loadFromFile("Textures/door.png"))
		std::cout << "ERROR::TILEMAP::Could not load door texture\n";
}

void TileMap::changeDoorTexture()
{
	this->map[12][0][1].setTexture(this->doorTexture, sf::IntRect(32, 0, 16, 16));
	this->map[13][0][1].setTexture(this->doorTexture, sf::IntRect(48, 0, 16, 16));
	this->map[12][1][1].setTexture(this->doorTexture, sf::IntRect(32, 16, 16, 16));
	this->map[13][1][1].setTexture(this->doorTexture, sf::IntRect(48, 16, 16, 16));
}

void TileMap::uptade()
{
}

void TileMap::render(sf::RenderTarget& target)
{
	for (auto& x : this->map)
	{
		for (auto& y : x)
		{
			for (auto& z : y)
			{
				z.render(target);
			}
		}
	}
}



