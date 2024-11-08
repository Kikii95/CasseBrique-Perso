#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "Brick.h"
#include "json.hpp" // Pour la gestion JSON

using json = nlohmann::json;

class LevelGenerator {
public:
    LevelGenerator();
    void saveLevel(); // Sauvegarde la disposition en JSON
    void handleMouseClick(const sf::Vector2i& mousePos); // Place une brique sur le quadrillage
    void drawGrid(sf::RenderWindow& window); // Affiche le quadrillage

private:
    std::vector<Brick> bricks;
    const int brickWidth = 120;
    const int brickHeight = 40;

    std::pair<int, int> getGridPosition(const sf::Vector2i& mousePos); // Calcule la position dans la grille
};
