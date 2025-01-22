#include "TypingEffect.h"

TypingEffect::TypingEffect(std::string textToDisplay, float intervalTime)
    : fullText(textToDisplay), interval(sf::seconds(intervalTime))
{
    font.loadFromFile("fajnaczcionka.ttf");
    text.setFont(font);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::Green);
    text.setPosition(50, 50);
}

void TypingEffect::update() {
    if (charIndex < fullText.size() && clock.getElapsedTime() > interval) {
        currentText += fullText[charIndex++];
        text.setString(currentText);
        clock.restart();
    }
}

void TypingEffect::draw(sf::RenderWindow& window) {
    window.draw(text);
}
void TypingEffect::showFullText() {
    currentText = fullText; 
    charIndex = fullText.size(); 
    showAll = true; 
    text.setString(currentText);
}