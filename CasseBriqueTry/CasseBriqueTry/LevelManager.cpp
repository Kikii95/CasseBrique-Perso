#include "LevelManager.h"
#include "Pad.h"
#include "Brick.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "json.hpp"
using json = nlohmann::json;


LevelManager::LevelManager() : currentLevel(LevelType::LEVEL_1) {}

bool LevelManager::selectLevel(sf::RenderWindow& window, LevelType level) {
    currentLevel = level;
    return true;
}

LevelType LevelManager::getCurrentLevel() const {
    return currentLevel;
}

void LevelManager::initializeLevel(LevelType level, Pad& pad, Ball& ball, std::vector<Brick>& bricks) {
    bricks.clear();

    if (level == LevelType::LEVEL_3) {
        if (!loadLevelFromFile("level_3.lvl", bricks)) {
            std::cerr << "Erreur : impossible de charger le niveau 3 depuis le fichier level_3.lvl" << std::endl;
        }
    }
    else if (level == LevelType::LEVEL_1) {
        // Initialisez les briques pour le niveau 1 ici si nécessaire
    }

    pad.setPosition(0.8f * SCREEN_WIDTH, 0.9f * SCREEN_HEIGHT);
    ball.setPosition(pad.getPosition().first + pad.getSize().first / 2, pad.getPosition().second - ball.getSize());
    ball.setSpeed(400);
}

bool LevelManager::loadLevelFromFile(const std::string& filename, std::vector<Brick>& bricks) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Erreur : impossible d'ouvrir le fichier " << filename << std::endl;
        return false;
    }

    int posX, posY, sizeX, sizeY;
    while (file >> posX >> posY >> sizeX >> sizeY) {
        bricks.emplace_back(posX, posY, sizeX, sizeY);
    }

    file.close();
    std::cout << "Niveau chargé depuis " << filename << std::endl;
    return true;
}


void LevelManager::renderLevel(sf::RenderWindow& window, Pad& pad, Ball& ball, const std::vector<Brick>& bricks) {
    // Dessiner le pad et la balle
    window.draw(pad.getShape());  // Cette ligne utilise maintenant getShape() correctement
    window.draw(ball.getShape());

    // Dessiner les briques
    for (const auto& brick : bricks) {
        if (!brick.isBroken()) {  // isBroken() peut maintenant être appelée sur const Brick
            window.draw(brick.getShape());
        }
    }
}
