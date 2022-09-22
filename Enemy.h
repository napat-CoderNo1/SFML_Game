#pragma once

#include<iostream>
#include<ctime>
#include<cstdlib>
#include<vector>

#include<SFML\System.hpp>
#include<SFML\Window.hpp>
#include<SFML\Graphics.hpp>
#include<SFML\Audio.hpp>
#include<SFML\Network.hpp>

#include"Animation.h"
#include"Player.h"
#include"Collider.h"
#include"HitBox.h"

class Enemy
{
public:
	Enemy(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float pos_x, float pos_y);
	~Enemy();

	void update(float deltaTime, Player* player);
	void draw(sf::RenderWindow& window);
	void move(Player* player);
	void setPosition(float pos_x, float pos_y);
	void render(sf::RenderTarget* target);
	
	void setColor();
	sf::Clock colorClock;
	
	//Hitbox
	HitBox* hitboxEnemy;
	HitBox* hitboxEnemy2;

	sf::RectangleShape enemy;
	Animation animation;
	unsigned int row;
	float speed;
	bool faceRight;

	sf::Vector2f GetPosition() { return enemy.getPosition(); }
	Collider GetCollider() { return Collider(enemy); }

	//Accessor
	sf::FloatRect getGobalBounds();

	//ส่วนของเลือด
	void initVariables();
	void decreaseHP();
	void decreaseHpbyBullet();
	int returnHP();
	int hp;

private:

};

