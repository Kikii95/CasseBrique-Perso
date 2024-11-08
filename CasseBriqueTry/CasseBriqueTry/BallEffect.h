#pragma once
#include "Ball.h"
#include <functional>
#include <string>

enum class BallEffectType {
    BallSpeedBoost,
    BallSpeedNerf,
    BallSizeBoost,
    BallSizeNerf,
    BallPiercing,
    BallSplit,
    BallExplosive,
    BallRandomDirection,
    BallReverse,
    BallMultiplier,
    BallTeleport,
    BallInvisible,
    BallPathPredictor,
    BallChaos,
};

class BallEffect {
protected:
    BallEffectType type;
    Ball& ball;
    int duration;
    bool isActive;
    std::function<void(Ball&)> applyCallback;
    std::function<void(Ball&)> removeCallback;

    static int EffectDuration;

public:
    BallEffect(BallEffectType type, Ball& ball, int duration,
        std::function<void(Ball&)> applyCallback,
        std::function<void(Ball&)> removeCallback);

    virtual ~BallEffect() = default;

    virtual void applyEffect();
    virtual void removeEffect();
    virtual void update(float deltaTime);
    void resetDuration();
    bool isEffectActive() const;
    std::string BallEffectTypeToString() const;
    
    static int getEffectDuration();

    virtual BallEffectType getType() const = 0;

    };


