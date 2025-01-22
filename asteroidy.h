#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class Asteroidy {
private:
    sf::Sprite sprite;
    std::vector<sf::Texture> textures;  // Przechowywanie ró¿nych tekstur asteroid
    float speed;
    sf::Clock textureClock;
    int currentTextureIndex; // Indeks aktualnej tekstury

public:
    // Konstruktor
    Asteroidy(float startX, float startY, float velocity);

    // Funkcja aktualizuj¹ca pozycjê asteroidy i zmieniaj¹ca teksturê
    void update(float deltaTime);

    // Funkcja rysuj¹ca asteroidê
    void draw(sf::RenderWindow& window);

    // Funkcja sprawdzaj¹ca, czy asteroida wysz³a poza ekran
    bool isOffScreen() const;

    // Funkcja zwracaj¹ca granice asteroidy (do kolizji)
    sf::FloatRect getBounds() const;
    void move(float deltaTime);
private:
    // Funkcja do zmiany tekstury asteroidy
    void changeTexture();
};
