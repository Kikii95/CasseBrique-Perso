#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "MainMenu.h"
#include "PauseMenu.h"

class HUD {
public:
    HUD(int width, int height, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window, bool isMainMenuActive);
    void updateScore(int score);
    void showPauseMenu(bool show);
    void handleMouseClick( sf::Vector2f& mousepos);
    void handleKeyboardInput(sf::Keyboard::Key key);
    int getSelectedMenuIndex();

    MainMenu& getMainMenu() { return mainMenu; } 
    PauseMenu& getPauseMenu() { return pauseMenu; } 

    ~HUD();

private:
    MainMenu mainMenu;
    PauseMenu pauseMenu;
    sf::Text scoreText;
    sf::Font font;
    int score;
    bool isPaused;
};
