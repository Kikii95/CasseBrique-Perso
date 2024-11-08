#include "PadEffectList.h"
#include <iostream>

PadSpeedBoost::PadSpeedBoost(Pad& pad, int duration)
    : PadEffect(PadEffectType::PadSpeedBoost, pad, duration,
        [&pad](Pad&) {
            pad.setSpeed(Pad::originalSpeed * 1.5f);
        },
        [&pad](Pad&) {
            pad.setSpeed(Pad::originalSpeed);
        }) {}


PadEffectType PadSpeedBoost::getType()  {
    return PadEffectType::PadSpeedBoost;
}

PadSpeedNerf::PadSpeedNerf(Pad& pad, int duration)
    : PadEffect(PadEffectType::PadSpeedNerf, pad, duration,
        [&pad](Pad&) {
            pad.setSpeed(Pad::originalSpeed * 0.5f);
        },
        [&pad](Pad&) {
            pad.setSpeed(Pad::originalSpeed);
        }) {}


PadEffectType PadSpeedNerf::getType()  {
    return PadEffectType::PadSpeedNerf;
}

PadSizeBoost::PadSizeBoost(Pad& pad, int duration)
    : PadEffect(PadEffectType::PadSizeBoost, pad, duration,
        [&pad](Pad&) {
            pad.setSize(pad.getSize().first * 1.5f);
        },
        [&pad](Pad&) {
            pad.setSize(Pad::originalSize.first);
        }) {}


PadEffectType PadSizeBoost::getType()  {
    return PadEffectType::PadSizeBoost;
}

PadSizeNerf::PadSizeNerf(Pad& pad, int duration)
    : PadEffect(PadEffectType::PadSizeNerf, pad, duration,
        [&pad](Pad&) {
            pad.setSize(pad.getSize().first * 0.5f);
        },
        [&pad](Pad&) {
            pad.setSize(Pad::originalSize.first);
        }) {}


PadEffectType PadSizeNerf::getType()  {
    return PadEffectType::PadSizeNerf;
}


