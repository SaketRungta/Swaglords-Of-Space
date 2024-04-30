#include "Enemy.h"
#include <iostream>

void Enemy::initVariables()
{
	asteroidType = rand() % 5 + 1;
	type = 0;
	speed = (float)asteroidType;
	hpMax = (int)asteroidType;
	hp = hpMax;
	damage = asteroidType * 2;
	points = asteroidType;
}

void Enemy::initTextures()
{
	switch (asteroidType)
	{
	case 1:
		if (!texture.loadFromFile("Textures/Asteroid_01.png"))
		{
			std::cout << "ERROR::Player::initTexture failed to load from Textures/Asteroid_01.png" << std::endl;
		}
		break;
	case 2:
		if (!texture.loadFromFile("Textures/Asteroid_02.png"))
		{
			std::cout << "ERROR::Player::initTexture failed to load from Textures/Asteroid_02.png" << std::endl;
		}
		break;
	case 3:
		if (!texture.loadFromFile("Textures/Asteroid_03.png"))
		{
			std::cout << "ERROR::Player::initTexture failed to load from Textures/Asteroid_03.png" << std::endl;
		}
		break;
	case 4:
		if (!texture.loadFromFile("Textures/Asteroid_04.png"))
		{
			std::cout << "ERROR::Player::initTexture failed to load from Textures/Asteroid_04.png" << std::endl;
		}
		break;
	case 5:
		if (!texture.loadFromFile("Textures/Asteroid_05.png"))
		{
			std::cout << "ERROR::Player::initTexture failed to load from Textures/Asteroid_05.png" << std::endl;
		}
		break;
	}
}

void Enemy::initShape()
{
	sprite.setTexture(texture);
	sprite.setScale(sf::Vector2f(0.3f, 0.3f));
}

Enemy::Enemy(float posX, float posY)
{
	initVariables();
	initTextures();
	initShape();

	sprite.setPosition(posX, posY);
}

Enemy::~Enemy()
{
}

const sf::FloatRect Enemy::getBounds() const
{
	return sprite.getGlobalBounds();
}

const int& Enemy::getPoints() const
{
	return points;
}

const int& Enemy::getDamage() const
{
	return damage;
}

void Enemy::update()
{
	sprite.move(0.f, speed);
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(sprite);
}
