#pragma once
#include "BallEffect.h"
#include <vector>

class BallSpeedBoost : public BallEffect {
public:
    BallSpeedBoost(Ball& ball, std::vector<Ball>& activeBalls, int duration);
    BallEffectType getType() const override;
};

class BallSpeedNerf : public BallEffect {
public:
    BallSpeedNerf(Ball& ball, std::vector<Ball>& activeBalls, int duration);
    BallEffectType getType() const override;
};

class BallSizeBoost : public BallEffect {
public:
    BallSizeBoost(Ball& ball, std::vector<Ball>& activeBalls, int duration);
    BallEffectType getType() const override;
};

class BallSizeNerf : public BallEffect {
public:
    BallSizeNerf(Ball& ball, std::vector<Ball>& activeBalls, int duration);
    BallEffectType getType() const override;
};

class BallPiercing : public BallEffect {
public:
    BallPiercing(Ball& ball, std::vector<Ball>& activeBalls, int duration);
    BallEffectType getType() const override;
};

class BallRandomDirection : public BallEffect {
public:
    BallRandomDirection(Ball& ball, std::vector<Ball>& activeBalls);
    BallEffectType getType() const override;
};

class BallInvisible : public BallEffect {
public:
    BallInvisible(Ball& ball, std::vector<Ball>& activeBalls, int duration);
    BallEffectType getType() const override;
};

class BallMultiplier : public BallEffect {
public:
    BallMultiplier(Ball& ball, std::vector<Ball>& activeBalls, int duration, int multiplier);
    BallEffectType getType() const override;
};

class BallReverse : public BallEffect {
public:
    BallReverse(Ball& ball, std::vector<Ball>& activeBalls, int duration);
    BallEffectType getType() const override;
};

class BallTeleport : public BallEffect {
public:
    BallTeleport(Ball& ball, std::vector<Ball>& activeBalls);
    BallEffectType getType() const override;
};

class BallChaos : public BallEffect {
public:
    BallChaos(Ball& ball, std::vector<Ball>& activeBalls, const sf::RectangleShape& pad, int duration);

    BallEffectType getType() const override;

private:
    std::vector<Ball>& activeBalls;
};

class BallSplit : public BallEffect {
public:
    BallSplit(Ball& ball, std::vector<Ball>& activeBalls, int duration);

    BallEffectType getType() const override;
};

