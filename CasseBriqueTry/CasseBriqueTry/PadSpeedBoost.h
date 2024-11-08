#pragma once
#include "PadEffect.h"

class PadSpeedBoost : public PadEffect {
public:
    PadSpeedBoost(Pad& pad, int duration);

    void applyPadEffect() override;
    void removePadEffect() override;

private:
    Pad& pad; 
    float originalSpeed; 

};
