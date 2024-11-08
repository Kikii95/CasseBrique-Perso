#pragma once
#include <functional>
#include <string>
#include <vector>
#include "Pad.h"

enum class PadEffectType {
    PadSpeedBoost,
    PadSpeedNerf,
    PadSizeBoost,
    PadSizeNerf,
    PadSticky,
    PadInvertedControls,
    PadMagnet,
    PadProjectile,
    PadShield,
    PadBallMultiplier,
    PadSliding,
    PadSplit,
    PadEnergyDrain,
};

class PadEffect {
protected:
    PadEffectType type;
    Pad& pad;
    int duration;
    bool isActive;
    std::function<void(Pad&)> applyCallback;
    std::function<void(Pad&)> removeCallback;


public:
    PadEffect(PadEffectType type, Pad& pad, int duration,
        std::function<void(Pad&)> applyCallback,
        std::function<void(Pad&)> removeCallback);

    virtual ~PadEffect() = default;

    virtual void applyEffect();
    virtual void removeEffect();
    virtual void update(float deltaTime);
    bool isEffectActive() const;
    std::string PadEffectTypeToString() ;
    virtual PadEffectType getType()  = 0;

};
