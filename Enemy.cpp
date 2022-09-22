#include "Enemy.h"

Enemy::Enemy(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float pos_x, float pos_y):
	animation(texture, imageCount, switchTime)
{
	this->enemy.setPosition(pos_x, pos_y);
	
	this->speed = speed;
	row = 0;
	faceRight = true;

	enemy.setSize(sf::Vector2f(164.0f, 57.0f));
	enemy.setOrigin(enemy.getSize() / 2.0f);
	enemy.setScale(2, 2);
	//enemy.setPosition(300.0f, 0.0f);
	enemy.setTexture(texture);

	initVariables();

	//กำหนดขนาดhitbox enemy
	hitboxEnemy = new HitBox(0, 0, Vector2f(10, 40), this->enemy.getPosition());
	hitboxEnemy2 = new HitBox(0, 0, Vector2f(50, 100), this->enemy.getPosition());

}

Enemy::~Enemy()
{
}

void Enemy::update(float deltaTime, Player* player)
{
	//sf::Vector2f  movement(0.0f, 0.0f);
	this->move(player);
	animation.update(row, deltaTime, faceRight); // ถ้าไม่มีจะไม่มี Animation
	enemy.setTextureRect(animation.uvRect); // ถ้าไม่มีจะไม่ตัดสไปร์ท
	//body.move(movement);

	if (colorClock.getElapsedTime().asSeconds() >= 0.1f)
	{
		enemy.setFillColor(sf::Color(255, 255, 255, 255));
	}
}

void Enemy::draw(sf::RenderWindow& window)
{
	window.draw(enemy);
}

void Enemy::move(Player* player)
{
	if (abs(enemy.getPosition().x - player->GetPosition().x ) <= 1000/*400*/ )
	{
		if (abs(enemy.getPosition().x - player->GetPosition().x ) <= 1070/*470*/ )
		{
			//printf("Hello");
			if (enemy.getPosition().x > player->GetPosition().x + 100.0f)
			{
				enemy.move(-0.1f, 0.0f);
				row = 1;
				faceRight = true;
			}
			else if (enemy.getPosition().x <= player->GetPosition().x -110.0f)
			{
				//printf("Hello");
				enemy.move(0.1f, 0.0f);
				row = 1;
				faceRight = false;
			}
			if (enemy.getPosition().y > player->GetPosition().y)
			{
				enemy.move(0.0f, -0.1f);
				//row = 1;
			}
			else if (abs(enemy.getPosition().y) < abs(player->GetPosition().y))
			{
				enemy.move(0.0f, 0.1f);
				//row = 1;
			}
		}
	}
}

void Enemy::setPosition(float pos_x, float pos_y)
{
	enemy.setPosition(pos_x, pos_y);
}

void Enemy::render(sf::RenderTarget* target)
{
	hitboxEnemy->draw(target);
	hitboxEnemy2->draw(target);
}

void Enemy::setColor()
{
	enemy.setFillColor(sf::Color(255,0,0,128));
	colorClock.restart();
}

void Enemy::initVariables()
{
	this->hp = 1200;
}

void Enemy::decreaseHP()
{
	this->hp -= 10;
}

void Enemy::decreaseHpbyBullet()
{
	this->hp -= 60;
}

int Enemy::returnHP()
{
	return this->hp;
}

sf::FloatRect Enemy::getGobalBounds()
{
	return this->enemy.getGlobalBounds();
}
