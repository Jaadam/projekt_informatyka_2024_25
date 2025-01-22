#include "Pauza.h"

Pauza::Pauza(sf::RenderWindow* window)
    : parentWindow(window), isPaused(false)
{
    // Wczytanie czcionki (zast¹p "arial.ttf" œcie¿k¹ do rzeczywistego pliku czcionki)
    if (!font.loadFromFile("arial.ttf")) {
        throw std::runtime_error("Nie uda³o siê za³adowaæ czcionki.");
    }

    // Ustawienia tekstu pauzy
    pauseText.setFont(font);
    pauseText.setString("PAUZA\nWCISNIJ F1 BY KONTYNUOWAC");
    pauseText.setCharacterSize(40);
    pauseText.setFillColor(sf::Color::White);
    pauseText.setStyle(sf::Text::Bold);

    // Wyœrodkowanie tekstu na ekranie
    sf::Vector2u windowSize = parentWindow->getSize();
    sf::FloatRect textBounds = pauseText.getLocalBounds();
    pauseText.setPosition(
        (windowSize.x - textBounds.width) / 2,
        (windowSize.y - textBounds.height) / 2
    );
}

bool Pauza::getIsPaused() const {
    return isPaused;
}

void Pauza::togglePause() {
    isPaused = !isPaused;
}

void Pauza::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F1) {
        togglePause();
    }
}

void Pauza::draw(sf::RenderWindow& window) {
    if (isPaused) {
        window.draw(pauseText);
    }
}
