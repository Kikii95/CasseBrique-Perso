#include "MainMenu.h"
#include <iostream>

MainMenu::MainMenu(sf::RenderWindow& window) {
    if (!font.loadFromFile("timesnewarial.ttf")) {
        std::cerr << "Erreur : impossible de charger la police." << std::endl;
    }

    sf::Text play("Demarrer le jeu", font, 100);
    play.setFillColor(sf::Color::Red);
    play.setPosition(sf::Vector2f(SCREEN_WIDTH / 2 - 350, SCREEN_HEIGHT / 2 - 150));
    menuItem.push_back(play);

    sf::Text option("Option", font, 100);
    option.setFillColor(sf::Color::White);
    option.setPosition(sf::Vector2f(SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2 + 50));
	menuItem.push_back(option);

	sf::Text levelGen("Level Generator", font, 100);
	levelGen.setFillColor(sf::Color::White);
	levelGen.setPosition(sf::Vector2f(SCREEN_WIDTH / 2 - 300, SCREEN_HEIGHT / 2 + 175));
	menuItem.push_back(levelGen);


    sf::Text quit("Quitter", font, 100);
    quit.setFillColor(sf::Color::White);
    quit.setPosition(sf::Vector2f(SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2 + 250));
    menuItem.push_back(quit);

    selectedItemIndex = 0;
}



void MainMenu::draw(sf::RenderWindow& window) {
    for ( auto& item : menuItem) {
        window.draw(item);
    }
}

void MainMenu::moveUp() {
    if (selectedItemIndex - 1 >= 0) {
        menuItem[selectedItemIndex].setFillColor(sf::Color::White); 
        selectedItemIndex--;
        menuItem[selectedItemIndex].setFillColor(sf::Color::Red); 
    }
}

void MainMenu::moveDown() {
    if (selectedItemIndex + 1 < menuItem.size()) {
        menuItem[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        menuItem[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}


int MainMenu::getSelectedItemIndex()
{
	return selectedItemIndex;
}

void MainMenu::selectItemByMouse( sf::Vector2f& mousepos)
{

}

MainMenu::~MainMenu()
{
}
