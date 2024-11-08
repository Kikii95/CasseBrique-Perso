#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio.hpp>


#define SCREEN_WIDTH 2560
#define SCREEN_HEIGHT 1440

class PauseMenu
{
public:


	PauseMenu(sf::RenderWindow& window);
	void display(sf::RenderWindow& window);
	void moveUp();
	void moveDown();
	void selectItemByMouse(sf::Vector2f& mousepos);
	bool handleEvent(sf::Event& event);
	int getSelectedItemIndex() const { return selectedItemIndex; }
	void playClickSound();
	sf::Sound& getClickSound();

	

private:

	sf::RenderWindow& window;
	sf::Font font;
	sf::Text PauseText;
	sf::RectangleShape overlay;
	std::vector<sf::Text> menuItem;
	int selectedItemIndex;
	sf::SoundBuffer clickSoundBuffer;
	sf::Sound clickSound;
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;

};
