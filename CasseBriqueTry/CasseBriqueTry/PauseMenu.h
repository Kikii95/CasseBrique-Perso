#pragma once
#include <SFML/Graphics.hpp>

#define SCREEN_WIDTH 3840
#define SCREEN_HEIGHT 2160

class PauseMenu
{
public:


	PauseMenu(sf::RenderWindow& window);

	void draw(sf::RenderWindow& window);
	void moveUp();
	void moveDown();
	int getSelectedItemIndex();
	void selectItemByMouse( sf::Vector2f& mousepos);

	~PauseMenu();

private:

	int selectedItemIndex;
	sf::Font font;
	std::vector<sf::Text>menuItem;

};
