#pragma once
#include <iostream>
#include <SFML/Graphics.hpp> // Inclure SFML pour utiliser RectangleShape
#include "Ball.h"
#include "Brick.h"

#define SCREEN_WIDTH 2560
#define SCREEN_HEIGHT 1440

class Pad {
public:
    Pad(float speed, int size);

    void moveLeft(float deltaTime);
    void moveRight(float deltaTime);

    void setSpeed(float newSpeed);
    float getSpeed() ;

    std::pair<float, float> getPosition() ;
    virtual void setPosition(float positionX, float positionY);
    std::pair<int, int> getSize() ;
    virtual void setSize(int size);

    void displayPosition();

protected:
    float positionX, positionY;
    float speed;     int sizeX, sizeY;
};
