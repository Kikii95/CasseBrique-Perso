//#include "BrickTypes.h"
//
//void ExplosiveBrick::explode(std::vector<Brick>& bricks, int radius) {
//    for (Brick& brick : bricks) {
//        if (!brick.isBroken()&& brick.getShape() {
//            brick.destroy();
//        }
//    }
//
//    for (Ball& ball : bricks) {
//
//    }
//
//}
//
//void BonusBrick::applyBonusEffect(Ball& ball, Pad& pad) {
//    int bonusType = rand() % 2;
//    if (bonusType == 0) {
//        ball.setSpeed(ball.getSpeed() / 2);     }
//    else {
//        pad.setSize(pad.getSize().first * 1.5);     }
//}
//
//void TrapBrick::applyTrapEffect(Ball& ball, Pad& pad) {
//    int trapType = rand() % 2;
//    if (trapType == 0) {
//        ball.setSpeed(ball.getSpeed() * 1.5);     }
//    else {
//        pad.setSize(pad.getSize().first * 0.7);     }
//}
