#include "PauseMenu.h"
#include <iostream>

PauseMenu::PauseMenu(sf::RenderWindow& window) {
    if (!font.loadFromFile("timesnewarial.ttf")) {
        std::cerr << "Erreur : impossible de charger la police." << std::endl;
    }

    sf::Text play("Play", font, 100);
    play.setFillColor(sf::Color::White);
    sf::FloatRect playBounds = play.getLocalBounds();
    play.setOrigin(playBounds.width / 2, playBounds.height / 2);
    play.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 300);
    menuItem.push_back(play);

    sf::Text restart("Restart", font, 100);
    restart.setFillColor(sf::Color::White);
    sf::FloatRect restartBounds = restart.getLocalBounds();
    restart.setOrigin(restartBounds.width / 2, restartBounds.height / 2);
    restart.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 100);
    menuItem.push_back(restart);

    sf::Text options("Option", font, 100);
    options.setFillColor(sf::Color::White);
    sf::FloatRect optionsBounds = options.getLocalBounds();
    options.setOrigin(optionsBounds.width / 2, optionsBounds.height / 2);
    options.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 100);
    menuItem.push_back(options);

    sf::Text quit("Quit", font, 100);
    quit.setFillColor(sf::Color::White);
    sf::FloatRect quitBounds = quit.getLocalBounds();
    quit.setOrigin(quitBounds.width / 2, quitBounds.height / 2);
    quit.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 300);
    menuItem.push_back(quit);

    selectedItemIndex = 0;
}


void PauseMenu::draw(sf::RenderWindow& window)
{
	for ( auto& item : menuItem) {

		window.draw(item);
	}
}

void PauseMenu::moveUp()
{
	if (selectedItemIndex - 1 >= 0) {
		menuItem[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		menuItem[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void PauseMenu::moveDown()
{
	if (selectedItemIndex + 1 < menuItem.size()) {
		menuItem[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		menuItem[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

int PauseMenu::getSelectedItemIndex()
{
	return selectedItemIndex;
}

void PauseMenu::selectItemByMouse( sf::Vector2f & mousepos)
	{
		for (size_t i = 0; i < menuItem.size(); ++i) {
			if (menuItem[i].getGlobalBounds().contains(mousepos)) {
				menuItem[selectedItemIndex].setFillColor(sf::Color::White);
				selectedItemIndex = i;
				menuItem[selectedItemIndex].setFillColor(sf::Color::Red);
				break;
			}
		}
}


PauseMenu::~PauseMenu()
{
}
