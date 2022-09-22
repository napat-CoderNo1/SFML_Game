#include "EnemyShooter.h"

EnemyShooter::EnemyShooter(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float pos_x, float pos_y):
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
	hitboxEnemy2 = new HitBox(0, 0, Vector2f(50, 100), this->enemy.getPosition());
	hitboxAttackEnemyShooter = new HitBox(0, 0, Vector2f(550, 30), this->enemy.getPosition());

}

EnemyShooter::~EnemyShooter()
{

}

void EnemyShooter::update(float deltaTime, Player* player)
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

void EnemyShooter::draw(sf::RenderWindow& window)
{
	window.draw(enemy);
}

void EnemyShooter::move(Player* player)
{
	if (abs(enemy.getPosition().x - player->GetPosition().x) <= 1000/*400*/)
	{
		if (abs(enemy.getPosition().x - player->GetPosition().x) <= 1070/*470*/)
		{
			//printf("Hello");
			if (enemy.getPosition().x > player->GetPosition().x + 350.0f)
			{
				enemy.move(-0.1f, 0.0f);
				row = 1;
				faceRight = true;
				enemyShootDirection = 1;
			}
			else if (enemy.getPosition().x < player->GetPosition().x - 350.0f)
			{
				//printf("Hello");
				enemy.move(0.1f, 0.0f);
				row = 1;
				faceRight = false;
				enemyShootDirection = 2;
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

void EnemyShooter::setPosition(float pos_x, float pos_y)
{
	enemy.setPosition(pos_x, pos_y);
}

void EnemyShooter::render(sf::RenderTarget* target)
{
	hitboxEnemy2->draw(target);
	hitboxAttackEnemyShooter->draw(target);
}

void EnemyShooter::setColor()
{
	enemy.setFillColor(sf::Color(255, 0, 0, 128));
	colorClock.restart();
}

sf::FloatRect EnemyShooter::getGobalBounds()
{
	return this->enemy.getGlobalBounds();
}

void EnemyShooter::initVariables()
{
	this->hp = 1200;
}

void EnemyShooter::decreaseHP()
{
	this->hp -= 5;
}

void EnemyShooter::decreaseHpbyBullet()
{
	this->hp -= 600;
}

int EnemyShooter::returnHP()
{
	return this->hp;
}
