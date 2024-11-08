#include "Pad.h"
#include <algorithm>

Pad::Pad(float spd, int size)
    : positionX(SCREEN_WIDTH / 2 - size / 2), positionY(SCREEN_HEIGHT - (SCREEN_HEIGHT / 10)), speed(spd), sizeX(size), sizeY(size / 6) {}

bool Pad::loadTexture(const std::string& filePath) {
    if (!padTexture.loadFromFile(filePath)) {
        std::cerr << "Erreur : Impossible de charger la texture du pad depuis " << filePath << std::endl;
        return false;
    }
    else {
        std::cout << "Texture du pad chargée avec succès depuis " << filePath << std::endl;
    }
    return true;
}


void Pad::moveLeft(float deltaTime) {
    positionX -= speed * deltaTime;
    if (positionX < 0) positionX = 0;
}

void Pad::moveRight(float deltaTime) {
    positionX += speed * deltaTime;
    if (positionX + sizeX > SCREEN_WIDTH) positionX = SCREEN_WIDTH - sizeX;
}

void Pad::setSpeed(float newSpeed) {
    speed = newSpeed;
}

float Pad::getSpeed() const {
    return speed;
}

std::pair<float, float> Pad::getPosition() const {
    return { positionX, positionY };
}

void Pad::setPosition(float posX, float posY) {
    positionX = posX;
    positionY = posY / 3;
}

std::pair<int, int> Pad::getSize() const {
    return { sizeX, sizeY };
}

void Pad::setSize(int size) {
    sizeX = size;
    sizeY = size / 3;
}

sf::RectangleShape Pad::getShape() const {
    sf::RectangleShape shape(sf::Vector2f(sizeX, sizeY));
    shape.setPosition(positionX, positionY);
    shape.setTexture(&padTexture); // Applique la texture au pad
    return shape;
}

void Pad::displayPosition() {
    std::cout << "Pad a la position : " << positionX << ", " << positionY << std::endl;
}
