#include "Ball.h"
#include <cstdlib>
#include <ctime>

float Ball::originalSpeed = 500.0f;
float Ball::originalSize = 40.0f;

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

void Ball::setPiercing(bool value) { 
    isPiercing = value; 
}

bool Ball::getPiercing() const { 
    return isPiercing; 
}

void Ball::setSize(int siz) {
    size = siz;
    ballShape.setRadius(size / 2); 
    ballShape.setOrigin(size / 2, size / 2); 
}

int Ball::getSize() {
    return size;
}

void Ball::setScoreMultiplier(int multiplier) {
    scoreMultiplier = multiplier > 0 ? multiplier : 1; 
}

int Ball::getScoreMultiplier() const { 
    return scoreMultiplier; 
}

bool Ball::isReverseBounceActive() const {
    return reverseBounce; 
}

void Ball::setReverseBounce(bool reverse) {
    reverseBounce = reverse;
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
        float normalizedDistance = distanceFromCenter / (pad.getSize().x / 2.0f);

        directionX = reverseBounce ? -normalizedDistance : normalizedDistance;

                directionY = -1.0f;

        normalizeDirection();
    }
}


void Ball::wallBounce(Pad& pad) {
    if (positionx - size / 2 <= 0) {          directionX = std::abs(directionX);
        if (reverseBounce) {
            directionY = -directionY;          }
    }
    else if (positionx + size / 2 >= SCREEN_WIDTH) {         directionX = -std::abs(directionX);
        if (reverseBounce) {
            directionY = -directionY;          }
    }

    if (positiony - size / 2 <= 0) {          directionY = std::abs(directionY);
        if (reverseBounce) {
            directionX = -directionX;          }
    }

    /*if (positiony + size / 2 >= SCREEN_HEIGHT) {
        if (pad.isShieldActive()) {
            directionY = -std::abs(directionY);
            std::cout << "Shield deflected the ball at the bottom wall!\n";
        }
    }*/
}

void Ball::brickBounce(Brick& brick) {
    if (ballShape.getGlobalBounds().intersects(brick.getBounds())) {
        sf::FloatRect brickBounds(brick.getBounds());
        sf::FloatRect ballBounds = ballShape.getGlobalBounds();

                float overlapLeft = ballBounds.left + ballBounds.width - brickBounds.left;
        float overlapRight = brickBounds.left + brickBounds.width - ballBounds.left;
        float overlapTop = ballBounds.top + ballBounds.height - brickBounds.top;
        float overlapBottom = brickBounds.top + brickBounds.height - ballBounds.top;

        float minOverlap = std::min({ overlapLeft, overlapRight, overlapTop, overlapBottom });

        if (minOverlap == overlapLeft) {              directionX = -std::abs(directionX);
        }
        else if (minOverlap == overlapRight) {              directionX = std::abs(directionX);
        }
        else if (minOverlap == overlapTop) {              directionY = -std::abs(directionY);
        }
        else if (minOverlap == overlapBottom) {              directionY = std::abs(directionY);
        }

        brick.destroy();      }
}

void Ball::move(float deltaTime, sf::RectangleShape& pad, std::vector<Brick>& bricks, Pad& Pad) {
    normalizeDirection();
    positionx += directionX * speed * deltaTime;
    positiony += directionY * speed * deltaTime;

    ballShape.setPosition(positionx, positiony);

    wallBounce(Pad);
    padBounce(pad);

    for (auto it = bricks.begin(); it != bricks.end(); /* Pas d'incr�ment ici */) {
        if (it->checkCollision(ballShape)) {
            brickBounce(*it);  
            it->destroy();

            if (!isPiercing) {
                break;              }
            else {
                it = bricks.erase(it);                  continue;
            }
        }
        ++it;     }

    ballShape.setPosition(positionx, positiony);
}


void Ball::setPosition(float posx, float posy) {
    positionx = posx;
    positiony = posy;
    ballShape.setPosition(positionx, positiony);
}

std::pair<float, float> Ball::getPosition() {
    return { positionx, positiony };
}


void Ball::normalizeDirection() {
    float magnitude = std::sqrt(directionX * directionX + directionY * directionY);
    if (magnitude != 0) {
        directionX /= magnitude;
        directionY /= magnitude;
    }
}
