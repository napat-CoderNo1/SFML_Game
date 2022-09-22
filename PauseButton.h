#pragma once
#include<SFML/Graphics.hpp>
#define MAX_ITEMS 3 // start leaderboard exit

class PauseButton
{
public:
	PauseButton(float width, float height);
	~PauseButton();

	void draw(sf::RenderWindow& window);
	void moveUp();
	void moveDown();
	int GetPressedItem() { return selectItem; }

	int selectItem = 0;
	sf::Font font;
	sf::Text menu[MAX_ITEMS];

private:
};

