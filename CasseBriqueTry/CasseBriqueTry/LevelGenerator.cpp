#include "LevelGenerator.h"
#include <fstream>
#include <iostream>

LevelGenerator::LevelGenerator() {}

void LevelGenerator::saveLevel() {
    std::string fileName = "level_generated.json";
    json levelJson;

    for (const auto& brick : bricks) {
        levelJson["bricks"].push_back({
            {"positionX", brick.getPositionX()},
            {"positionY", brick.getPositionY()},
            {"sizeX", brick.getSizeX()},
            {"sizeY", brick.getSizeY()}
            });
    }

    std::ofstream levelFile(fileName);
    if (levelFile.is_open()) {
        levelFile << levelJson.dump(4); // Sauvegarde avec une indentation
        levelFile.close();
        std::cout << "Niveau sauvegard� sous " << fileName << std::endl;
    }
    else {
        std::cerr << "Erreur : impossible de cr�er le fichier " << fileName << std::endl;
    }
}

void LevelGenerator::handleMouseClick(const sf::Vector2i& mousePos) {
    // Calcule la position de la brique dans la grille
    auto gridPosition = getGridPosition(mousePos);
    int posX = gridPosition.first;
    int posY = gridPosition.second;

    // Ajoute une brique � cette position
    Brick newBrick(posX, posY, brickWidth, brickHeight);
    bricks.push_back(newBrick);

    std::cout << "Brique ajout�e � la position (" << posX << ", " << posY << ")" << std::endl;
}

void LevelGenerator::drawGrid(sf::RenderWindow& window) {
    // Dessine le quadrillage
    sf::RectangleShape line(sf::Vector2f(window.getSize().x, 1));
    line.setFillColor(sf::Color::White);

    for (int y = 0; y < window.getSize().y; y += brickHeight) {
        line.setPosition(0, y);
        window.draw(line);
    }

    line.setSize(sf::Vector2f(1, window.getSize().y));
    for (int x = 0; x < window.getSize().x; x += brickWidth) {
        line.setPosition(x, 0);
        window.draw(line);
    }

    // Dessine toutes les briques plac�es
    for (const auto& brick : bricks) {
        window.draw(brick.getShape());
    }
}

std::pair<int, int> LevelGenerator::getGridPosition(const sf::Vector2i& mousePos) {
    int posX = (mousePos.x / brickWidth) * brickWidth;
    int posY = (mousePos.y / brickHeight) * brickHeight;
    return { posX, posY };
}
