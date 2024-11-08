#include "BallEffectList.h"


BallSpeedBoost::BallSpeedBoost(Ball& ball, std::vector<Ball>& activeBalls, int duration)
    : BallEffect(BallEffectType::BallSpeedBoost, activeBalls.front(), duration,
        [&activeBalls](Ball&) {
            for (auto& ball : activeBalls) {
                ball.setSpeed(ball.originalSpeed * 1.5f);
                ball.getShape().setFillColor(sf::Color::Red);
            }
        },
        [&activeBalls](Ball&) {
            for (auto& ball : activeBalls) {
                ball.setSpeed(ball.originalSpeed);
                ball.getShape().setFillColor(sf::Color::White);
            }
        }) {}

BallEffectType BallSpeedBoost::getType() const {
    return BallEffectType::BallSpeedBoost;
}

BallSpeedNerf::BallSpeedNerf(Ball& ball, std::vector<Ball>& activeBalls, int duration)
    : BallEffect(BallEffectType::BallSpeedNerf, activeBalls.front(), duration,
        [&activeBalls](Ball&) {
            for (auto& ball : activeBalls) {
                ball.setSpeed(ball.originalSpeed * 1.5f);
                ball.getShape().setFillColor(sf::Color::Blue);
            }
        },
        [&activeBalls](Ball&) {
            for (auto& ball : activeBalls) {
                ball.setSpeed(ball.originalSpeed);
                ball.getShape().setFillColor(sf::Color::White);
            }
        }) {}

BallEffectType BallSpeedNerf::getType() const {
    return BallEffectType::BallSpeedNerf;
}

BallSizeBoost::BallSizeBoost(Ball& ball, std::vector<Ball>& activeBalls, int duration)
    : BallEffect(BallEffectType::BallSizeBoost, activeBalls.front(), duration,
        [&activeBalls](Ball&) {
            for (auto& ball : activeBalls) {
                ball.setSize(ball.originalSize * 1.5f);
                ball.getShape().setFillColor(sf::Color::Green);
            }
        },
        [&activeBalls](Ball&) {
            for (auto& ball : activeBalls) {
                ball.setSize(ball.originalSize);                 
                ball.getShape().setFillColor(sf::Color::White);
            }
        }) {}


BallEffectType BallSizeBoost::getType() const {
    return BallEffectType::BallSizeBoost;
}


BallSizeNerf::BallSizeNerf(Ball& ball, std::vector<Ball>& activeBalls, int duration)
    : BallEffect(BallEffectType::BallSizeNerf, activeBalls.front(), duration,
        [&activeBalls](Ball&) {
            for (auto& ball : activeBalls) {
                ball.setSize(ball.originalSize * 0.75f);
                ball.getShape().setFillColor(sf::Color::Blue);
            }
        },
        [&activeBalls](Ball&) {
            for (auto& ball : activeBalls) {
                ball.setSize(ball.originalSize);                 
                ball.getShape().setFillColor(sf::Color::White);
            }
        }) {}


BallEffectType BallSizeNerf::getType() const {
    return BallEffectType::BallSizeNerf;
}


BallPiercing::BallPiercing(Ball& ball, std::vector<Ball>& activeBalls, int duration)
    : BallEffect(BallEffectType::BallPiercing, activeBalls.front(), duration,
        [&activeBalls](Ball&) {
            for (auto& ball : activeBalls) {
                ball.setPiercing(true);
                ball.getShape().setFillColor(sf::Color::Yellow);
            }
        },
        [&activeBalls](Ball&) {
            for (auto& ball : activeBalls) {
                ball.setPiercing(false);
                ball.getShape().setFillColor(sf::Color::White);
            }
        }) {}

BallEffectType BallPiercing::getType() const {
    return BallEffectType::BallPiercing;
}

BallRandomDirection::BallRandomDirection(Ball& ball, std::vector<Ball>& activeBalls)
    : BallEffect(BallEffectType::BallRandomDirection, activeBalls.front(), 0,
        [&activeBalls](Ball&) {
            for (auto& ball : activeBalls) {
                float directionX = (static_cast<float>(std::rand()) / RAND_MAX) * 2 - 1;
                float directionY = (static_cast<float>(std::rand()) / RAND_MAX) * 2 - 1;
                ball.setDirection(directionX, directionY);
            }
        },
        nullptr) {}

BallEffectType BallRandomDirection::getType() const {
    return BallEffectType::BallRandomDirection;
}

BallInvisible::BallInvisible(Ball& ball, std::vector<Ball>& activeBalls, int duration)
    : BallEffect(BallEffectType::BallInvisible, activeBalls.front(), duration,
        [&activeBalls](Ball&) {
            for (auto& ball : activeBalls) {
                ball.getShape().setFillColor(sf::Color(255, 255, 255, 5));
            }
        },
        [&activeBalls](Ball&) {
            for (auto& ball : activeBalls) {
                ball.getShape().setFillColor(sf::Color::White);
            }
        }) {}

BallEffectType BallInvisible::getType() const {
    return BallEffectType::BallInvisible;
}

BallMultiplier::BallMultiplier(Ball& ball, std::vector<Ball>& activeBalls, int duration, int multiplier)
    : BallEffect(BallEffectType::BallMultiplier, activeBalls.front(), duration,
        [&activeBalls, multiplier](Ball&) {
            for (auto& ball : activeBalls) {
                ball.setScoreMultiplier(multiplier);
                ball.getShape().setFillColor(sf::Color::Magenta);
            }
        },
        [&activeBalls](Ball&) {
            for (auto& ball : activeBalls) {
                ball.setScoreMultiplier(1);
                ball.getShape().setFillColor(sf::Color::White);
            }
        }) {}

BallEffectType BallMultiplier::getType() const {
    return BallEffectType::BallMultiplier;
}

BallReverse::BallReverse(Ball& ball, std::vector<Ball>& activeBalls, int duration)
    : BallEffect(BallEffectType::BallReverse, activeBalls.front(), duration,
        [&activeBalls](Ball&) {
            for (auto& ball : activeBalls) {
                ball.setReverseBounce(true);
                ball.getShape().setFillColor(sf::Color::Cyan);
            }
        },
        [&activeBalls](Ball&) {
            for (auto& ball : activeBalls) {
                ball.setReverseBounce(false);
                ball.getShape().setFillColor(sf::Color::White);
            }
        }) {}

BallEffectType BallReverse::getType() const {
    return BallEffectType::BallReverse;
}

BallTeleport::BallTeleport(Ball& ball, std::vector<Ball>& activeBalls)
    : BallEffect(BallEffectType::BallTeleport, activeBalls.front(), 0,         [&activeBalls](Ball&) {
            for (auto& ball : activeBalls) {
                float newX = static_cast<float>(std::rand() % SCREEN_WIDTH);
                float newY = static_cast<float>(std::rand() % (SCREEN_HEIGHT / 2));
                ball.setPosition(newX, newY);
            }
        },
        nullptr) {}

BallEffectType BallTeleport::getType() const {
    return BallEffectType::BallTeleport;
}

BallChaos::BallChaos(Ball& ball, std::vector<Ball>& activeBalls, const sf::RectangleShape& pad, int duration)
    : BallEffect(BallEffectType::BallChaos, ball, duration,
        [&activeBalls, &pad](Ball& b) {
                        for (int i = 0; i < 3; ++i) {
                float randomSpeed = 200.0f + (std::rand() % 300);
                float directionX = (static_cast<float>(std::rand()) / RAND_MAX) * 2 - 1;
                float directionY = (static_cast<float>(std::rand()) / RAND_MAX) * 2 - 1;

                float startX = pad.getPosition().x + pad.getSize().x / 2.0f;                 
                float startY = pad.getPosition().y - b.getSize();            
                Ball newBall(startX, startY, randomSpeed, b.getSize());
                newBall.setDirection(directionX, directionY);

                activeBalls.push_back(newBall);                  
            }
        },
        [&activeBalls, &ball](Ball& b) {
                        if (activeBalls.size() > 1) {
                activeBalls.erase(activeBalls.begin() + 1, activeBalls.end());
            }
            b.setSpeed(400);             
        }),
    activeBalls(activeBalls) {}

BallEffectType BallChaos::getType() const {
    return BallEffectType::BallChaos;
}

BallSplit::BallSplit(Ball& ball, std::vector<Ball>& activeBalls, int duration)
    : BallEffect(BallEffectType::BallSplit, ball, duration,
        [&activeBalls](Ball& b) {
            std::vector<Ball> newBalls; 
            for (auto& activeBall : activeBalls) {
                auto currentPos = activeBall.getPosition();
                auto originalDirection = activeBall.getDirection();

                float newDirectionX = - originalDirection.first;
                float newDirectionY = - originalDirection.second;

                Ball newBall(currentPos.first, currentPos.second, activeBall.getSpeed(), activeBall.getSize());
                newBall.setDirection(newDirectionX, newDirectionY);
                newBall.normalizeDirection();

                newBalls.push_back(newBall);                 
            }

                        activeBalls.insert(activeBalls.end(), newBalls.begin(), newBalls.end());
        },
        [](Ball&) {
                    }) {}


BallEffectType BallSplit::getType() const {
    return BallEffectType::BallSplit;
}



