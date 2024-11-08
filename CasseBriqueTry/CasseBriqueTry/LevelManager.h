#pragma once
#include <vector>
#include <string>
#include "Brick.h"
#include "Pad.h"
#include "Ball.h"
#include <SFML/Graphics.hpp>
#include "json.hpp" // Inclure la biblioth�que JSON
using json = nlohmann::json;

enum LevelType {
    LEVEL_1,
    LEVEL_2,
    LEVEL_3
};

class LevelManager {
public:
    LevelManager();
    bool selectLevel(sf::RenderWindow& window, LevelType level);  // S�lectionne le niveau
    void initializeLevel(LevelType level, Pad& pad, Ball& ball, std::vector<Brick>& bricks);
    void renderLevel(sf::RenderWindow& window, Pad& pad, Ball& ball, const std::vector<Brick>& bricks);
    LevelType getCurrentLevel() const;

private:
    LevelType currentLevel;
    bool loadLevelFromFile(const std::string& filename, std::vector<Brick>& bricks);
};
