#pragma once
#include "HUD.h"

HUD::HUD(int width, int height, sf::RenderWindow& window)
    : mainMenu(window), pauseMenu(window),endMenu(window),opMenu(window), score(50)
{
    
    if (!font.loadFromFile("timesnewarial.ttf")) {
        std::cerr << "Erreur : impossible de charger la police." << std::endl;
        
    }
    else {
        std::cout << "Police chargée avec succès." << std::endl;
    }
    
    scoreText.setFont(font);
    scoreText.setCharacterSize(50);
    scoreText.setFillColor(sf::Color::Red);
    scoreText.setPosition(10, 10);

    
}

void HUD::draw(sf::RenderWindow& window, bool isMainMenuActive, bool isPaused, bool isGameOver,bool isOptionsMenuActive) {
    window.clear();
    scoreText.setString("Score : 50");
    window.draw(scoreText);

    if (isMainMenuActive) {
        mainMenu.draw(window);
    }
    else if (isPaused) {
        pauseMenu.display(window);
    }
    else if (isGameOver) {
        endMenu.display();
    }
    else if (isOptionsMenuActive) {
        opMenu.display(window);
    }
}




void HUD::handleMouseClick( sf::Vector2f& mousepos)
{
   /* if (isPaused) {
        pauseMenu.selectItemByMouse(mousepos);
    } else {
        mainMenu.selectItemByMouse(mousepos);
    }*/
}

void HUD::handleKeyboardInput(sf::Keyboard::Key key)
{
    
    if (isPaused) {
        // Si le jeu est en pause, gérer les entrées du clavier pour le menu de pause
        if (key == sf::Keyboard::Up) {
            pauseMenu.moveUp();
        }
        else if (key == sf::Keyboard::Down) {
            pauseMenu.moveDown();
        }
    }
    else if (isGameOver) {
        // Si le jeu est terminé, gérer les entrées du clavier pour le menu de fin de jeu
        if (key == sf::Keyboard::Up) {
            endMenu.moveUp();
        }
        else if (key == sf::Keyboard::Down) {
            endMenu.moveDown();
        }
    }
    else if (isOptionsMenuActive) {
        // Si le jeu est terminé, gérer les entrées du clavier pour le menu de fin de jeu
        if (key == sf::Keyboard::Up) {
            opMenu.moveUp();
        }
        else if (key == sf::Keyboard::Down) {
            opMenu.moveDown();
        }
    }
    else  {
        // Si le jeu n'est pas en pause et que le jeu n'est pas terminé, gérer les entrées du clavier pour le menu principal
        if (key == sf::Keyboard::Up) {
            mainMenu.moveUp();
        }
        else if (key == sf::Keyboard::Down) {
            mainMenu.moveDown();
        }
    }
}

int HUD::getSelectedMenuIndex()
{
    if (isPaused) {
        return pauseMenu.getSelectedItemIndex();
    }
    else if (isGameOver) {
  
        return endMenu.getSelectedItemIndex(); // Implémentation nécessaire dans EndMenu
    }
    else if (isOptionsMenuActive) {
        return opMenu.getSelectedItemIndex();
    }
    else {
        return mainMenu.getSelectedItemIndex();
    }
}



HUD::~HUD() {}
