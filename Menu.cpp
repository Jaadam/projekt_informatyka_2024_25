#include "Menu.h"

Menu::Menu(float szerokosc, float wysokosc) 
{
	if (!czcionka.loadFromFile("arial.ttf")) {	}

	tytul.setFont(czcionka);
	tytul.setString("__KAPITAN BOMBA__");
	tytul.setFillColor(sf::Color::Yellow);
	tytul.setPosition(sf::Vector2f(szerokosc / 4 +40, 150));
	tytul.setCharacterSize(50);
	tytul.setStyle(sf::Text::Bold);

	menu[0].setFont(czcionka);
	menu[0].setFillColor(sf::Color::Green);
	menu[0].setString("NOWA GRA");
	menu[0].setPosition(sf::Vector2f(szerokosc / 2.5, 350));
	menu[0].setStyle(sf::Text::Bold);

	menu[1].setFont(czcionka);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("WCZYTAJ");
	menu[1].setPosition(sf::Vector2f(szerokosc / 2.5, 425));
	menu[1].setStyle(sf::Text::Bold);

	menu[2].setFont(czcionka);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("WYNIKI");
	menu[2].setPosition(sf::Vector2f(szerokosc / 2.5, 500));
	menu[2].setStyle(sf::Text::Bold);
	

	menu[3].setFont(czcionka);
	menu[3].setFillColor(sf::Color::Red);
	menu[3].setString("ZAMKNIJ ALE NA CZERWONO");
	menu[3].setPosition(sf::Vector2f(szerokosc / 2.5, 575));
	menu[3].setStyle(sf::Text::Bold);

	menu[4].setFont(czcionka);
	menu[4].setFillColor(sf::Color::White);
	menu[4].setString("ZAMKNIJ");
	menu[4].setPosition(sf::Vector2f(szerokosc / 2.5, 650));
	menu[4].setStyle(sf::Text::Bold);
	
wybranepole = 0;
}

Menu::~Menu(){}



void Menu::draw(sf::RenderWindow& window) 
{
	window.draw(tytul);//nag³ówek jest tu

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
		menu[wybranepole].setFillColor(sf::Color::Green);
	}
}
void Menu::strzalkadol()
{
	if (wybranepole + 1 < MAX_NUMBER_OF_ITEMS)
	{
		menu[wybranepole].setFillColor(sf::Color::White);
		wybranepole++;
		menu[wybranepole].setFillColor(sf::Color::Green);
	}
}
