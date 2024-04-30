#pragma once

#include <map>
#include <string>
#include <sstream>
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Powerups.h"

class Game
{
private:
	std::shared_ptr<sf::RenderWindow> window;

	std::map<std::string, std::unique_ptr<sf::Texture>> textures;
	unsigned bulletsCount;
	std::vector<std::unique_ptr<Bullet>> bullets;
	sf::Text remainingBulletsText;
	std::unique_ptr<Player> player;

	sf::Font font;
	unsigned points;
	sf::Text pointText;

	sf::Text gameOverText;

	sf::Texture worldBackgroundTex;
	sf::Sprite worldBackground;

	sf::RectangleShape playerHpBar;
	sf::RectangleShape playerHpBarBack;

	float spawnTimer;
	float spawnTimerMax;
	std::vector<std::unique_ptr<Enemy>> enemies;

	float powerupsSpawnTimer;
	float powerupsSpawnTimerMax;
	std::vector<std::unique_ptr<Powerups>> powerups;

	void initWindow();
	void initTextures();
	void initGUI();
	void initWorld();
	void initSystems();

	void initPlayer();
	void initEnemies();
	void initPowerups();

public:
	Game();
	virtual ~Game();

	void run();

	void updatePollEvents();
	void updateInput();
	void updateGUI();
	void updateWorld();
	void updateCollision();
	void updateBullets();
	void updateEnemies();
	void updateCombat();
	void updatePowerups();
	void update();

	void renderGUI();
	void renderWorld();
	void render();
};

