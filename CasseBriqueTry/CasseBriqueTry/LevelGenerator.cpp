#include "LevelGenerator.h"
#include "FileUtils.h"  // Pour fileExists
#include <fstream>
#include <iostream>


LevelGenerator::LevelGenerator() {
    levelNumber = getNextLevelNumber();
}

int LevelGenerator::getNextLevelNumber()  {
    int level = 1;
    while (fileExists("level_" + std::to_string(level) + ".lvl")) {
        ++level;
    }
    return level;
}

void LevelGenerator::saveLevel() {
    std::string fileName = "level_" + std::to_string(levelNumber) + ".lvl";
    std::ofstream levelFile(fileName);

    if (levelFile.is_open()) {
        for ( auto& brick : bricks) {
            levelFile << brick.getPositionX() << " "
                << brick.getPositionY() << " "
                << brick.getSizeX() << " "
                << brick.getSizeY() << "\n";
        }
        levelFile.close();
        std::cout << "Niveau " << levelNumber << " enregistré sous " << fileName << std::endl;
    }
    else {
        std::cerr << "Erreur : impossible de créer le fichier " << fileName << std::endl;
    }
}
