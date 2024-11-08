#pragma once
#include "PadEffect.h"
#include <memory>
#include <vector>

class PadSpeedBoost : public PadEffect {
public:
    PadSpeedBoost(Pad& pad, int duration);
    PadEffectType getType()  override;
};

class PadSpeedNerf : public PadEffect {
public:
    PadSpeedNerf(Pad& pad, int duration);
    PadEffectType getType()  override;
};

class PadSizeBoost : public PadEffect {
public:
    PadSizeBoost(Pad& pad, int duration);
    PadEffectType getType()  override;
};

class PadSizeNerf : public PadEffect {
public:
    PadSizeNerf(Pad& pad, int duration);
    PadEffectType getType()  override;
};


