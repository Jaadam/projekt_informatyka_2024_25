#include <SFML/Graphics.hpp>
#include <iostream>
#include "Menu.h"


int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Kulka strzela w kwadraciki");
   
    Menu menu(window.getSize().x, window.getSize().y);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {    
           
            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::Down)
                {
                    menu.strzalkadol();
                }
                if (event.key.code == sf::Keyboard::Up)
                {
                    menu.strzalkagora();
                }
                if (event.key.code == sf::Keyboard::S)
                {
                    menu.strzalkadol();
                }
                if (event.key.code == sf::Keyboard::W)
                {
                    menu.strzalkagora();
                }
                if (event.key.code == sf::Keyboard::Enter)
                {
                    switch (menu.wybranaopcja())
                    {
                    case 0:
                        std::cout << "Rozpocznij gre" << std::endl;
                        break;
                    case 1:
                        std::cout << "Wczytaj gre" << std::endl;
                        break;
                    case 2:
                        std::cout << "Lista wynikow" << std::endl;
                        break;
                    case 3:
                        std::cout << "Opcje" << std::endl;
                        break;
                    case 4:
                        window.close();
                        
                    }
                    
                }
            }

            
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        
        menu.draw(window);
        window.display();
    }

    return 0;
}