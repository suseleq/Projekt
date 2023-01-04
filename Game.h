#pragma once

#include "TileMap.h"
#include "Menu.h"
#include "ChooseCharacterMenu.h"
#include "Mage.h"
#include "Knight.h"
#include "Bullet.h"
#include "Goblin.h"
#include "Slime.h"
#include "EscapeMenu.h"

class Game
{
private:
	//Window
	sf::RenderWindow *window;
	unsigned windowWidth;
	unsigned windowHeight;
	sf::Image icon;
	
	int gameMode;
	
	sf::Cursor cursor;
	sf::Image imageCursor;
	sf::Sprite backgroung;

	sf::View view;
	
	//Map
	TileMap *map;
	bool isOpenDoor;

	//Menu
	Menu menu;
	ChooseCharacterMenu chooseMenu;
	EscapeMenu escapeMenu;

	//Character
	ClassCharacter *character;
	
	//Random
	std::random_device rd;
	std::uniform_int_distribution<int> randomEnemiesDist;
	
	//Enemies
	int maxEnemies;
	std::vector <Enemies*> enemies;

	//Resources
	std::map<std::string, sf::Texture*> textures;
	std::vector<Bullet*> bullets;
	sf::Vector2f aimDir;
	sf::Vector2f aimDirNorm;
	sf::Font font;
	sf::Clock delay;

	//Private functions
	void initFonts();
	void initWindow();
	void initCharacter(int whichCharater);
	void initTexture();
	void initMap();
	void initBulletTextures(int whichCharater);

	sf::Vector2f calculateDirection(sf::Vector2f position1, sf::Vector2f position2);
public:
	//Constructor/Destructor
	Game();
	~Game();

	//Functions
	void run();
	void uptadePollEvent();
	
	const sf::Vector2i getMousePosition();
	
	void uptadeInputs();
	void uptadeMovingCharacter();
	void uptadeShootingCharacter();
	void uptadeDodgeCharacter();
	void uptadeBullets();
	void uptadeEnemies();

	void deletingBullets(int counter, int option);
	void deletingAllEnemies();

	void uptadeMenu();
	void uptadeChooseMenu();
	void uptadeEscapeMenu();
	void uptadeMap();
	void uptadeGame();

	void initChooseMenu();
	void initEscpaeMenu();
	void initGame(int whichCharater);
	void initEnemies();
	void quitToMenu();

	void renderMenu();
	void renderChooseMenu();
	void renderEscapeMenu();
	void renderGame();

	void uptade();
	void render();

};

