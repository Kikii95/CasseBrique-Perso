#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Pad.h"
#include "Brick.h"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

class Ball {
protected:
    float positionx, positiony;
    float speed;
    int size;
    float directionX;
    float directionY;
    float normalizedDistance;

public:
    Ball(float posx, float posy, float spd, int sz);
    void move(float deltaTime, sf::RectangleShape& pad, std::vector<Brick>& bricks);
    void wallBounce();
    void padBounce(sf::RectangleShape& pad);
    void display();

    sf::CircleShape ballShape;
    sf::CircleShape& getShape();

    void setDirection(float dirX, float dirY);
    std::pair<int, int> getDirection();
    void setSpeed(int spd);
    int getSpeed();
    void setSize(int siz);
    int getSize();
    void setPosition(float posx, float posy);
    std::pair<float, float> getPosition();
};
