#include "Tlo.h"
#include <iostream>

Tlo::Tlo(const sf::RenderWindow& window, const std::vector<std::string>& texturePaths, float speed)
    : speed(speed), windowWidth(static_cast<float>(window.getSize().x)), currentTextureIndex(0) {

    // £adowanie tekstur z plików
    for (const auto& path : texturePaths) {
        sf::Texture texture;
        if (!texture.loadFromFile(path)) {
            std::cerr << "Nie mo¿na za³adowaæ pliku t³a: " << path << std::endl;
            return;
        }
        textures.push_back(texture);
    }

    if (textures.empty()) {
        std::cerr << "Brak tekstur t³a!" << std::endl;
        return;
    }

    // Ustawienie pierwszej tekstury
    changeTexture(currentTextureIndex);  // Ustawienie pierwszej tekstury
}

void Tlo::update(float deltaTime) {
    // Przesuniêcie sprite'ów w lewo
    float moveDistance = speed * deltaTime;
    sprite1.move(-moveDistance, 0);
    sprite2.move(-moveDistance, 0);

    // Zapêtlenie tekstury
    float textureWidthScaled = textures[currentTextureIndex].getSize().x * sprite1.getScale().x;

    if (sprite1.getPosition().x + textureWidthScaled <= 0) {
        sprite1.setPosition(sprite2.getPosition().x + textureWidthScaled, 0);
    }
    if (sprite2.getPosition().x + textureWidthScaled <= 0) {
        sprite2.setPosition(sprite1.getPosition().x + textureWidthScaled, 0);
    }
}

void Tlo::draw(sf::RenderWindow& window) {
    window.draw(sprite1);
    window.draw(sprite2);
}

void Tlo::changeTexture(size_t textureIndex) {
    // Sprawdzenie, czy indeks jest poprawny
    if (textureIndex < textures.size()) {
        currentTextureIndex = textureIndex;
        sf::Texture& texture = textures[currentTextureIndex];

        // Ustawienie tekstury dla sprite'ów
        sprite1.setTexture(texture);
        sprite2.setTexture(texture);

        // Prze³aduj skalowanie i pozycje sprite'ów
        float scaleFactorY = static_cast<float>(sprite1.getTexture()->getSize().y) / texture.getSize().y;
        sprite1.setScale(scaleFactorY, scaleFactorY);
        sprite2.setScale(scaleFactorY, scaleFactorY);
        sprite1.setPosition(0, 0);
        sprite2.setPosition(texture.getSize().x * scaleFactorY, 0);
    }
    else {
        std::cerr << "Niepoprawny indeks tekstury!" << std::endl;
    }
}
