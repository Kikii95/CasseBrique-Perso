#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Pad.h"
#include "Brick.h"

#define SCREEN_WIDTH 3840
#define SCREEN_HEIGHT 2160

class Ball {
protected:
    float positionx, positiony;
    float speed;
    int size;
    float directionX;
    float directionY;
    /*float normalizedDistance;*/
    bool isPiercing = false;
    int scoreMultiplier = 1;
    bool reverseBounce = false;
    /*bool reverseControls = false;*/

public:
    Ball(float posx, float posy, float spd, int sz);
    void move(float deltaTime, sf::RectangleShape& pad, std::vector<Brick>& bricks, Pad& Pad);
    void wallBounce(Pad& pad);
    void padBounce(sf::RectangleShape& pad);
    void brickBounce(Brick& brick);
    void display();

    static float originalSpeed;
    static float originalSize;

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

    void normalizeDirection();

    void setPiercing(bool value);
    bool getPiercing() const;

    void setScoreMultiplier(int multiplier);
    int getScoreMultiplier() const;

    void setReverseBounce(bool reverse);
    bool isReverseBounceActive() const;
    /*void setReverseControls(bool reverse);
    bool areControlsReversed() const;*/
};
