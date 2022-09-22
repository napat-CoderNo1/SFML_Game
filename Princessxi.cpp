#include "Princessxi.h"

Princessxi::Princessxi(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed):
	animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	row = 0;
	faceRight = true;

	body.setSize(sf::Vector2f(164.0f, 55.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setScale(2, 2);
	body.setPosition(8000.0f, 0.0f);
	body.setTexture(texture);
}

Princessxi::~Princessxi()
{
}

void Princessxi::update(float deltaTime)
{
	sf::Vector2f  movement(0.0f, 0.0f);
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

void Princessxi::draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Princessxi::render(sf::RenderTarget* target)
{

}

sf::FloatRect Princessxi::getGobalBounds()
{
	return this->body.getGlobalBounds();
}

void Princessxi::setPosition(float x, float y)
{
	this->body.setPosition(x, y);
}
