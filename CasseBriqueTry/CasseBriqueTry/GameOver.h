#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "MainMenu.h"

class GameOver : public MainMenu {
public:
    GameOver(sf::RenderWindow& window);
    void display();
    bool handleEvent(sf::Event& event);

    void moveUp();
    void moveDown();
    void select();
    int getSelectedItemIndex() const;


private:
    sf::RenderWindow& window;
    sf::Font font;
    sf::Text gameOverText;
    sf::Text bricksRemainingText;
    sf::Text bonusText;
    sf::Text scoreText;
    sf::RectangleShape overlay;
    sf::Text replayButton;    // Nouveau bouton
    sf::Text optionsButton;   // Nouveau bouton
    sf::Text quitButton;
    std::vector<sf::Text> menuItems; // Nouveau vecteur pour stocker les éléments de menu
    int selectedItemIndex = 0;
    
};
