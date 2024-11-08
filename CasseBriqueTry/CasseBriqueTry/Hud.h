#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "MainMenu.h"
#include "PauseMenu.h"
#include "EndMenu.h"
#include "OptionsMenu.h"

class HUD {
public:
    HUD(int width, int height, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window, bool isMainMenuActive, bool isPaused, bool isGameOver, bool isOptionsMenuActive);
    
    void handleMouseClick( sf::Vector2f& mousepos);
    void handleKeyboardInput(sf::Keyboard::Key key);
    int getSelectedMenuIndex();
    MainMenu& getMainMenu() { return mainMenu; } 
    PauseMenu& getPauseMenu() { return pauseMenu; }
    EndMenu& getEndMenu() { return endMenu; }
    OptionsMenu& getOpMenu() { return opMenu;  }
    

    ~HUD();

private:
    
    MainMenu mainMenu;
    PauseMenu pauseMenu;
    EndMenu endMenu;
    OptionsMenu opMenu;
    sf::Text scoreText;
    sf::Font font;
    int score;
    bool isPaused;
    bool isMainMenuActive;
    bool isGameOver;
    bool isOptionsMenuActive;
};
