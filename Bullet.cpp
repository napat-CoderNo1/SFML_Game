#include "Bullet.h"

Bullet::Bullet()
{
    rect.setSize(sf::Vector2f(40, 40));
    //rect.setPosition(0, 0);
    rect.setFillColor(sf::Color::Yellow);
}

Bullet::~Bullet()
{

}

void Bullet::update()
{
    if (direction == 1 && rect.getPosition().x > bulletRange-300)
    {
        rect.move(-bulletspeed, 0);
    }
    else if (direction == 2 && rect.getPosition().x < bulletRange+300)
    {
        rect.move(bulletspeed, 0);
    }
    else
    {
        bulletin = false;
    }
}
