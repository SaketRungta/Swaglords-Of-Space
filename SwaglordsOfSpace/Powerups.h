#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

enum PowerUpType
{
	HEALTH_REFILL,
	BULLET_REFILL
};

class Powerups
{
private:
	sf::Texture healthRefillTexture;
	sf::Texture bulletRefillTexture;

	sf::Sprite sprite;

	PowerUpType powerUpType;

	void initTextures();

public:
	Powerups(PowerUpType inPowerUpType, float posX, float posY);
	virtual ~Powerups();

	const sf::FloatRect getBounds() const;
	const PowerUpType getPowerUpType() const;

	void update();
	void render(sf::RenderTarget* target);
};

