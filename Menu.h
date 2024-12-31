#pragma once
#include "SFML/Graphics.hpp"

#define MAX_NUMBER_OF_ITEMS 5

class Menu
{
public:
	Menu(float szerokosc, float wysokosc);
	~Menu();

	void draw(sf::RenderWindow& window);
	void drawbackground(sf::RenderTexture tlo);
	void strzalkagora();
	void strzalkadol();
	int wybranaopcja() { return wybranepole; }

private:
	int wybranepole;
	sf::Font czcionka;
	sf::Text menu[MAX_NUMBER_OF_ITEMS];
	sf::Texture tlo;


};