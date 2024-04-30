#include "Powerups.h"

void Powerups::initTextures()
{
	if (!healthRefillTexture.loadFromFile(std::string("Textures/HealthRefill.png")))
	{
		std::cout << "ERRO::Powerups::initTextures() Failed to load texture healthRefillTexture" << std::endl;
	}
	if (!bulletRefillTexture.loadFromFile(std::string("Textures/BulletRefill.png")))
	{
		std::cout << "ERRO::Powerups::initTextures() Failed to load texture bulletRefillTexture" << std::endl;
	}
}

Powerups::Powerups(PowerUpType inPowerUpType, float posX, float posY)
{
	powerUpType = inPowerUpType;

	initTextures();

	switch (inPowerUpType)
	{
	case HEALTH_REFILL:
		sprite.setTexture(healthRefillTexture);
		break;
	case BULLET_REFILL:
		sprite.setTexture(bulletRefillTexture);
		break;
	}

	sprite.setPosition(sf::Vector2f(posX, posY));
	sprite.setScale(sf::Vector2f(0.15f, 0.15f));
}

Powerups::~Powerups()
{
}

const sf::FloatRect Powerups::getBounds() const
{
	return sprite.getGlobalBounds();
}

const PowerUpType Powerups::getPowerUpType() const
{
	return powerUpType;
}

void Powerups::update()
{
	sprite.move(sf::Vector2f(0.f, 3.f));
}

void Powerups::render(sf::RenderTarget* target)
{
	target->draw(sprite);
}
