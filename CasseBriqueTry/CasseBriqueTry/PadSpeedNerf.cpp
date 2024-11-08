#include "PadSpeedNerf.h"

PadSpeedNerf::PadSpeedNerf(Pad& pad, int duration) : PadEffect(PadEffectType::PadSpeedNerf, pad, duration) {}

void PadSpeedNerf::applyPadEffect() {
    pad.setSpeed(pad.getSpeed() / 10);
    isActive = true;
    PadEffect::display();
}

void PadSpeedNerf::removePadEffect() {
    pad.setSpeed(pad.getSpeed() * 2);
    isActive = false;
    PadEffect::display();
}
