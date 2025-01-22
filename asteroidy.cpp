#include "Asteroidy.h"

// Konstruktor klasy
Asteroidy::Asteroidy(float startX, float startY, float velocity) : speed(velocity), currentTextureIndex(0) {
    // Wczytanie tekstur
    sf::Texture texture1;
    sf::Texture texture2;
    if (texture1.loadFromFile("asteroida1.png")) {
        textures.push_back(texture1);
    }
    if (texture2.loadFromFile("asteroida2.png")) {
        textures.push_back(texture2);
    }

    // Ustawienie pocz¹tkowej tekstury
    if (!textures.empty()) {
        sprite.setTexture(textures[currentTextureIndex]);
    }
    sprite.setPosition(startX, startY);
    float randomScale = 0.1f + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / (1.5f - 0.3f)));

    // Ustawienie skali dla sprite'a (ta sama wartoœæ dla X i Y)
    sprite.setScale(randomScale, randomScale);
}

// Aktualizacja pozycji asteroidy oraz zmiana tekstury
void Asteroidy::update(float deltaTime) {
    // Ruch asteroidy w lewo
    sprite.move(-speed * deltaTime, 0);

    // Zmiana tekstury co 1 sekundê
    if (textureClock.getElapsedTime().asSeconds() > 1.0f) {
        changeTexture();
        textureClock.restart();
    }
}

// Rysowanie asteroidy na ekranie
void Asteroidy::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

// Sprawdzenie, czy asteroida wysz³a poza ekran
bool Asteroidy::isOffScreen() const {
    return sprite.getPosition().x + sprite.getGlobalBounds().width < 0;
}

// Funkcja do pobierania granic asteroidy
sf::FloatRect Asteroidy::getBounds() const {
    return sprite.getGlobalBounds();
}

// Zmiana tekstury asteroidy na kolejn¹
void Asteroidy::changeTexture() {
    if (!textures.empty()) {
        currentTextureIndex = (currentTextureIndex + 1) % textures.size();
        sprite.setTexture(textures[currentTextureIndex]);
    }
}
void Asteroidy::move(float deltaTime) {
    sprite.move(-speed * deltaTime, 0);
}