#include "PadEffect.h"
#include <iostream>

PadEffect::PadEffect(PadEffectType type, Pad& pad, int duration,
    std::function<void(Pad&)> applyCallback,
    std::function<void(Pad&)> removeCallback)
    : type(type), pad(pad), duration(duration), isActive(false),
    applyCallback(applyCallback), removeCallback(removeCallback) {}

void PadEffect::applyEffect() {
    if (!isActive) {
        applyCallback(pad);
        isActive = true;
    }
}

void PadEffect::removeEffect() {
    if (isActive) {
        removeCallback(pad);
        isActive = false;
    }
}

void PadEffect::update(float deltaTime) {
    if (isActive && duration > 0) {
        duration -= deltaTime;
        if (duration <= 0) {
            removeEffect();
        }
    }
}

bool PadEffect::isEffectActive() const {
    return isActive;
}

std::string PadEffect::PadEffectTypeToString()  {
    switch (type) {
    case PadEffectType::PadSpeedBoost: return "Speed Boost";
    case PadEffectType::PadSpeedNerf: return "Speed Nerf";
    case PadEffectType::PadSizeBoost: return "Size Increase";
    case PadEffectType::PadSizeNerf: return "Size Decrease";
    /*case PadEffectType::PadShield: return "Invert Controls";*/
    default: return "Unknown Effect";
    }
}


