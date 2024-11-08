#include "BallEffect.h"
#include <iostream>

void BallEffect::update(float deltaTime) {
    if (isActive && duration > 0) {
        std::cout << "Temps : " << duration << std::endl;
        duration -= deltaTime;
        if (duration <= 0) {
            isActive = false;
            removeBallEffect();
        }
    }
}

void BallEffect::display() {
    if (isActive) {
        std::cout << "Effet actif : " << BallEffectTypeToString(type) << " sur la ball en position ("
            << ball.getPosition().first << ", " << ball.getPosition().second << ") " << std::endl;
    }
    else {
        std::cout << "Effet inactif : " << BallEffectTypeToString(type) << " sur la ball en position ("
            << ball.getPosition().first << ", " << ball.getPosition().second << ") " << std::endl;
    }

}

std::string BallEffect::BallEffectTypeToString(BallEffectType type) {
    switch (type) {
    case BallEffectType::BallSpeedBoost: return "Speed Boost";
    case BallEffectType::BallSpeedNerf: return "Speed Nerf";
    default: return "Unknown Effect";
    }
}
