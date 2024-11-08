#include "Ball.h"
#include <cstdlib>
#include <ctime>


Ball::Ball(float posx, float posy, float spd, int sz)
    : positionx(posx), positiony(posy), speed(spd), size(sz), directionX(1.0f), directionY(-1.0f) {
    ballShape.setRadius(size / 2);
    ballShape.setOrigin(size / 2, size / 2);
    ballShape.setPosition(positionx, positiony);
}

void Ball::display() {
    std::cout << "Ball a la position : " << positionx << ", " << positiony << std::endl;
}

void Ball::setSpeed(int spd) {
    speed = spd;
}

int Ball::getSpeed() {
    return speed;
}

void Ball::setSize(int siz) {
    size = siz;
}

int Ball::getSize() {
    return size;
}

sf::CircleShape& Ball::getShape() {
    return ballShape;
}

void Ball::setDirection(float dirX, float dirY) {
    float length = std::sqrt(dirX * dirX + dirY * dirY);
    if (length != 0) {
        directionX = dirX / length;
        directionY = dirY / length;
    }
}

std::pair<int, int> Ball::getDirection() {
    return { directionX, directionY };
}

void Ball::padBounce(sf::RectangleShape& pad) {
    if (ballShape.getGlobalBounds().intersects(pad.getGlobalBounds())) {
        float padCenterX = pad.getPosition().x + pad.getSize().x / 2.0f;
        float ballCenterX = positionx;

        float distanceFromCenter = ballCenterX - padCenterX;
        normalizedDistance = distanceFromCenter / (pad.getSize().x / 2.0f);

        directionY = -std::abs(directionY);
        directionX += normalizedDistance * 0.5f;
    }
}



void Ball::move(float deltaTime, sf::RectangleShape& pad, std::vector<Brick>& bricks) {
    positionx += (directionX * speed * deltaTime);
    positiony += directionY * speed * deltaTime;

    ballShape.setPosition(positionx, positiony);
    wallBounce();
    padBounce(pad);

    for (Brick& brick : bricks) {
        if (brick.checkCollision(ballShape)) {
            sf::FloatRect brickBounds(brick.getPositionX(), brick.getPositionY(), brick.getSizeX(), brick.getSizeY());
            sf::FloatRect ballBounds = ballShape.getGlobalBounds();

            float overlapLeft = ballBounds.left + ballBounds.width - brickBounds.left;
            float overlapRight = brickBounds.left + brickBounds.width - ballBounds.left;
            float overlapTop = ballBounds.top + ballBounds.height - brickBounds.top;
            float overlapBottom = brickBounds.top + brickBounds.height - ballBounds.top;

            float minOverlap = std::min({ overlapLeft, overlapRight, overlapTop, overlapBottom });

            if (minOverlap == overlapLeft) {
                directionX = -1;
            }
            else if (minOverlap == overlapRight) {
                directionX = 1;
            }
            else if (minOverlap == overlapTop) {
                directionY = -1;
            }
            else if (minOverlap == overlapBottom) {
                directionY = 1;
            }

            brick.destroy();
            break;
        }
    }

    ballShape.setPosition(positionx, positiony);
}






void Ball::wallBounce() {
    if (positionx - size / 2 <= 0) {
        directionX = std::abs(directionX);
    }
    else if (positionx + size / 2 >= SCREEN_WIDTH) {
        directionX = -std::abs(directionX);
    }

    if (positiony - size / 2 <= 0) {
        directionY = std::abs(directionY);
    }
    /*else if (positiony + size / 2 >= SCREEN_HEIGHT) {
        directionY = -std::abs(directionY);
    }*/
}

void Ball::setPosition(float posx, float posy) {
    positionx = posx;
    positiony = posy;
    ballShape.setPosition(positionx, positiony);
}

std::pair<float, float> Ball::getPosition() {
    return { positionx, positiony };
}
