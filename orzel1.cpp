#include "orzel1.h"

orzel::orzel(float x_in, float y_in) {
    if (!orzeutekstura1.loadFromFile("orzel1.png")) {}
    if (!orzeutekstura2.loadFromFile("orzel2.png")) {}
    orzeu.setTexture(orzeutekstura1);
    orzeu.setPosition(x_in, y_in);
    orzeu.setScale(0.2f, 0.2f);
}

void orzel::move(float offsetX, float offsetY) {
    // Obliczamy now¹ pozycjê Or³a
    sf::Vector2f newPos = orzeu.getPosition() + sf::Vector2f(offsetX, offsetY);

    // Sprawdzamy, czy nowa pozycja jest w dozwolonym zakresie na osi Y
    if (newPos.y >= 0 && newPos.y + orzeu.getGlobalBounds().height <= 720) { // 720 to wysokoœæ okna
        orzeu.move(offsetX, offsetY);
    }
}

void orzel::draw(sf::RenderWindow& window) {
    changeTexture(); // Aktualizacja tekstury
    window.draw(orzeu);
}

const sf::FloatRect orzel::getBounds() const {
    return orzeu.getGlobalBounds();
}

void orzel::changeTexture() {
    if (textureClock.getElapsedTime().asSeconds() >= 0.2f) {
        // Zmiana tekstury na naprzemienn¹
        if (orzeu.getTexture() == &orzeutekstura1) {
            orzeu.setTexture(orzeutekstura2);
        }
        else {
            orzeu.setTexture(orzeutekstura1);
        }
        textureClock.restart();
    }
}

// Dodana metoda getPosition
sf::Vector2f orzel::getPosition() const {
    return orzeu.getPosition();
}

// Dodana metoda setPosition
void orzel::setPosition(float x, float y) {
    orzeu.setPosition(x, y);
}
