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

class bulletEnemy
{
public:
	bulletEnemy();
	~bulletEnemy();

    int direction = 2;
    bool bulletin = true;
    float bulletspeed = 0.5;
    int bulletdamage;
    int bulletfirerate;
    int bulletRange;
    sf::RectangleShape rect;
    void update();

private:

};

