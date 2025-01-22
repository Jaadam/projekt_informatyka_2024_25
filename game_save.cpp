#include "game_save.h"
#include <iostream>

void GameSave::saveGame(const orzel& o, const licznikpunktow& score, float elapsedTime, const std::string& filename) {
    std::ofstream outFile(filename);
    if (outFile.is_open()) {
        // Zapisujemy dane: pozycja Or³a, wynik, czas gry
        outFile << o.getPosition().x << " " << o.getPosition().y << "\n";  // Pozycja Or³a
        outFile << score.getPunkty() << "\n";  // Wynik
        outFile << elapsedTime << "\n";  // Czas gry
        outFile.close();
    }
}

bool GameSave::loadGame(orzel& o, licznikpunktow& score, float& elapsedTime, const std::string& filename) {
    std::ifstream inFile(filename);
    if (inFile.is_open()) {
        float posX, posY;
        int scoreValue;
        float timeElapsed;

        // Wczytujemy dane z pliku
        inFile >> posX >> posY;
        inFile >> scoreValue;
        inFile >> timeElapsed;

        // Ustawiamy wczytane dane w odpowiednich obiektach
        o.setPosition(posX, posY); // Ustawiamy pozycjê Or³a
        score.setPunkty(scoreValue); // Ustawiamy punkty w liczniku
        elapsedTime = timeElapsed; // Ustawiamy czas gry

        inFile.close();
        return true;
    }
    return false;
}
