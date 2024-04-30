#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Bullet
{
private:
	sf::Sprite shape;

	sf::Vector2f direction;
	float movementSpeed;

public:
	Bullet(sf::Texture* texture, float posX, float posY, float dirX, float dirY, float movementSpeed);
	virtual ~Bullet();

	const sf::FloatRect getBounds() const;

	void update();
	void render(sf::RenderTarget* target);
};

