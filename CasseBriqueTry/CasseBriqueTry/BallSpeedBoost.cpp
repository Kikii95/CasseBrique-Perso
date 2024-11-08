#include "BallSpeedBoost.h"
#include "Pad.h"

BallSpeedBoost::BallSpeedBoost(Ball& ball, int duration) : BallEffect(BallEffectType::BallSpeedBoost, ball, duration), ball(ball), originalSpeed(ball.getSpeed()) {}

void BallSpeedBoost::applyBallEffect() {
    ball.setSpeed(originalSpeed);

    ball.setSpeed(ball.getSpeed() * 1.5);
    isActive = true;
    BallEffect::display();
}

void BallSpeedBoost::removeBallEffect() {
    ball.setSpeed(originalSpeed);
    isActive = false;
    BallEffect::display();
}
