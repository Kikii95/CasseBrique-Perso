#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "Brick.h"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

class Pad {
public:
    Pad(float speed, int size);

    void moveLeft(float deltaTime);
    void moveRight(float deltaTime);

    void setSpeed(float newSpeed);
    float getSpeed() const;

    std::pair<float, float> getPosition() const;
    virtual void setPosition(float positionX, float positionY);
    std::pair<int, int> getSize() const;
    virtual void setSize(int size);

    sf::RectangleShape getShape() const;  // Modifie pour retourner un Pad avec texture
    bool loadTexture(const std::string& filePath); // Ajoute une méthode pour charger la texture

    void displayPosition();

protected:
    float positionX, positionY;
    float speed;
    int sizeX, sizeY;
    sf::Texture padTexture;  // Ajoute un membre pour la texture du pad
};
