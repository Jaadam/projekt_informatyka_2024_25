#include "wyjscie.h"

wyjscie::wyjscie(float szerokosc, float wysokosc)
{
	if (!czcionka.loadFromFile("arial.ttf")) {}

	tekst.setFont(czcionka);
	tekst.setString("Czy napewno chcesz wyjsc???");
	tekst.setFillColor(sf::Color::Yellow);
	tekst.setPosition(sf::Vector2f(szerokosc / 5, 150));
	tekst.setCharacterSize(50);
	tekst.setStyle(sf::Text::Bold);

	taknie[0].setFont(czcionka);
	taknie[0].setFillColor(sf::Color::Red);
	taknie[0].setString("NIE");
	taknie[0].setPosition(sf::Vector2f(300, 500));
	taknie[0].setStyle(sf::Text::Bold);

	taknie[1].setFont(czcionka);
	taknie[1].setFillColor(sf::Color::White);
	taknie[1].setString("TAK");
	taknie[1].setPosition(sf::Vector2f(900, 500));
	taknie[1].setStyle(sf::Text::Bold);

	wybranepole = 0;
}

wyjscie::~wyjscie(){}

void wyjscie::draw(sf::RenderWindow& window)
{
	window.draw(tekst);//nag³ówek jest tu

	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(taknie[i]);
	}
}

void wyjscie::strzalkalewo()
{
	if (wybranepole - 1 >= 0)
	{
		taknie[wybranepole].setFillColor(sf::Color::White);
		wybranepole--;
		taknie[wybranepole].setFillColor(sf::Color::Red);
	}
}
void wyjscie::strzalkaprawo()
{
	if (wybranepole + 1 < MAX_NUMBER_OF_ITEMS)
	{
		taknie[wybranepole].setFillColor(sf::Color::White);
		wybranepole++;
		taknie[wybranepole].setFillColor(sf::Color::Red);
	}
}
