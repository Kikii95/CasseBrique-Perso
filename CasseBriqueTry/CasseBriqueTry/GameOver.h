#pragma once
#include <SFML/Graphics.hpp>
#include "MainMenu.h"

class GameOver : public MainMenu {
public:
    GameOver(sf::RenderWindow& window);
    void display();
    bool handleEvent(sf::Event& event);

private:
    sf::RenderWindow& window;
    sf::Font font;
    sf::Text gameOverText;
    sf::Text bricksRemainingText;
    sf::Text bonusText;
    sf::Text scoreText;
    sf::RectangleShape overlay;
};
