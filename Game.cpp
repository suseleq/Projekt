#include "Game.h"


void Game::initFonts()
{
	/*
		@void return void
		Initialize fonts
	*/

	if (!this->font.loadFromFile("fonts/PixellettersFull.ttf")) {
		std::cout << "ERROR::GAME::INITFONTS::Failed to load font!" << "\n";
	}
}


void Game::initWindow()
{
	/*
		@void return void
		Initialize window parameters
	*/

	this->icon.loadFromFile("Textures/knight.png");
	this->windowHeight = 900;
	this->windowWidth = 1440;
	this->window = new sf::RenderWindow(sf::VideoMode(windowWidth, windowHeight), "2D Game");
	this->window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	this->window->setFramerateLimit(60);
	this->view.setSize(float(this->windowWidth), float(this->windowHeight));
	this->view.setCenter(this->window->getSize().x / 2.f, this->window->getSize().y / 2.f);
}

void Game::initCharacter(int whichCharater)
{
	/*
		@void return void
		Initialize class of character
	*/

	if (whichCharater == 0)
		this->character = new Knight;
	else
		this->character = new Mage;
	
	this->character->setPosition(510.f, 600.f);
	
}

void Game::initTexture()
{
	/*
		@void return void
		Initialize Textures:
		- background of menu
		- crosshair
		- spritesheet tiles

		Setting texture to background
	*/
	this->textures["FLOOR"] = new sf::Texture();
	this->textures["FLOOR"]->loadFromFile("Textures/floor.png");

	this->textures["BACKGROUND"] = new sf::Texture();
	this->textures["BACKGROUND"]->loadFromFile("Textures/background.jpg");
	
	this->textures["CROSSHAIR"] = new sf::Texture();
	this->textures["CROSSHAIR"]->loadFromFile("Textures/crosshair.png");
	this->imageCursor = this->textures["CROSSHAIR"]->copyToImage();
	this->backgroung.setTexture(*this->textures["BACKGROUND"]);
	
	this->backgroung.scale(3.f, 2.5f);
}

void Game::initMap()
{
	this->map = new TileMap;
}

void Game::initBulletTextures(int whichCharater)
{
	/*
		@void return void
		Initialize textures of bullets depends of class
	*/

	if (whichCharater == 0) {
		this->textures["BULLET"] = new sf::Texture();
		this->textures["BULLET"]->loadFromFile("Textures/sword.png");
	}
	else
	{
		this->textures["BULLET"] = new sf::Texture();
		this->textures["BULLET"]->loadFromFile("Textures/fireball.png");
	}
}

sf::Vector2f Game::calculateDirection(sf::Vector2f position1, sf::Vector2f position2)
{
	sf::Vector2f direction = position1 - position2;
	direction = direction / float(sqrt(pow(direction.x, 2) + pow(direction.y, 2)));

	return direction;
}



Game::Game()
{
	this->gameMode = 0;
	this->initWindow();
	this->initFonts();
	this->initTexture();
	
}

Game::~Game()
{
	delete this->character;
	delete this->window;
	delete this->map;
	
	//Delete texture
	for (auto& i : this->textures) {
		delete i.second;
	}

	//Delete bullets
	for (auto* i : this->bullets) {
		delete i;
	}
	//Delete enemies
	for (auto* i : this->enemies) {
		delete i;
	}
}

void Game::run()
{
	while (this->window->isOpen()) {
		this->uptade();
		this->render();
	}
}

void Game::uptadePollEvent()
{
	/*
		@void return void
		Closing game
	*/

	sf::Event e;
	while (this->window->pollEvent(e)) {
		if (e.type == sf::Event::Closed) {
			this->window->close();
		}
	}

}


const sf::Vector2i Game::getMousePosition()
{
	/*
		@Vector2i return Vector2i of mouse position
	*/

	return sf::Mouse::getPosition(*this->window);
}

void Game::uptadeInputs()
{
	/*
		@void return void
		Culling inputs of game
	*/
	

	this->initEscpaeMenu();
	this->uptadeMovingCharacter();
	this->uptadeShootingCharacter();
	this->uptadeDodgeCharacter();
	
}

void Game::uptadeMovingCharacter()
{
	/*
		@void return void
		Moving character
		Setting isMoving to character
	*/

	this->character->setIsMoving(false);

	//Move Player
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		this->character->move(-1.f, 0.f);
		this->character->setIsMoving(true);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		this->character->move(1.f, 0.f);
		this->character->setIsMoving(true);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		this->character->move(0.f, -1.f);
		this->character->setIsMoving(true);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		this->character->move(0.f, 1.f);
		this->character->setIsMoving(true);
	}
}

void Game::uptadeShootingCharacter()
{
	/*
		@void return void
		Uptading shooting character
		Creating ne bullet
	*/

	//Shooting
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || (sf::Mouse::isButtonPressed(sf::Mouse::Left))) &&
		this->character->canAttack()) {
		
		this->bullets.push_back(new Bullet(this->textures["BULLET"],
			this->character->getPosition(),
			this->calculateDirection(sf::Vector2f(getMousePosition()), this->character->getPosition()),
			10.f,
			this->character->getAttackDistance()));
	}
}

void Game::uptadeDodgeCharacter()
{
	/*
		@void return void
		Uptading of dodge character
	*/

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && this->character->checkCanDodge()) {
		
		this->aimDir = sf::Vector2f(this->getMousePosition()) - this->character->getPosition();
		if (abs(this->aimDir.x) > 250.f)
			this->aimDirNorm.x = this->aimDir.x / float(sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2))) * 250.f;
		else
			this->aimDirNorm.x = this->aimDir.x;
		if (abs(this->aimDir.y) > 250.f)
			this->aimDirNorm.y = this->aimDir.y / float(sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2))) * 250.f;
		else
			this->aimDirNorm.y = this->aimDir.y;

		this->character->dodge(this->aimDirNorm.x, this->aimDirNorm.y);
	}
	

}

void Game::uptadeBullets()
{
	/*
		@void return void
		Uptading bullets:
		- moving bullets
		- deleting bullets
	*/


	unsigned counter = 0;
	for (auto* bullet : this->bullets) {
		bullet->uptade();

		//Bullet culling (top of screen)
		if (bullet->checkMaxDistance() || bullet->checkBounds()) {
			//Delete bullet
			this->deletingBullets(counter, 0);
			--counter;
		}
		++counter;
	}
}

void Game::uptadeEnemies()
{
	
	if (this->enemies.size() == 0 && !this->isOpenDoor)
	{
		this->isOpenDoor = true;
		this->map->openDoor();
		return;
	}

	int counter = 0;
	for (auto* enemy : this->enemies) {
		bool isDead = false;
		int counterBullet = 0;
		for (auto* bullet : this->bullets) {
			if (enemy->collisionBullet(bullet->getSprite()))
			{
				this->deletingBullets(counterBullet, 0);
				counterBullet--;

				enemy->takeDamage();
				if (enemy->getLife() <= 0) 
				{

					delete this->enemies.at(counter);
					this->enemies.erase(this->enemies.begin() + counter);
					counter--;
					isDead = true;
					break;
				}
			}
			counterBullet++;
		}
		if (!isDead)
			enemy->move(this->calculateDirection(this->character->getPosition(), enemy->getPosition()).x,
				this->calculateDirection(this->character->getPosition(), enemy->getPosition()).y);

		counter++;
	}

	//this->enemy->move(this->calculateDirection(this->character->getPosition(), this->enemy->getPosition()).x,
		//this->calculateDirection(this->character->getPosition(), this->enemy->getPosition()).y);
}

void Game::deletingBullets(int counter, int option)
{
	if(option == 0)
	{
		delete this->bullets.at(counter);
		this->bullets.erase(this->bullets.begin() + counter);
	}else if (option == 1)
	{

		for (auto* bullet : this->bullets) 
		{
			delete this->bullets.at(0);
			this->bullets.erase(this->bullets.begin() + counter);
		}
	}
}

void Game::deletingAllEnemies()
{
	for (auto* enemy : this->enemies)
	{
		delete this->enemies.at(0);
		this->enemies.erase(this->enemies.begin());
	}
}

void Game::uptadeMenu()
{
	/*
		@void return void
		Uptading main menu:
		- changing options
		- getting options
		- close game form main menu
		- initialize chooseMenu
	*/


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		this->menu.moveUp();

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		this->menu.moveDown();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
		if (this->menu.getPressedOption() == 0){
			this->initChooseMenu();
		}else if(this->menu.getPressedOption() == 2)
			this->window->close();
	}
}

void Game::uptadeChooseMenu()
{
	/*
		@void return void
		Uptading main menu:
		- changing options
		- getting character
		- initialize game
	*/


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
		this->chooseMenu.moveLeft();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
		
		this->chooseMenu.moveRight();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && 
		this->chooseMenu.checkCanChangeOption() 
		&& delay.getElapsedTime().asSeconds() >= 1.f) {
		this->initGame(this->chooseMenu.getPressedOption());
	}


	this->chooseMenu.uptade();
}

void Game::uptadeEscapeMenu()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		this->escapeMenu.moveUp();

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		this->escapeMenu.moveDown();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
		if (this->escapeMenu.getPressedOption() == 0) {
			this->gameMode = 2;
		}
		else if (this->escapeMenu.getPressedOption() == 1) {
			this->quitToMenu();
		}
	}
}

void Game::uptadeMap()
{
	if (this->isOpenDoor) {
		if(this->character->getPosition().y < 90.f)
		{
			this->character->setPosition(700.f, 600.f);
			this->map = new TileMap;
			this->isOpenDoor = false;
			this->initEnemies();
		}
	}

}

void Game::uptadeGame()
{
	/*
		@void return void
		Uptading game	
	*/
	this->character->uptade();
	this->uptadeInputs();
	this->uptadeBullets();
	this->uptadeEnemies();
	this->uptadeMap();
}

void Game::initChooseMenu()
{
	this->gameMode = 1;
	delay.restart();
}

void Game::initEscpaeMenu()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		this->escapeMenu.setCurrentOption(0);
		this->gameMode = 3;
	}
}

void Game::initGame(int whichCharater)
{
	this->randomEnemiesDist = std::uniform_int_distribution<int>(4, 7);
	this->isOpenDoor = false;
	this->initMap();
	this->gameMode = 2;
	this->cursor.loadFromPixels(this->imageCursor.getPixelsPtr(), this->imageCursor.getSize(), sf::Vector2u(0, 0));
	this->window->setMouseCursor(this->cursor);
	this->initBulletTextures(whichCharater);
	this->initCharacter(whichCharater);
}

void Game::initEnemies()
{
	this->maxEnemies = this->randomEnemiesDist(this->rd);
	std::cout << this->maxEnemies;
	for (size_t i = 0; i < this->maxEnemies; i++)
	{
		this->enemies.push_back(new Slime);
	}
}

void Game::quitToMenu()
{
	this->deletingAllEnemies();
	this->deletingBullets(0, 1);
	this->gameMode = 0;
	this->menu.setDelay();
}

void Game::renderMenu()
{
	this->window->draw(this->backgroung);
	this->menu.render(*this->window);
}

void Game::renderChooseMenu()
{
	this->window->draw(this->backgroung);
	this->chooseMenu.render(*this->window);
}

void Game::renderEscapeMenu()
{
	this->window->draw(this->backgroung);
	this->escapeMenu.render(*this->window);
}

void Game::renderGame()
{
	this->map->render(*this->window);

	this->character->render(*this->window);
	//this->enemy->render(*this->window);
	for (auto* bullet : this->bullets) {
		bullet->render(this->window);
	}
	for (auto* enemy : this->enemies) {
		enemy->render(*this->window);
	}
	
}

void Game::uptade()
{
	/*
		@void return void
		Uptading game
		TODO: idle animations
	*/
	this->uptadePollEvent();

	switch (this->gameMode)
	{
	case 0:
		this->uptadeMenu();
		break;
	case 1:
		this->uptadeChooseMenu();
		break;
	case 2:
		this->uptadeGame();
		break;
	case 3:
		this->uptadeEscapeMenu();
		break;
	default:
		break;
	}


}

void Game::render()
{
	/*
		@void return void
		Render game
	*/


	this->window->clear();

	switch (this->gameMode){
	case 0:
		this->renderMenu();
		break;
	case 1:
		this->renderChooseMenu();
		break;
	case 2:
		this->renderGame();
		break;
	case 3:
		this->renderEscapeMenu();
		break;
	default:
		break;
	}
	
	this->window->setView(this->view);
	this->window->display();
}
