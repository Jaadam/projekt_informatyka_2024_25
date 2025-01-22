#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>

class Tlo {
private:
    sf::Sprite sprite1;
    sf::Sprite sprite2;
    std::vector<sf::Texture> textures;  // Przechowywanie tekstur
    size_t currentTextureIndex;  // Indeks aktualnej tekstury
    float speed;  // Prêdkoœæ poruszania t³a
    float windowWidth;  // Szerokoœæ okna

public:
    Tlo(const sf::RenderWindow& window, const std::vector<std::string>& texturePaths, float speed);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    void changeTexture(size_t textureIndex);  // Zmiana tekstury na podstawie indeksu
    void setRandomTexture(const std::vector<std::string>& texturePaths);
};