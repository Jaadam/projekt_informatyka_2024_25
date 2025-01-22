#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Pauza
{
private:
    sf::RenderWindow* parentWindow; // WskaŸnik na g³ówne okno gry
    sf::Font font;                 // Czcionka dla tekstu
    sf::Text pauseText;            // Tekst wyœwietlany podczas pauzy
    bool isPaused;                 // Czy gra jest w stanie pauzy?

public:
    // Konstruktor
    Pauza(sf::RenderWindow* window);

    // Metoda zwracaj¹ca stan pauzy
    bool getIsPaused() const;

    // Prze³¹czanie pauzy
    void togglePause();

    // Obs³uga zdarzeñ
    void handleEvent(const sf::Event& event);

    // Rysowanie ekranu pauzy
    void draw(sf::RenderWindow& window);
};