#pragma once
#include "Ball.h"


enum class BallEffectType {
    BallSpeedBoost,
    BallSpeedNerf,
};

class BallEffect {
protected:
    BallEffectType type;
    Ball& ball; 
    int duration;
    bool isActive;

public:
    BallEffect(BallEffectType type, Ball& ball, int duration)
        : type(type), ball(ball), duration(duration), isActive(false) {}

    virtual ~BallEffect() = default;
    std::string BallEffectTypeToString(BallEffectType type);
    virtual void applyBallEffect() = 0;
    virtual void removeBallEffect() = 0;
    void update(float deltaTime);
    void display();

    bool isEffectActive()  { return isActive; }
};
