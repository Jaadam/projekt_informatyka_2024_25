#include "Menu.h"

Menu::Menu(float szerokosc, float wysokosc) 
{
	if (!czcionka.loadFromFile("arial.ttf")) 
	{
		//niedziala
	}
	if (!tlo.loadFromFile("tlo.jpg"))
	{
		//hehe
	}
	menu[0].setFont(czcionka);
	menu[0].setFillColor(sf::Color::Cyan);
	menu[0].setString("NOWA GRA");
	menu[0].setPosition(sf::Vector2f(szerokosc / 2.5, 100));
	menu[0].setOutlineColor(sf::Color::White);
	menu[0].setOutlineThickness(1);

	menu[1].setFont(czcionka);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("WCZYTAJ");
	menu[1].setPosition(sf::Vector2f(szerokosc / 2.5, 200));
	menu[1].setOutlineColor(sf::Color::White);
	menu[1].setOutlineThickness(1);

	menu[2].setFont(czcionka);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("WYNIKI");
	menu[2].setPosition(sf::Vector2f(szerokosc / 2.5, 300));
	menu[2].setOutlineColor(sf::Color::White);
	menu[2].setOutlineThickness(1);

	menu[3].setFont(czcionka);
	menu[3].setFillColor(sf::Color::White);
	menu[3].setString("OPCJE");
	menu[3].setPosition(sf::Vector2f(szerokosc / 2.5, 550));
	menu[3].setOutlineColor(sf::Color::White);
	menu[3].setOutlineThickness(1);

	menu[4].setFont(czcionka);
	menu[4].setFillColor(sf::Color::White);
	menu[4].setString("ZAMKNIJ");
	menu[4].setPosition(sf::Vector2f(szerokosc / 2.5, 650));
	menu[4].setOutlineColor(sf::Color::White);
	menu[4].setOutlineThickness(1);
	wybranepole = 0;
}

Menu::~Menu(){}

void Menu::draw(sf::RenderWindow& window) 
{
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) 
	{
		window.draw(menu[i]);
	}
}
	
void Menu::strzalkagora()
{
	if (wybranepole - 1 >= 0)
	{
		menu[wybranepole].setFillColor(sf::Color::White);
		wybranepole--;
		menu[wybranepole].setFillColor(sf::Color::Cyan);
	}
}
void Menu::strzalkadol()
{
	if (wybranepole + 1 < MAX_NUMBER_OF_ITEMS)
	{
		menu[wybranepole].setFillColor(sf::Color::White);
		wybranepole++;
		menu[wybranepole].setFillColor(sf::Color::Cyan);
	}
}