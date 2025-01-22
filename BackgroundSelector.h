// BackgroundSelector.h
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class BackgroundSelector {
private:
    std::vector<sf::Texture> textures; // Lista tekstur
    sf::Sprite currentBackground; // Obecne t³o
    int currentIndex; // Indeks obecnie wybranego t³a
public:
    BackgroundSelector();
    void loadTextures(); // Za³aduj wszystkie tekstury
    void draw(sf::RenderWindow& window); // Rysowanie obecnego t³a
    void nextBackground(); // Zmiana t³a na nastêpne
    void previousBackground(); // Zmiana t³a na poprzednie
    sf::Sprite& getCurrentBackground(); // Zwróæ aktualne t³o
};
