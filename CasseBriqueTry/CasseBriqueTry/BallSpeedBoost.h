#pragma once
#include "BallEffect.h"

class BallSpeedBoost : public BallEffect {
public:
    BallSpeedBoost(Ball& ball, int duration);

    void applyBallEffect() override;
    void removeBallEffect() override;

private:
    Ball& ball;
    float originalSpeed;
};

