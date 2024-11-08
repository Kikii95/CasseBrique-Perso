#include <vector>
#include <SFML/Graphics.hpp>
#include "Brick.h"
#include <iostream> 
sf::Texture Brick::brickTexture; 

Brick::Brick(int x, int y, int sx, int sy)
    : positionx(x), positiony(y), sizex(sx), sizey(sy), isDestroyed(false) {

     shape.setSize(sf::Vector2f(sizex, sizey));
     shape.setPosition(positionx, positiony);
     shape.setTexture(&brickTexture); }

void Brick::loadTexture(const std::string& textureFile) {
    if (!brickTexture.loadFromFile(textureFile)) {
        std::cerr << "Erreur : Impossible de charger la texture de la brique depuis " << textureFile << std::endl;
    }
}

void Brick::destroy() { isDestroyed = true; }
bool Brick::isBroken() { return isDestroyed; }

int Brick::getPositionX() { return positionx; }
int Brick::getPositionY() { return positiony; }
int Brick::getSizeX() { return sizex; }
int Brick::getSizeY() { return sizey; }


std::vector<Brick> Brick::createBricks(int rows, int columns, int brickWidth, int brickHeight) {
    std::vector<Brick> bricks;
    std::pair<int, int> spaceBetween = { brickWidth / 2, brickHeight };
    int totalWidth = columns * brickWidth + (columns - 1) * spaceBetween.first;
    int startX = (SCREEN_WIDTH - totalWidth) / 2;
    int topOffset = 150;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            int xPos = startX + j * (brickWidth + spaceBetween.first);
            int yPos = topOffset + i * (brickHeight + spaceBetween.second);
            bricks.emplace_back(xPos, yPos, brickWidth, brickHeight);
        }
    }
    return bricks;
}


sf::RectangleShape Brick::getShape()  {
    if (isDestroyed) {
        return sf::RectangleShape();
    }
    return shape;
}

bool Brick::checkCollision(sf::CircleShape& ballShape) {
    if (isDestroyed) return false;

    sf::RectangleShape brickShape(sf::Vector2f(sizex, sizey));
    brickShape.setPosition(positionx, positiony);

    return ballShape.getGlobalBounds().intersects(brickShape.getGlobalBounds());
}
