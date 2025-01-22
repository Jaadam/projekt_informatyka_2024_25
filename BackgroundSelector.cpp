// BackgroundSelector.cpp
#include "BackgroundSelector.h"

BackgroundSelector::BackgroundSelector() : currentIndex(0) {
    loadTextures();
    currentBackground.setTexture(textures[currentIndex]);
}

void BackgroundSelector::loadTextures() {
    // Za³aduj tekstury
    sf::Texture texture1, texture2, texture3;
    if (texture1.loadFromFile("background1.png")) {
        textures.push_back(texture1);
    }
    if (texture2.loadFromFile("background2.png")) {
        textures.push_back(texture2);
    }
    if (texture3.loadFromFile("background3.png")) {
        textures.push_back(texture3);
    }
}

void BackgroundSelector::draw(sf::RenderWindow& window) {
    window.draw(currentBackground);
}

void BackgroundSelector::nextBackground() {
    currentIndex = (currentIndex + 1) % textures.size();
    currentBackground.setTexture(textures[currentIndex]);
}

void BackgroundSelector::previousBackground() {
    currentIndex = (currentIndex - 1 + textures.size()) % textures.size();
    currentBackground.setTexture(textures[currentIndex]);
}

sf::Sprite& BackgroundSelector::getCurrentBackground() {
    return currentBackground;
}
