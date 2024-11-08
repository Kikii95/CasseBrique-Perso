#include "PadSpeedBoost.h"

PadSpeedBoost::PadSpeedBoost(Pad& pad, int duration): PadEffect(PadEffectType::PadSpeedBoost, pad, duration), pad(pad), originalSpeed(pad.getSpeed()) {}

void PadSpeedBoost::applyPadEffect() {
    pad.setSpeed(originalSpeed);

    pad.setSpeed(pad.getSpeed() * 1.5);
    isActive = true;
    PadEffect::display();
}

void PadSpeedBoost::removePadEffect() {
    pad.setSpeed(originalSpeed);
    isActive = false;
    PadEffect::display();
}