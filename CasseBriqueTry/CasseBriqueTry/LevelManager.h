#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Pad.h"
#include "Ball.h"
#include "Brick.h"

enum class LevelType {
    Level1,
    Level2
};

class LevelManager {
public:
    LevelManager();
    ~LevelManager();

    int selectedOption = 0;
    bool selectLevel(sf::RenderWindow& window, int selectedOption);
    int getSelectedOption();
    void setSelectedOption(int option);
    void initializeLevel(LevelType levelType, Pad& pad, Ball& ball, std::vector<Brick>& bricks);
    void renderLevel(sf::RenderWindow& window, Pad& pad, Ball& ball, std::vector<Brick>& bricks);

    LevelType getCurrentLevel()  { return currentLevel; } 
private:
    LevelType currentLevel;
};
