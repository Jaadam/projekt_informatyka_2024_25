#pragma once
#include <SFML/Graphics.hpp>

class orzel {
private:
    sf::Sprite orzeu;
    sf::Texture orzeutekstura1;
    sf::Texture orzeutekstura2;
    sf::Clock textureClock;

public:
    orzel(float x_in, float y_in);

    void move(float offsetX, float offsetY);
    void draw(sf::RenderWindow& window);
    const sf::FloatRect getBounds() const;
    void changeTexture();
    sf::Vector2f getPosition() const;  // Dodana funkcja getPosition
    void setPosition(float x, float y); // Dodana funkcja setPosition
};
