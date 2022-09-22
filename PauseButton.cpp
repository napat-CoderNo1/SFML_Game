#include "PauseButton.h"
#include<iostream>

PauseButton::PauseButton(float width, float height)
{
	if (!font.loadFromFile("font/FC Friday Medium Italic.otf"))
	{
		std::cout << "Failed" << std::endl;
	}

	menu[0].setFont(font);
	menu[0].setCharacterSize(72);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("Continue");
	menu[0].setOrigin(menu[0].getGlobalBounds().width / 2, menu[0].getGlobalBounds().height / 2);
	menu[0].setPosition(sf::Vector2f(width / 2, height / (MAX_ITEMS + 1) * 1));

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Exit");
	menu[1].setOrigin(menu[2].getGlobalBounds().width / 2, menu[2].getGlobalBounds().height / 2);
	menu[1].setPosition(sf::Vector2f(width / 2, height / (MAX_ITEMS + 1) * 2));
}

PauseButton::~PauseButton()
{
}

void PauseButton::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_ITEMS; i++)
	{
		window.draw(menu[i]);
	}
}

void PauseButton::moveUp()
{
	if (selectItem - 1 >= 0)
	{
		menu[selectItem].setFillColor(sf::Color::White);
		selectItem--;
		menu[selectItem].setFillColor(sf::Color::Red);

	}
}

void PauseButton::moveDown()
{
	if (selectItem + 1 < MAX_ITEMS)
	{
		menu[selectItem].setFillColor(sf::Color::White);
		selectItem++;
		menu[selectItem].setFillColor(sf::Color::Red);
	}
}
