#include "HUD.h"

HUD::HUD(int width, int height, sf::RenderWindow& window)
    : mainMenu(window), pauseMenu(window), score(0), isPaused()
{
    
    if (!font.loadFromFile("timesnewarial.ttf")) {
        std::cerr << "Erreur : impossible de charger la police." << std::endl;
    }
    scoreText.setCharacterSize(50);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(20, 20); 
}

void HUD::draw(sf::RenderWindow& window, bool isMainMenuActive) {
    window.draw(scoreText);

    if (isMainMenuActive) {
        mainMenu.draw(window);
    }
    else if (isPaused) {
        pauseMenu.draw(window);
    }
}

void HUD::updateScore(int newScore)
{
    score = newScore;
    scoreText.setString("Score: " + std::to_string(score));
}

void HUD::showPauseMenu(bool show)
{
    isPaused = show;
}

void HUD::handleMouseClick( sf::Vector2f& mousepos)
{
    if (isPaused) {
        pauseMenu.selectItemByMouse(mousepos);
    } else {
        mainMenu.selectItemByMouse(mousepos);
    }
}

void HUD::handleKeyboardInput(sf::Keyboard::Key key)
{
    if (isPaused) {
        if (key == sf::Keyboard::Up) {
            pauseMenu.moveUp();
        } else if (key == sf::Keyboard::Down) {
            pauseMenu.moveDown();
        }
    } else {
        if (key == sf::Keyboard::Up) {
            mainMenu.moveUp();
        } else if (key == sf::Keyboard::Down) {
            mainMenu.moveDown();
        }
    }
}

int HUD::getSelectedMenuIndex()
{
    return isPaused ? pauseMenu.getSelectedItemIndex() : mainMenu.getSelectedItemIndex();
}

HUD::~HUD() {}
