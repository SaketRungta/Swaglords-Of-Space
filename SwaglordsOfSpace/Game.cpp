#include "Game.h"

void Game::initWindow()
{
	window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1920, 1080), "Swaglords of Space", sf::Style::Close | sf::Style::Titlebar);
	window->setFramerateLimit(144);
	window->setVerticalSyncEnabled(false);
}

void Game::initTextures()
{
	textures["BULLET"] = std::make_unique<sf::Texture>();
	textures["BULLET"]->loadFromFile("Textures/Bullet.png");
}

void Game::initGUI()
{
	if (!font.loadFromFile("Fonts/ethnocentric_rg.otf"))
		std::cout << "ERROR::Game::initGUI failed to load font" << std::endl;

	pointText.setFont(font);
	pointText.setCharacterSize(24);
	pointText.setFillColor(sf::Color::White);
	pointText.setString("Test");
	pointText.setPosition(sf::Vector2f(20.f, 55.f));

	remainingBulletsText.setFont(font);
	remainingBulletsText.setCharacterSize(24);
	remainingBulletsText.setFillColor(sf::Color::Cyan);
	remainingBulletsText.setPosition(sf::Vector2f(20.f, 80.f));

	gameOverText.setFont(font);
	gameOverText.setCharacterSize(108);
	gameOverText.setFillColor(sf::Color::Red);
	gameOverText.setString("Game Over!");
	gameOverText.setPosition(
		window->getSize().x / 2.f - gameOverText.getGlobalBounds().width / 2.f,
		window->getSize().y / 2.f - gameOverText.getGlobalBounds().height / 2.f);

	playerHpBar.setSize(sf::Vector2f(300.f, 25.f));
	playerHpBar.setFillColor(sf::Color::Red);
	playerHpBar.setPosition(sf::Vector2f(20.f, 20.f));

	playerHpBarBack = playerHpBar;
	playerHpBarBack.setFillColor(sf::Color::White);
}

void Game::initWorld()
{
	if (!worldBackgroundTex.loadFromFile("Textures/SpaceBG.jpg"))
		std::cout << "ERROR::Game::initWorld failed to load worldBackgroundTex" << std::endl;

	worldBackground.setTexture(worldBackgroundTex);
}

void Game::initSystems()
{
	points = 0;
}

void Game::initPlayer()
{
	bulletsCount = 30;

	player = std::make_unique<Player>();
	player->setPosition(sf::Vector2f(window->getSize().x / 2.f, window->getSize().y / 2.f));
}

void Game::initEnemies()
{
	spawnTimerMax = 45.f;
	spawnTimer = spawnTimerMax;
}

void Game::initPowerups()
{
	powerupsSpawnTimerMax = 900.f;
	powerupsSpawnTimer = 0.f;
}

Game::Game()
{
	initWindow();
	initTextures();
	initGUI();
	initWorld();
	initSystems();

	initPlayer();
	initEnemies();
	initPowerups();
}

Game::~Game()
{
}

void Game::run()
{
	while (window->isOpen())
	{
		updatePollEvents();

		if (player->getHp() > 0)
			update();

		render();
	}
}

void Game::updatePollEvents()
{
	sf::Event ev;
	while (window->pollEvent(ev))
	{
		if (ev.Event::type == sf::Event::Closed)
			window->close();
		else if (ev.Event::KeyPressed && ev.Event::key.code == sf::Keyboard::Escape)
			window->close();
	}
}

void Game::updateInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		player->move(-1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		player->move(1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		player->move(0.f, -1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		player->move(0.f, 1.f);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && player->canAttack() && bulletsCount > 0)
	{
		--bulletsCount;
		sf::Vector2f playerPos = player->getPos();
		playerPos.x += player->getBounds().width / 2.f;
		bullets.push_back(std::make_unique<Bullet>(textures["BULLET"].get(), playerPos.x, playerPos.y, 0.f, -1.f, 5.f));
	}
}

void Game::updateGUI()
{
	{
		std::stringstream ss;
		ss << "Points: " << points;
		pointText.setString(ss.str());

		float hpPercent = static_cast<float>(player->getHp()) / player->getHpMax();
		playerHpBar.setSize(sf::Vector2f(300.f * hpPercent, 25.f));
	}

	{
		std::stringstream ss;
		ss << "Bullets: " << bulletsCount;
		remainingBulletsText.setString(ss.str());
	}
}

void Game::updateWorld()
{
}

void Game::updateCollision()
{
	if (player->getBounds().left < 0.f)
	{
		player->setPosition(0.f, player->getBounds().top);
	}
	else if (player->getBounds().left + player->getBounds().width >= window->getSize().x)
	{
		player->setPosition(window->getSize().x - player->getBounds().width, player->getBounds().top);
	}

	if (player->getBounds().top < 0.f)
	{
		player->setPosition(player->getBounds().left, 0.f);
	}
	else if (player->getBounds().top + player->getBounds().height >= window->getSize().y)
	{
		player->setPosition(player->getBounds().left, window->getSize().y - player->getBounds().height);
	}
}

void Game::updateBullets()
{
	unsigned counter = 0;
	for (const auto& bullet_ptr : bullets)
	{
		Bullet* bullet = bullet_ptr.get();
		if (bullet == nullptr)
		{
			std::cout << "ERROR::Game::updateBullets bullet nullptr" << std::endl;
			continue;
		}

		bullet->update();

		if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
		{
			bullets.erase(bullets.begin() + counter);
		}

		counter += 1;
	}
}

void Game::updateEnemies()
{
	spawnTimer += 0.5f;
	if (spawnTimer >= spawnTimerMax)
	{
		enemies.push_back(std::make_unique<Enemy>((float)(rand() % window->getSize().x), -200.f));
		spawnTimer = 0.f;
	}

	unsigned counter = 0;
	for (const auto& enemy_ptr : enemies)
	{
		Enemy* currEnemy = enemy_ptr.get();
		if (currEnemy == nullptr)
		{
			std::cout << "ERROR::Game::updateEnemies currEnemy nullptr" << std::endl;
			continue;
		}

		currEnemy->update();

		if (currEnemy->getBounds().top > window->getSize().y)
		{
			enemies.erase(enemies.begin() + counter);
		}
		else if (currEnemy->getBounds().intersects(player->getBounds()))
		{
			player->loseHp(enemies.at(counter)->getDamage());
			enemies.erase(enemies.begin() + counter);
		}
		counter += 1;
	}
}

void Game::updateCombat()
{
	for (int i = 0; i < enemies.size(); ++i)
	{
		bool enemyHitByBullet = false;
		for (int k = 0; k < bullets.size() && !enemyHitByBullet; k++)
		{
			if (enemies[i]->getBounds().intersects(bullets[k]->getBounds()))
			{
				this->points += enemies[i]->getPoints();

				enemies.erase(enemies.begin() + i);

				bullets.erase(bullets.begin() + k);

				enemyHitByBullet = true;
			}
		}
	}
}

void Game::updatePowerups()
{
	powerupsSpawnTimer += 0.5f;
	if (powerupsSpawnTimer >= powerupsSpawnTimerMax)
	{
		PowerUpType powerUpType = rand() % 2 == 0 ? PowerUpType::BULLET_REFILL : PowerUpType::HEALTH_REFILL;
		powerups.push_back(std::make_unique<Powerups>(powerUpType, (float)(rand() % window->getSize().x), -200.f));
		powerupsSpawnTimer = 0.f;
	}

	unsigned counter = 0;
	for (const auto& powerup_ptr : powerups)
	{
		Powerups* currPowerup = powerup_ptr.get();
		if (currPowerup == nullptr)
		{
			std::cout << "ERROR::Game::updateEnemies currEnemy nullptr" << std::endl;
			continue;
		}

		currPowerup->update();

		if (currPowerup->getBounds().top > window->getSize().y)
		{
			powerups.erase(powerups.begin() + counter);
		}
		else if (currPowerup->getBounds().intersects(player->getBounds()))
		{
			PowerUpType powerUpType = currPowerup->getPowerUpType();
			switch (powerUpType)
			{
			case HEALTH_REFILL:
				player->setHp(100);
				break;
			case BULLET_REFILL:
				bulletsCount += 30;
				break;
			}

			powerups.erase(powerups.begin() + counter);
		}

		counter++;
	}
}

void Game::update()
{
	updateInput();
	player->update();
	updateCollision();
	updateBullets();
	updateEnemies();
	updateCombat();
	updateGUI();
	updateWorld();
	updatePowerups();
}

void Game::renderGUI()
{
	this->window->draw(pointText);
	this->window->draw(remainingBulletsText);
}

void Game::renderWorld()
{
	window->draw(worldBackground);
	window->draw(playerHpBarBack);
	window->draw(playerHpBar);
}

void Game::render()
{
	window->clear();

	renderWorld();

	player->render(*window);

	for (const auto& bullet_ptr : bullets)
	{
		Bullet* bullet = bullet_ptr.get();
		bullet->render(this->window.get());
	}

	for (const auto& enemy_ptr : enemies)
	{
		Enemy* currEnemy = enemy_ptr.get();
		currEnemy->render(this->window.get());
	}

	for (const auto& powerup_ptr : powerups)
	{
		Powerups* currPowerup = powerup_ptr.get();
		currPowerup->render(this->window.get());
	}

	if (player->getHp() <= 0)
		window->draw(gameOverText);

	renderGUI();

	window->display();
}
