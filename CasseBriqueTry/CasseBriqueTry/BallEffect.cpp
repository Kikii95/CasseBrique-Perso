#include "BallEffect.h"
#include <iostream>

int BallEffect::EffectDuration = 7500; 

BallEffect::BallEffect(BallEffectType type, Ball& ball, int duration,
    std::function<void(Ball&)> applyCallback,
    std::function<void(Ball&)> removeCallback)
    : type(type), ball(ball), duration(duration),
    isActive(false), applyCallback(applyCallback), removeCallback(removeCallback) {}

void BallEffect::applyEffect() {
    if (isActive) return; 
    if (applyCallback) {
        applyCallback(ball);
    }

    isActive = true;
    duration = EffectDuration; }

void BallEffect::removeEffect() {
    if (removeCallback) {
        removeCallback(ball);
    }
    isActive = false;
}

void BallEffect::update(float deltaTime) {
    if (isActive && duration > 0) {
        /*std::cout << "Time : " << duration << std::endl;*/
        duration -= deltaTime;
        if (duration <= 0) {
            removeEffect();
        }
    }
}

int BallEffect::getEffectDuration() {
    return EffectDuration;
}

void BallEffect::resetDuration() {
    if (!isActive) return;     /*std::cout << "Time avant reset :" << duration << std::endl;*/
    duration = EffectDuration;     /*std::cout << "Time apres reset :" << duration << std::endl;*/
}

bool BallEffect::isEffectActive() const {
    return isActive;
}

std::string BallEffect::BallEffectTypeToString() const {
    switch (type) {
    case BallEffectType::BallSpeedBoost: return "Speed Boost";
    case BallEffectType::BallSpeedNerf: return "Speed Nerf";
    case BallEffectType::BallSizeBoost: return "Size Boost";
    case BallEffectType::BallSizeNerf: return "Size Nerf";
    case BallEffectType::BallPiercing: return "Piercing";
    case BallEffectType::BallSplit: return "Split";
    /*case BallEffectType::BallExplosive: return "Explosive";*/
    case BallEffectType::BallRandomDirection: return "Random Direction";
    case BallEffectType::BallReverse: return "Reverse";
    case BallEffectType::BallMultiplier: return "Multiplier";
    case BallEffectType::BallTeleport: return "Teleport";
    case BallEffectType::BallInvisible: return "Invisible";
    /*case BallEffectType::BallPathPredictor: return "Path Predictor";*/
    case BallEffectType::BallChaos: return "Chaos";
    default: return "Unknown Effect";
    }
}
