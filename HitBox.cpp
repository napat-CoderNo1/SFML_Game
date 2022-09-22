#include "HitBox.h"

HitBox::HitBox(float offset_x, float offset_y, Vector2f size, Vector2f playerPosition)
{
	//เซตตำเเหน่งของhitbox
	hitbox.setPosition(playerPosition.x + offset_x, playerPosition.y + offset_y);
	//ส่วนของไซส์กล่อง
	hitbox.setSize(size);
	hitbox.setOrigin(hitbox.getSize() / 2.f);
	//ส่วนของสีกล่อง
	hitbox.setFillColor(Color::Transparent);
	hitbox.setOutlineThickness(1.f);
	hitbox.setOutlineColor(Color::Transparent);
}

HitBox::~HitBox()
{
}

void HitBox::update(Vector2f playerPosition, float offset_x, float offset_y)
{
	hitbox.setPosition(playerPosition.x + offset_x, playerPosition.y + offset_y);
}

void HitBox::draw(RenderTarget* target)
{
	target->draw(this->hitbox);
}

sf::FloatRect HitBox::getGobalBounds()
{
 	return this->hitbox.getGlobalBounds();
}
