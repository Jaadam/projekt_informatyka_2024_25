#pragma once
#include "SFML/Graphics.hpp"
#define MAX_NUMBER_OF_ITEMS 2
class wyjscie
{
private:

	int wybranepole;
	sf::Font czcionka;
	sf::Text taknie[MAX_NUMBER_OF_ITEMS];
	sf::Text tekst;

public:
	wyjscie(float szerokosc, float wysokosc);
	~wyjscie();

	void draw(sf::RenderWindow& window);
	void strzalkalewo();
	void strzalkaprawo();
	int wybranaopcja() { return wybranepole; }
};

