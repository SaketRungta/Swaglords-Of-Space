#include "Player.h"

void Player::initVariables()
{
	movementSpeed = 3.f;
	attackCooldownMax = 30.f;
	attackCooldown = attackCooldownMax;

	hpMax = 100;
	hp = hpMax;
}

void Player::initTexture()
{
	if (!texture.loadFromFile("Textures/SpaceFighter.png"))
	{
		std::cout << "ERROR::Player::initTexture failed to load from Textures/SpaceFighter.png" << std::endl;
	}
}

void Player::initSprite()
{
	sprite.setTexture(texture);
	sprite.setScale(sf::Vector2f(0.3f, 0.3f));
}

Player::Player()
{
	initVariables();
	initTexture();
	initSprite();
}

Player::~Player()
{
}

const sf::Vector2f& Player::getPos() const
{
	return sprite.getPosition();
}

const sf::FloatRect& Player::getBounds() const
{
	return sprite.getGlobalBounds();
}

const int& Player::getHp() const
{
	return hp;
}

const int& Player::getHpMax() const
{
	return hpMax;
}

void Player::setPosition(const sf::Vector2f pos)
{
	sprite.setPosition(pos);
}

void Player::setPosition(const float x, const float y)
{
	sprite.setPosition(x, y);
}

void Player::setHp(const int inHp)
{
	hp = inHp;
}

void Player::loseHp(const int value)
{
	hp = hp - value < 0 ? 0 : hp - value;
}

void Player::move(const float dirX, const float dirY)
{
	sprite.move(sf::Vector2f(movementSpeed * dirX, movementSpeed * dirY));
}

const bool Player::canAttack()
{
	if (attackCooldown >= attackCooldownMax)
	{
		attackCooldown = 0.f;
		return true;
	}

	return false;
}

void Player::updateAttack()
{
	if (attackCooldown < attackCooldownMax)
		attackCooldown += 0.5f;
}

void Player::update()
{
	updateAttack();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(sprite);
}
