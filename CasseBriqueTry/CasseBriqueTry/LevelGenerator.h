#pragma once
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "Brick.h"

class LevelGenerator {
public:
    LevelGenerator();

        void addBrick(int x, int y, int width, int height);

        void saveLevel();

        int getNextLevelNumber() ;

private:
    std::vector<Brick> bricks;
    int levelNumber;

        std::string generateLevelFileName(int levelNum) ;
};
