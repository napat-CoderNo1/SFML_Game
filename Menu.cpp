#include "Menu.h"

#include<iostream>

Menu::Menu(float width, float height)
{
	if (!font.loadFromFile("font/FC Friday Medium Italic.otf"))
	{
		std::cout << "Failed" << std::endl;
	}
	menu[0].setFont(font);
	menu[0].setCharacterSize(50);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("Play");
	menu[0].setOrigin(menu[0].getGlobalBounds().width / 2, menu[0].getGlobalBounds().height / 2);
	menu[0].setPosition(sf::Vector2f(width / 2, height / (MAX_ITEMS + 1) * 2.5));

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::Black);
	menu[1].setString("Leaderboard");
	menu[1].setOrigin(menu[1].getGlobalBounds().width / 2, menu[1].getGlobalBounds().height / 2);
	menu[1].setPosition(sf::Vector2f(width / 2, height / (MAX_ITEMS + 1) * 3));

	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::Black);
	menu[2].setString("Exit");
	menu[2].setOrigin(menu[2].getGlobalBounds().width / 2, menu[2].getGlobalBounds().height / 2);
	menu[2].setPosition(sf::Vector2f(width / 2, height / (MAX_ITEMS + 1) * 3.5));

	menu[3].setFont(font);
	menu[3].setFillColor(sf::Color::Black);
	menu[3].setString("Credit");
	menu[3].setOrigin(menu[3].getGlobalBounds().width / 2, menu[3].getGlobalBounds().height / 2);
	menu[3].setPosition(sf::Vector2f(width / 2, height / (MAX_ITEMS + 1) * 4));

	menu[4].setFont(font);
	menu[4].setFillColor(sf::Color::Black);
	menu[4].setString("How to play");
	menu[4].setOrigin(menu[4].getGlobalBounds().width / 2, menu[4].getGlobalBounds().height / 2);
	menu[4].setPosition(sf::Vector2f(width / 2, height / (MAX_ITEMS + 1) * 4.5));
}

Menu::~Menu()
{
}

void Menu::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_ITEMS; i++)
	{
		window.draw(menu[i]);
	}
}

void Menu::moveUp()
{
	if (selectItem - 1 >= 0)
	{
		menu[selectItem].setFillColor(sf::Color::Black);
		selectItem--;
		menu[selectItem].setFillColor(sf::Color::Red);
	}
}

void Menu::moveDown()
{
	if (selectItem + 1 < MAX_ITEMS)
	{
		menu[selectItem].setFillColor(sf::Color::Black);
		selectItem++;
		menu[selectItem].setFillColor(sf::Color::Red);
	}
}
