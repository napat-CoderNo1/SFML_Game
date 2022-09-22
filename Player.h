#pragma once
#include<SFML/Graphics.hpp>
#include"Animation.h"
#include"HitBox.h"
#include"Collider.h"

class Player
{
public:
	Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed);
	~Player();

	void update(float deltaTime);
	void draw(sf::RenderWindow& window);
	void render(sf::RenderTarget* target);

	// ประกาศ "ฟังก์ชั้น" returnHP ขึ้นมา ละให้ return เป็นค่า int 
	int returnHP();
	// "ฟังก์ชัน" นี้ทำให้ค่า hp ลดลง 10 ใน Player.cpp
	void decreaseHpByBoss();
	void decreaseHp();
	int hp;
	void plusHP();

	sf::RectangleShape body;
	Animation animation;
	unsigned int row;
	float speed;
	bool faceRight;
	int permissionOfAttack;
	int playerDirection = 2;
	void initVariables();

	sf::Vector2f GetPosition() { return body.getPosition(); }
	Collider GetCollider() { return Collider(body); }

	//Accessor
	sf::FloatRect getGobalBounds();
	void setPosition(float x,float y);

	//Hitbox
	HitBox* hitbox;
	HitBox* hitboxplayer2;

private:
	
};
