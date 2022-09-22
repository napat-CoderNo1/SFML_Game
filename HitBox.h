#pragma once

#include<iostream>
#include<ctime>
#include<cstdlib>
#include<vector>

#include"SFML\System.hpp"
#include"SFML\Window.hpp"
#include"SFML\Graphics.hpp"
#include"SFML\Audio.hpp"
#include"SFML\Network.hpp"

using namespace sf;

class HitBox
{
public:
	HitBox(float offset_x, float offset_y, Vector2f size, Vector2f playerPosition);
	~HitBox();

	sf::RectangleShape hitbox;

	void update(Vector2f playerPosition, float offset_x, float offset_y);
	void draw(RenderTarget* target);

	//Accessor
	sf::FloatRect getGobalBounds();

private:

};