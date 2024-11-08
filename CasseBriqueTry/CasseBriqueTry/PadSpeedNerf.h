#pragma once
#include "PadEffect.h"

class PadSpeedNerf : public PadEffect {
public:
    PadSpeedNerf(Pad& pad, int duration);

    void applyPadEffect() override;
    void removePadEffect() override;
};
