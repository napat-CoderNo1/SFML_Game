#include "Boss1.h"

Boss1::Boss1(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float pos_x, float pos_y):
	animation(texture, imageCount, switchTime)
{
	this->boss1.setPosition(pos_x, pos_y);

	this->speed = speed;
	row = 0;
	faceRight = true;

	boss1.setSize(sf::Vector2f(164.0f, 57.0f));
	boss1.setOrigin(boss1.getSize() / 2.0f);
	boss1.setScale(2, 6);
	//enemy.setPosition(300.0f, 0.0f);
	boss1.setTexture(texture);

	initVariables();

	//กำหนดขนาดhitbox enemy
	hitboxbossOne = new HitBox(0, 0, Vector2f(50, 40), this->boss1.getPosition());
	hitboxbossOne2 = new HitBox(0, 0, Vector2f(100, 200), this->boss1.getPosition());
}

Boss1::~Boss1()
{
}

void Boss1::update(float deltaTime, Player* player)
{
	//sf::Vector2f  movement(0.0f, 0.0f);
	this->move(player);
	animation.update(row, deltaTime, faceRight); // ถ้าไม่มีจะไม่มี Animation
	boss1.setTextureRect(animation.uvRect); // ถ้าไม่มีจะไม่ตัดสไปร์ท
	//body.move(movement);

	if (colorClock.getElapsedTime().asSeconds() >= 0.1f)
	{
		boss1.setFillColor(sf::Color(255, 255, 255, 255));
	}
}

void Boss1::draw(sf::RenderWindow& window)
{
	window.draw(boss1);
}

void Boss1::move(Player* player)
{
	if (abs(boss1.getPosition().x - player->GetPosition().x) <= 1000/*400*/)
	{
		if (abs(boss1.getPosition().x - player->GetPosition().x) <= 1070/*470*/)
		{
			//printf("Hello");
			if (boss1.getPosition().x > player->GetPosition().x + 100.0f)
			{
				boss1.move(-0.1f, 0.0f);
				row = 0;
				faceRight = true;
			}
			else if (boss1.getPosition().x <= player->GetPosition().x - 110.0f)
			{
				//printf("Hello");
				boss1.move(0.1f, 0.0f);
				row = 0;
				faceRight = false;
			}
			if (boss1.getPosition().y > player->GetPosition().y)
			{
				boss1.move(0.0f, -0.1f);
				//row = 1;
			}
			else if (abs(boss1.getPosition().y) < abs(player->GetPosition().y))
			{
				boss1.move(0.0f, 0.1f);
				//row = 1;
			}
		}
	}
}

void Boss1::setPosition(float pos_x, float pos_y)
{
	boss1.setPosition(pos_x, pos_y);
}

void Boss1::render(sf::RenderTarget* target)
{
	hitboxbossOne->draw(target);
	hitboxbossOne2->draw(target);
}

void Boss1::setColor()
{
	boss1.setFillColor(sf::Color(255, 0, 0, 128));
	colorClock.restart();
}

sf::FloatRect Boss1::getGobalBounds()
{
	return this->boss1.getGlobalBounds();
}

void Boss1::initVariables()
{
	this->hp = 10000;
}

void Boss1::decreaseHP()
{
	this->hp -= 100;
}

void Boss1::decreaseHpbyBullet()
{
	this->hp -= 600;
}

int Boss1::returnHP()
{
	return this->hp;
}
