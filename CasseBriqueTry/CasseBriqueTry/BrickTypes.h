#pragma once
#include "Brick.h"
#include "Ball.h"
#include "Pad.h"

class ExplosiveBrick : public Brick {
public:
    using Brick::Brick;
    void explode(std::vector<Brick>& bricks, int radius);
};

class BonusBrick : public Brick {
public:
    using Brick::Brick;
    void applyBonusEffect(Ball& ball, Pad& pad);
};

class TrapBrick : public Brick {
public:
    using Brick::Brick;
    void applyTrapEffect(Ball& ball, Pad& pad);
};
