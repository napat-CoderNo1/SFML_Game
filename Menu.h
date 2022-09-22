#pragma once
#include<SFML/Graphics.hpp>
#define MAX_ITEMS 5 // start leaderboard exit

class Menu
{
public:
	Menu(float width, float height);
	~Menu();

	void draw(sf::RenderWindow& window);
	void moveUp();
	void moveDown();
	int GetPressedItem() { return selectItem; }

	int selectItem = 0;
	sf::Font font;
	sf::Text menu[MAX_ITEMS];

private:

};