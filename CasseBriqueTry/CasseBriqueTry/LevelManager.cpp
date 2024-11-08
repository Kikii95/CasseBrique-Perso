#include "LevelManager.h"

LevelManager::LevelManager() : selectedOption(0) {}

LevelManager::~LevelManager() {}

int LevelManager::getSelectedOption() {
    return selectedOption;
}

void LevelManager::setSelectedOption(int option) {
    selectedOption = option;
}

bool LevelManager::selectLevel(sf::RenderWindow& window, int option) {
    selectedOption = option;
    sf::Font font;
    if (!font.loadFromFile("timesnewarial.ttf")) {
        std::cerr << "Erreur : Impossible de charger la police " << std::endl;
        return false;
    }

    sf::Text level1Text("Niveau 1", font, 50);
    level1Text.setPosition(800, 400);

    sf::Text level2Text("Niveau 2", font, 50);
    level2Text.setPosition(800, 500);

    int selectedOption = 0;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up) {
                    selectedOption = 0;
                }
                if (event.key.code == sf::Keyboard::Down) {
                    selectedOption = 1;
                }
                if (event.key.code == sf::Keyboard::Enter) {
                    currentLevel = (selectedOption == 0) ? LevelType::Level1 : LevelType::Level2;
                    return true;
                }
            }
        }

        if (selectedOption == 0) {
            level1Text.setFillColor(sf::Color::Red);
            level2Text.setFillColor(sf::Color::White);
        }
        else {
            level1Text.setFillColor(sf::Color::White);
            level2Text.setFillColor(sf::Color::Red);
        }

        window.clear();
        window.draw(level1Text);
        window.draw(level2Text);
        window.display();
    }

    return false;
}

void LevelManager::initializeLevel(LevelType levelType, Pad& pad, Ball& ball, std::vector<Brick>& bricks) {
    pad = Pad((0.8 * SCREEN_WIDTH), (0.2 * SCREEN_HEIGHT));
    ball = Ball(pad.getPosition().first + pad.getSize().first / 2, pad.getPosition().second - ball.getSize() / 2, (0.3 * SCREEN_HEIGHT), (0.01 * SCREEN_WIDTH));

    if (levelType == LevelType::Level1) {
        bricks.clear();
        bricks = Brick::createBricks(5, 10, 115, 40);
    }
    else if (levelType == LevelType::Level2) {
        bricks.clear();
        bricks.emplace_back(800, 300, 115, 40);
        bricks.emplace_back(1000, 300, 115, 40);
    }
}

void LevelManager::renderLevel(sf::RenderWindow& window, Pad& pad, Ball& ball, std::vector<Brick>& bricks) {
    for (Brick& brick : bricks) {
        if (!brick.isBroken()) window.draw(brick.getShape());
    }
}
