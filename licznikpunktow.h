#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class licznikpunktow {
private:
    int wynik;  // Zmienna przechowuj¹ca wynik
    sf::Text napis;
    sf::Font font;
    void updateText();
public:
    licznikpunktow();  // Konstruktor
    void dodawaniepunktow(int punkty);  // Dodawanie punktów do wyniku
    void draw(sf::RenderWindow& window);  // Rysowanie tekstu
    int getPunkty() const;  // Zwraca liczbê punktów
    void setPunkty(int punkty);  // Ustawia liczbê punktów
};
