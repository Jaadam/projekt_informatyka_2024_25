#include <SFML/Graphics.hpp>
#include <string>

class TypingEffect {
    sf::Text text;
    sf::Font font;
    std::string fullText;
    std::string currentText;
    sf::Clock clock;
    sf::Time interval;
    size_t charIndex = 0;

public:
    TypingEffect(std::string textToDisplay, float intervalTime);
    void update();
    void draw(sf::RenderWindow& window);
    void showFullText();
    bool showAll = false;
};