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

#include"Player.h"
#include"Platform.h"
#include"Enemy.h"
#include"Collider.h"
#include"Menu.h"

class Bullet
{
public:
	Bullet();
	~Bullet();

    int direction = 2;
    bool bulletin = true;
    float bulletspeed = 2;
    int bulletdamage;
    int bulletfirerate;
    int bulletRange;
    sf::RectangleShape rect;
    void update();

private:

};

