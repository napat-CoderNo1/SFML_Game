#pragma once
#include<SFML/Graphics.hpp>
#include"Animation.h"
#include"HitBox.h"
#include"Collider.h"

class Princessxi
{
public:
	Princessxi(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed);
	~Princessxi();

	void update(float deltaTime);
	void draw(sf::RenderWindow& window);
	void render(sf::RenderTarget* target);

	sf::RectangleShape body;
	Animation animation;
	unsigned int row;
	float speed;
	bool faceRight;
	int permissionOfAttack;
	int playerDirection = 2;

	sf::Vector2f GetPosition() { return body.getPosition(); }
	Collider GetCollider() { return Collider(body); }

	//Accessor
	sf::FloatRect getGobalBounds();
	void setPosition(float x, float y);
};

