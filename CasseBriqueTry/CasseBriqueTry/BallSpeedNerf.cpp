#include "BallSpeedNerf.h"

BallSpeedNerf::BallSpeedNerf(Ball& ball, int duration) : BallEffect(BallEffectType::BallSpeedNerf, ball, duration) {}

void BallSpeedNerf::applyBallEffect() {
    ball.setSpeed(ball.getSpeed() / 2);
    isActive = true;
    BallEffect::display();
}

void BallSpeedNerf::removeBallEffect() {
    ball.setSpeed(ball.getSpeed() * 2);
    isActive = false;
    BallEffect::display();
}
