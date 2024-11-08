#include "PadEffect.h"
#include <iostream>

void PadEffect::update(float deltaTime) {
    if (isActive && duration > 0) {
        duration -= deltaTime;
        if (duration <= 0) {
            isActive = false;
            removePadEffect();
        }
    }
}

void PadEffect::display() {
    if (isActive) {
        std::cout << "Effet actif : " << PadEffectTypeToString(type) << " sur le pad en position ("
            << pad.getPosition().first << ", " << pad.getPosition().second << ") "<< std::endl;
    }
    else {
        std::cout << "Effet inactif : " << PadEffectTypeToString(type) << " sur le pad en position ("
            << pad.getPosition().first << ", " << pad.getPosition().second << ") " << std::endl;
    }
    
}

std::string PadEffect::PadEffectTypeToString(PadEffectType type) {
    switch (type) {
    case PadEffectType::PadSpeedBoost: return "Speed Boost";
    case PadEffectType::PadSpeedNerf: return "Speed Nerf";
    default: return "Unknown Effect";
    }
}
