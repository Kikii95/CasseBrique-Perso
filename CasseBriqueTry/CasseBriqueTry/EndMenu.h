#pragma once
#include "MainMenu.h"
#include <SFML/Graphics.hpp>



class EndMenu : public  MainMenu {
public:

	EndMenu(sf::RenderWindow& window);
	void display();
	bool handleEvent(sf::Event& event);
    void moveUp();    
    void moveDown();
    void selectItemByMouse(sf::Vector2f& mousepos);
    int getSelectedItemIndex() const;
    void playClickSound();
    
	

private:
    sf::RenderWindow& window;
    sf::Font font;
    sf::Text gameOverText;
    sf::Text bricksRemainingText;
    sf::Text bonusText;
    sf::Text scoreText;
    sf::Text menuOptions[3];
    sf::RectangleShape overlay;
    std::vector<sf::Text> menuItems;         
    int selectedIndex;
    sf::SoundBuffer clickSoundBuffer;
    sf::Sound clickSound;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
  

};

