#pragma once
#include "BallEffect.h"

class BallSpeedNerf : public BallEffect {
public:
    BallSpeedNerf(Ball& ball, int duration);

    void applyBallEffect() override;
    void removeBallEffect() override;
};

