#include "bulletEnemy.h"

bulletEnemy::bulletEnemy()
{
    rect.setSize(sf::Vector2f(40, 40));
    //rect.setPosition(0, 0);
    rect.setFillColor(sf::Color(255, 0, 255,128));
}

bulletEnemy::~bulletEnemy()
{
}

void bulletEnemy::update()
{
    if (direction == 1 && rect.getPosition().x > bulletRange - 500)
    {
        rect.move(-bulletspeed, 0);
    }
    else if (direction == 2 && rect.getPosition().x < bulletRange + 500)
    {
        rect.move(bulletspeed, 0);
    }
    else
    {
        bulletin = false;
    }
}
