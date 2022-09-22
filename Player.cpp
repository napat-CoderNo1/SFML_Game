#include "Player.h"

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed):
	animation(texture,imageCount,switchTime)
{
	this->speed = speed;
	row = 0;
	faceRight = true;

	body.setSize(sf::Vector2f(164.0f, 55.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setScale(2, 2);
	body.setPosition(0.0f, -100.0f);
	body.setTexture(texture);

	//กำหนดขนาด HITBOX
	hitbox = new HitBox(0, 0, Vector2f(90, 40), this->body.getPosition());
	hitboxplayer2 = new HitBox(0, 0, Vector2f(50, 100), this->body.getPosition());

	initVariables();
}

Player::~Player()
{
}

void Player::update(float deltaTime)
{
	sf::Vector2f  movement(0.0f, 0.0f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		movement.x -= speed * deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		movement.x += speed * deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		movement.y -= speed * deltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		movement.y += speed * deltaTime;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
	{
		movement.x = 0.0f;
		permissionOfAttack = 1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::K))
	{
		movement.x = 0.0f;
		permissionOfAttack = 2;
	}

	if (movement.x == 0.0f)
	{
		row = 0;
	}
	else
	{
		row = 1;

		if (movement.x > 0.0f)
		{
			faceRight = false;
			playerDirection = 2;
		}
		else
		{
			faceRight = true;
			playerDirection = 1;
		}
	}

	if (movement.x == 0.0f && permissionOfAttack == 1)
	{
		row = 2;
		permissionOfAttack = 0;
	}

	if (movement.x == 0.0f && permissionOfAttack == 2)
	{
		row = 3;
		permissionOfAttack = 0;
	}

	animation.update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
	body.move(movement);
}

void Player::draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Player::render(sf::RenderTarget* target)
{
	hitbox->draw(target);
	hitboxplayer2->draw(target);
}

int Player::returnHP()
{
	return this->hp;
}

void Player::decreaseHpByBoss()
{
	this->hp -= 100;
}

void Player::decreaseHp()
{
	this->hp -= 20;
}

void Player::plusHP()
{
	this->hp += 100;
}

void Player::initVariables()
{
	this->permissionOfAttack = 0;
	this->hp = 500;
}

sf::FloatRect Player::getGobalBounds()
{
	return this->body.getGlobalBounds();
}

void Player::setPosition(float x, float y)
{
	this->body.setPosition(x, y);
}
