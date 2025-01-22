#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>  // Do zapisywania stanu gry
#include <memory>
#include <vector>
#include <random>
#include <ctime>
#include "Menu.h"
#include "orzel1.h"
#include "asteroidy.h"
#include "wyjscie.h"
#include "TypingEffect.h"
#include "licznikpunktow.h"
#include "Tlo.h"
#include "game_save.h"
#include <string>

void zapiszWynik(int wynik) {
    std::ifstream file("wynik.txt");

    int najlepszyWynik = 0;
    int poprzedniWynik = 0;

    // Jeœli plik istnieje, wczytujemy poprzednie wyniki
    if (file.is_open()) {
        file >> najlepszyWynik;
        file >> poprzedniWynik;
        file.close();
    }
    if (wynik != 0) {
        poprzedniWynik = wynik;
    }
    // Jeœli nowy wynik jest lepszy, nadpisujemy najlepszy wynik
    if (wynik > najlepszyWynik) {
        najlepszyWynik = wynik;
    }

    // Zapisujemy wyniki do pliku
    std::ofstream outputFile("wynik.txt");
    if (outputFile.is_open()) {
        outputFile << najlepszyWynik << "\n" << poprzedniWynik;
        outputFile.close();
    }
}

void wczytajWyniki(int& najlepszyWynik, int& poprzedniWynik) {
    std::ifstream file("wynik.txt");

    if (file.is_open()) {
        file >> najlepszyWynik;
        file >> poprzedniWynik;
        file.close();
    }
    else {
        najlepszyWynik = 0;
        poprzedniWynik = 0;
    }
}



// Funkcja do wczytywania stanu gry
void wczytajGre(licznikpunktow& scoreCounter, orzel& orzel)
{
    std::ifstream saveFile("game_save.txt");
    if (saveFile.is_open())
    {
        int punkty;
        float x, y;

        saveFile >> punkty; // Wczytaj punkty
        saveFile >> x >> y; // Wczytaj pozycjê Or³a

        // Ustawienia wczytanych danych
        scoreCounter.setPunkty(punkty); // Ustaw punkty w liczniku
        orzel.setPosition(x, y); // Ustaw pozycjê Or³a

        std::cout << "Gra wczytana! Punkty: " << punkty << " Pozycja Or³a: (" << x << ", " << y << ")" << std::endl;
    }
    else
    {
        std::cout << "Nie udalo sie wczytac stanu gry!" << std::endl;
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Kapitan D...Bomba");
    TypingEffect typing("Galaktyka Kurvix zostala opanowana przez zlych kosmitow.\n"
        "Pokonac ich moze tylko zaloga Gwiezdnego Patrolu\n"
        "na czele ktorej stoi \n"
        "Kapitan D...Bomba.\n\n\n\n\n"
        "MIEJSCE: OSIEDLE DLA STUDENTOW\n"
        "MISJA: ZROBIC PORZADEK\n\n\n"
        "Siadasz za sterami LEGENDARNEGO Orzela1\n"
        "Musisz dotrzec do planety .\n"
        "unikajac asteroid sterujac strzalkami Up Down\n"
        "Powodzenia Tepy \n\n\n\n"
        "*Nacisnij ENTER aby rozpoczac*", 0.12);
    Menu menu(window.getSize().x, window.getSize().y);
    orzel orzel(0, 360);
    wyjscie wyjscie(window.getSize().x, window.getSize().y);

    std::vector<std::string> backgrounds = { "background1.png", "background2.png", "background3.png" };

    // Tworzymy obiekt t³a
    Tlo background(window, backgrounds, 300.0f);  // Losowo wybrana tekstura na pocz¹tku

    bool menuglowne = true;
    bool ekranstart = false;
    bool nowagra = false;
    bool wczytaj = false;
    bool wyniki = false;
    bool opcje = false;
    bool potwierdzwyjscie = false;
    bool poprzednistan[6] = { false, false, false, false, false, false };
    float elapsedTime = 0.0f;  // Czas gry
    bool isGameLoaded = false; // Flaga wczytania gry
    static bool resultDisplayed = false;
    bool pauza = false;  // Flaga pauzy
    bool zapiszStan = false; // Flaga czy nale¿y zapisaæ stan gry
    bool glosowanie = false;

    sf::Text saveText;
    sf::Font font;
    font.loadFromFile("arial.ttf"); // Za³aduj font
    saveText.setFont(font);
    saveText.setCharacterSize(24);
    saveText.setFillColor(sf::Color::White);
    saveText.setPosition(400, 250);
    saveText.setString("F1   PAUZA\n\n\n\n\n\n\n\n Nacisnij F5 aby zapisac");

    sf::Clock clock;
    sf::Clock spawnClock;
    sf::Clock gameClock;
    sf::Clock updateClock;
    sf::Clock closeClock;

    sf::Text resultText;
    resultText.setFont(font);
    resultText.setCharacterSize(48); // Wielkoœæ czcionki
    resultText.setFillColor(sf::Color::White);
    resultText.setPosition(window.getSize().x / 2 - 200, window.getSize().y / 2 - 50); // Ustawienie tekstu na œrodku


    const float spawnInterval = 2.5f;
    const float gameDuration = 125.0f;

    std::vector<std::unique_ptr<Asteroidy>> asteroids;
    licznikpunktow scoreCounter; // U¿ywamy licznikpunktow zamiast ScoreCounter

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distY(0, 690);
    float deltaTime = updateClock.restart().asSeconds();  // Zegary i obliczanie deltaTime

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    if (!potwierdzwyjscie) {
                        potwierdzwyjscie = true;
                        poprzednistan[0] = menuglowne;
                        poprzednistan[1] = ekranstart;
                        poprzednistan[2] = nowagra;
                        poprzednistan[3] = wczytaj;
                        poprzednistan[4] = wyniki;
                        poprzednistan[5] = opcje;

                        menuglowne = ekranstart = nowagra = wczytaj = wyniki = opcje = false;
                    }
                    else {
                        potwierdzwyjscie = false;
                        menuglowne = poprzednistan[0];
                        ekranstart = poprzednistan[1];
                        nowagra = poprzednistan[2];
                        wczytaj = poprzednistan[3];
                        wyniki = poprzednistan[4];
                        opcje = poprzednistan[5];
                    }
                }
                // Obs³uga zmiany wyboru w trybie potwierdzenia wyjœcia
                else if (potwierdzwyjscie) {
                    if (event.key.code == sf::Keyboard::Left) {
                        wyjscie.strzalkalewo();
                    }
                    else if (event.key.code == sf::Keyboard::Right) {
                        wyjscie.strzalkaprawo();
                    }
                    else if (event.key.code == sf::Keyboard::Enter) {
                        int wybor = wyjscie.wybranaopcja();
                        if (wybor == 0) { // U¿ytkownik wybra³ "NIE"
                            potwierdzwyjscie = false;
                            menuglowne = poprzednistan[0];
                            ekranstart = poprzednistan[1];
                            nowagra = poprzednistan[2];
                            wczytaj = poprzednistan[3];
                            wyniki = poprzednistan[4];
                            opcje = poprzednistan[5];
                        }
                        else if (wybor == 1) { // U¿ytkownik wybra³ "TAK"
                            window.close();
                        }
                    }
                }

            }
            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::Enter)
                {
                    int selectedOption = menu.wybranaopcja();

                    if (selectedOption == 1) // Opcja "Wczytaj grê"
                    {
                        std::cout << "Wczytaj gre" << std::endl;
                        menuglowne = false; // Wyjœcie z menu g³ównego
                        wczytaj = true;

                        // Wczytaj stan gry
                        if (GameSave::loadGame(orzel, scoreCounter, elapsedTime, "game_save.txt")) {
                            std::cout << "Gra wczytana! Punkty: " << scoreCounter.getPunkty()
                                << ", Pozycja Or³a: (" << orzel.getPosition().x << ", " << orzel.getPosition().y << ")"
                                << ", Czas: " << elapsedTime << "s" << std::endl;
                            nowagra = true; // Rozpocznij grê po wczytaniu
                        }
                        else {
                            std::cout << "Nie udalo sie wczytac stanu gry!" << std::endl;
                        }
                    }
                }
            }




            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F1) {
                pauza = !pauza; // Toggle pauzy
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F5 && pauza) {
                // Zapisz stan gry do pliku
                std::ofstream saveFile("game_save.txt");
                if (saveFile.is_open()) {
                    saveFile << scoreCounter.getPunkty() << "\n"; // Zapisz punkty
                    saveFile << orzel.getPosition().x << " " << orzel.getPosition().y << "\n"; // Zapisz pozycjê Or³a
                    saveFile.close();
                    std::cout << "Stan gry zapisany!" << std::endl;
                }
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                typing.showFullText();
            }

            
            if (menuglowne)
            {
                if (event.type == sf::Event::KeyReleased)
                {
                    if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S) {
                        menu.strzalkadol();
                    }
                    else if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W) {
                        menu.strzalkagora();
                    }
                    else if (event.key.code == sf::Keyboard::Enter)
                    {
                        int selectedOption = menu.wybranaopcja();

                        if (selectedOption == 0)
                        {
                            std::cout << "Rozpocznij gre" << std::endl;
                            menuglowne = false;
                            ekranstart = true;
                        }
                        else if (selectedOption == 1)
                        {
                            std::cout << "Wczytaj gre" << std::endl;
                            menuglowne = false;
                            wczytaj = true;

                            // Wczytaj stan gry
                            wczytajGre(scoreCounter, orzel);
                            nowagra = true; // Rozpocznij grê po wczytaniu
                        }
                        else if (selectedOption == 2) // Opcja "Lista wyników"
                        {
                            std::cout << "Lista wyników" << std::endl;
                            menuglowne = false;
                            wyniki = true;

                            // Zmienna na wyniki
                            int najlepszyWynik, poprzedniWynik;
                            wczytajWyniki(najlepszyWynik, poprzedniWynik);

                            // Tworzymy string z wynikami
                            std::string wynikiString = "Najlepszy wynik: " + std::to_string(najlepszyWynik) +
                                "\nPoprzedni wynik: " + std::to_string(poprzedniWynik);

                            // Tworzymy tekst wyników do wyœwietlenia na ekranie
                            sf::Text wynikText;
                            wynikText.setFont(font);
                            wynikText.setCharacterSize(24);
                            wynikText.setFillColor(sf::Color::White);
                            wynikText.setPosition(400, 250); // Pozycja na ekranie
                            wynikText.setString(wynikiString); // Przypisujemy wyniki do tekstu

                            // G³ówna pêtla wyœwietlania wyników
                            while (wyniki)
                            {
                                sf::Event event;
                                while (window.pollEvent(event))
                                {
                                    if (event.type == sf::Event::Closed)
                                        window.close();

                                    // Sprawdzamy, czy naciœniêto Enter
                                    if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Enter)
                                    {
                                        // Powrót do menu g³ównego
                                        ekranstart = false;
                                        menuglowne = true;
                                        wyniki = false; // Zatrzymujemy wyœwietlanie wyników
                                        break; // Wyjœcie z pêtli wyœwietlania wyników
                                    }
                                }

                                // Rysowanie wyników na ekranie
                                window.clear();
                                window.draw(wynikText); // Wyœwietlenie wyniku
                                window.display();
                            }
                        }


                        else if (selectedOption == 3)
                        {
                            std::cout << "Opcje" << std::endl;
                            window.close();
                        }
                        else if (selectedOption == 4) // Opcja "Zamknij"
                        {
                            window.close();
                        }

                    }
                }
            }
        }
        
        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::F5 && pauza) {
            // Zapisz stan gry do pliku
            GameSave::saveGame(orzel, scoreCounter, elapsedTime, "game_save.txt");
            std::cout << "Stan gry zapisany!" << std::endl;
        }

        // Mechanika gry, tylko gdy nowagra jest ustawione na true
        if (nowagra && !pauza)
        {
            elapsedTime += clock.restart().asSeconds();
            // Ruch Or³a
            float deltaTime = updateClock.restart().asSeconds();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                orzel.move(0, -400 * deltaTime);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                orzel.move(0, 400 * deltaTime);
            }

            // Generowanie asteroid
            if (spawnClock.getElapsedTime().asSeconds() > spawnInterval && gameClock.getElapsedTime().asSeconds() < gameDuration) {
                float randomY = static_cast<float>(distY(gen));
                float randomVelocity = 150.0f + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / (600.0f - 150.0f)));
                asteroids.emplace_back(std::make_unique<Asteroidy>(1280, randomY, randomVelocity));
                spawnClock.restart();
            }

            // Aktualizacja asteroid
            for (auto it = asteroids.begin(); it != asteroids.end();) {
                (*it)->update(deltaTime);

                // Usuniêcie asteroidy, jeœli opuœci ekran
                if ((*it)->isOffScreen()) {
                    scoreCounter.dodawaniepunktow(10); // Dodaj 10 punktów
                    it = asteroids.erase(it);
                }
                // Kolizja z Or³em
                else if ((*it)->getBounds().intersects(orzel.getBounds())) {
                    scoreCounter.dodawaniepunktow(-10); // Odejmij 10 punktów
                    it = asteroids.erase(it);
                }
                else {
                    ++it;
                }
            }
        }
        
        if (gameClock.getElapsedTime().asSeconds() >= gameDuration) {
            // Wyœwietlenie tekstu z wynikiem
            resultText.setString("TWÓJ WYNIK TO: " + std::to_string(scoreCounter.getPunkty()) +
                "\n\n\n\n\nKONIEC GRY");
            nowagra = false; // Zatrzymanie gry
            window.draw(resultText); // Rysowanie wyniku

            if (!resultDisplayed) {
                closeClock.restart();  // Rozpoczynamy odliczanie
                resultDisplayed = true;  // Ustawiamy flagê, ¿eby nie restartowaæ zegara
                zapiszWynik(scoreCounter.getPunkty());  // Zapisz wynik gry (tylko raz)
            }

            // Sprawdzenie czy minê³o 10 sekund od zakoñczenia gry
            if (closeClock.getElapsedTime().asSeconds() >= 10) {
                window.close();// Przejœcie do menu g³ównego
            }
        }


        // Rozpoczêcie gry po naciœniêciu Enter na ekranie startowym
        if (ekranstart)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
            {
                ekranstart = false;
                nowagra = true;
                clock.restart();
            }
        }
        
        // Rysowanie elementów gry
        window.clear();
        if (potwierdzwyjscie)
        {
            wyjscie.draw(window);
        }
        else if (ekranstart)
        {
            typing.update();
            typing.draw(window);
        }
        else if (nowagra && !pauza)
        {
            elapsedTime += clock.restart().asSeconds();
            float deltaTime = updateClock.restart().asSeconds();

            background.update(deltaTime); // Aktualizacja przesuniêcia t³a
            background.draw(window);      // Rysowanie t³a

            // Rysowanie pozosta³ych elementów gry
            for (auto& asteroid : asteroids) {
                asteroid->draw(window);
            }
            orzel.draw(window);
            scoreCounter.draw(window); // Wyœwietlanie punktów
        }
        else if (pauza)
        {
            // Wyœwietlenie tekstu "Naciœnij F5, aby zapisaæ"
            window.draw(saveText);
        }
        else if (wczytaj)
        {
            orzel.draw(window);
        }
        
        else if (wyniki)
        {
            // Zmienna na wyniki
            int najlepszyWynik, poprzedniWynik;
            wczytajWyniki(najlepszyWynik, poprzedniWynik);

            // Tworzymy string z wynikami
            std::string wynikiString = "Najlepszy wynik: " + std::to_string(najlepszyWynik) +
                "\nPoprzedni wynik: " + std::to_string(poprzedniWynik);

            // Tworzymy tekst wyników do wyœwietlenia na ekranie
            sf::Text wynikText;
            wynikText.setFont(font);
            wynikText.setCharacterSize(24);
            wynikText.setFillColor(sf::Color::White);
            wynikText.setPosition(400, 250); // Pozycja na ekranie
            wynikText.setString(wynikiString); // Przypisujemy wyniki do tekstu

            // Rysowanie wyników na ekranie
            window.clear();
            window.draw(wynikText); // Wyœwietlenie wyniku
            window.display();
        }

        else if (gameClock.getElapsedTime().asSeconds() >= gameDuration) {
            window.draw(resultText); // Rysowanie tekstu z wynikiem
        }

        else
        {
            menu.draw(window);
        }

        window.display();
    }

    return 0;
}

















