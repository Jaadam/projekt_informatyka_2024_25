#include "licznikpunktow.h"

licznikpunktow::licznikpunktow() : wynik(0) {
    if (!font.loadFromFile("arial.ttf")) {
        // Jeœli nie uda³o siê za³adowaæ czcionki, zostanie wyœwietlony tylko domyœlny tekst
    }
    napis.setFont(font);
    napis.setCharacterSize(24);
    napis.setFillColor(sf::Color::Yellow);
    napis.setPosition(5, 5);
    updateText();
}

void licznikpunktow::dodawaniepunktow(int punkty) {
    wynik += punkty;  // Dodaj punkty do wyniku
    updateText();  // Zaktualizuj tekst
}

void licznikpunktow::draw(sf::RenderWindow& window) {
    window.draw(napis);  // Rysuj tekst na ekranie
}

void licznikpunktow::updateText() {
    napis.setString("PUNKTY:  " + std::to_string(wynik));  // Uaktualnij tekst z wynikiem
}

int licznikpunktow::getPunkty() const {
    return wynik;  // Zwróæ wynik
}

void licznikpunktow::setPunkty(int punkty) {
    wynik = punkty;  // Ustaw wynik na przekazan¹ wartoœæ
    updateText();  // Zaktualizuj tekst
}
