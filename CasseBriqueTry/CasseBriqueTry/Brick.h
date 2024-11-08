#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#define SCREEN_WIDTH 3840
#define SCREEN_HEIGHT 2160

class Brick {
private:
    bool isDestroyed = false;
    static sf::Texture brickTexture;
    sf::RectangleShape shape;
    int positionx;
    int positiony;
    int sizex;
    int sizey;

public:
    Brick(int x, int y, int sx, int sy);

    void destroy();
    bool isBroken() ;

    static void loadTexture(const std::string& textureFile); 
    static std::vector<Brick> createBricks(int rows, int columns, int brickWidth, int brickHeight);

    sf::RectangleShape getShape() ;
    sf::FloatRect getBounds() const;

    int getPositionX();
    int getPositionY();
    int getSizeX();
    int getSizeY();

    bool checkCollision(sf::CircleShape& ballShape);
};
