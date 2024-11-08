#include "Game.h"

#include <memory>

#include "FileUtils.h"  
#include <fstream>
#include <iostream>
#include "BallEffectList.h"




Game::Game()
    : window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Casse-Brique", sf::Style::Fullscreen),
    hud(SCREEN_WIDTH, SCREEN_HEIGHT, window),
         isGameOver(false),
    pad((0.8 * SCREEN_WIDTH), (0.2 * SCREEN_HEIGHT)),
    ball(pad.getPosition().first + pad.getSize().first / 2, pad.getPosition().second - ball.originalSize, ball.originalSpeed, ball.originalSize),
    levelManager(),
    isMainMenuActive(true),
    isPaused(false),
    padShape(sf::Vector2f(pad.getSize().first, pad.getSize().second))
{
    if (!heartTexture.loadFromFile("heart.png")) {
        std::cerr << "Erreur : Impossible de charger la texture de c�ur" << std::endl;
    }
    if (!heartLostTexture.loadFromFile("heart_black.png")) {
        std::cerr << "Erreur : Impossible de charger la texture de c�ur perdu" << std::endl;
    }

    for (int i = 0; i < 3; ++i) {
        sf::Sprite heart(heartTexture);
        heart.setScale(0.000018f * SCREEN_WIDTH, 0.000018f * SCREEN_WIDTH);
        heart.setPosition(20 + i * (heart.getGlobalBounds().width + 10), 0);
        hearts.push_back(heart);
    }

    initializeMusic();
    loadBrickTexture();

    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    padShape.setFillColor(sf::Color::Blue);
}

void Game::run() {
    while (window.isOpen()) {
        processEvents();
        float deltaTime = clock.restart().asSeconds();

        if (isLevelEditorActive) {
            updateLevelEditor();
        }
        else {
            update(deltaTime);
        }

        render();
    }
}


void Game::resetBall() {
        for (auto& effect : activeBallEffects) {
        effect->removeEffect();
    }
    activeBallEffects.clear(); 
        if (activeBalls.empty()) {
        Ball newBall(pad.getPosition().first + pad.getSize().first / 2,
            pad.getPosition().second - ball.originalSize / 2,
            ball.originalSpeed,
            ball.originalSize);
        activeBalls.push_back(newBall);
    }

        Ball& mainBall = activeBalls.front();
    mainBall.setPosition(pad.getPosition().first + pad.getSize().first / 2,
        pad.getPosition().second - mainBall.getSize() / 2);
    mainBall.setSpeed(ball.originalSpeed);

        float directionX;
    do {
        directionX = (static_cast<float>(std::rand()) / RAND_MAX) * 0.8f - 0.4f;
    } while (std::abs(directionX) < 0.1f);

    mainBall.setDirection(directionX, -1.0f);
    mainBall.normalizeDirection();

    isBallLaunched = false; }






void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (isMainMenuActive) {
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up) {
                    hud.getMainMenu().moveUp();
                }
                else if (event.key.code == sf::Keyboard::Down) {
                    hud.getMainMenu().moveDown();
                }
                else if (event.key.code == sf::Keyboard::Enter) {
                    int selectedOption = hud.getMainMenu().getSelectedItemIndex();
                    if (selectedOption == 0) {
                        isMainMenuActive = false;
                        initializeLevelManager();
                    }
                    else if (selectedOption == 2) {
                        isMainMenuActive = false;
                        isLevelEditorActive = true;
                        
                    }
                    else if (selectedOption == 3) {
                        window.close();
                    }
                }
            }
        }
        else if (isPaused) {
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up) {
                    hud.getPauseMenu().moveUp();
                }
                else if (event.key.code == sf::Keyboard::Down) {
                    hud.getPauseMenu().moveDown();
                }
                else if (event.key.code == sf::Keyboard::Enter) {
                    int selectedOption = hud.getPauseMenu().getSelectedItemIndex();
                    if (selectedOption == 0 /*Play*/) {
                        isPaused = false;
                    }
                    else if (selectedOption == 1 /* Restart */) {
                        LevelType currentLevel = levelManager.getCurrentLevel();
                        levelManager.initializeLevel(currentLevel, pad, ball, bricks);

                        lives = 3;
                        for (size_t i = 0; i < hearts.size(); ++i) {
                            hearts[i].setTexture(heartTexture);
                        }

                        isBallLaunched = false;
                        isPaused = false;
                    }
                    else if (selectedOption == 2 /*Option*/) {
                        /*isOption = true;*/
                    }
                    else if (selectedOption == 3 /*Quit*/) {
                        isMainMenuActive = true;
                        isPaused = false;
                    }
                }
            }
        }



        else {
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                isMainMenuActive = false;
                levelManager.setSelectedOption(0);
            }
        }
    }
}


void Game::initializeMusic() {
    if (music.loadFromFile("medievale.ogg")) {
        music.setLoop(true);
        music.setVolume(50);
        music.play();
    }
    else {
        std::cerr << "Erreur : Impossible de charger la musique." << std::endl;
    }
}

void Game::loadBrickTexture() {
    Brick::loadTexture("SharinganBrick3T.png");
}

void Game::initializeLevelManager() {
    LevelManager levelManager;
    if (!levelManager.selectLevel(window, 0)) {
        std::cerr << "Erreur lors de la s�lection du niveau" << std::endl;
        window.close();
        return;
    }
    activeBalls.clear();
    activeBalls.push_back(ball);

    levelManager.initializeLevel(levelManager.getCurrentLevel(), pad, ball, bricks);
    levelManager.renderLevel(window, pad, ball, bricks);
}
void Game::updateLevelEditor() {
        while (window.pollEvent(event)) {
                if (event.key.code == sf::Keyboard::S) {
            std::cout << "Saving Level" << std::endl;
            saveLevel();
            std::cout << "Level saved successfully" << std::endl;
        }
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        int brickWidth = 60, brickHeight = 20;
        bricks.emplace_back(mousePos.x, mousePos.y, brickWidth, brickHeight);
        std::cout << "Brick added at position: (" << mousePos.x << ", " << mousePos.y << ")" << std::endl;
    }
    
}







void Game::saveLevel() {
    int levelNumber = getNextLevelNumber();
    std::string fileName = "level_" + std::to_string(levelNumber) + ".lvl";
    std::ofstream levelFile(fileName);

    if (levelFile.is_open()) {
        std::cout << "Saving to file: " << fileName << std::endl;
        for (auto& brick : bricks) {
            levelFile << brick.getPositionX() << " "
                << brick.getPositionY() << " "
                << brick.getSizeX() << " "
                << brick.getSizeY() << "\n";
        }
        levelFile.close();
        std::cout << "Niveau " << levelNumber << " enregistr� sous " << fileName << std::endl;
    }
    else {
        std::cerr << "Erreur : impossible de cr�er le fichier " << fileName << std::endl;
    }
}

int Game::getNextLevelNumber()  {
    int level = 1;
    while (fileExists("level_" + std::to_string(level) + ".lvl")) {
        ++level;
    }
    return level;
}


void Game::checkLife() {
        for (auto it = activeBalls.begin(); it != activeBalls.end();) {
        if (it->getPosition().second > SCREEN_HEIGHT) {
            it = activeBalls.erase(it);         }
        else {
            ++it;         }
    }

        if (activeBalls.empty()) {
        --lives;

                if (lives >= 0 && lives < hearts.size()) {
            hearts[lives].setTexture(heartLostTexture);
        }

        if (lives > 0) {
                        resetBall();         }
        else {
                        isGameOver = true;
        }
    }
}




void Game::update(float deltaTime) {
    if (isGameOver) {
        return;
    }
    if (!isMainMenuActive && !isPaused && !isGameOver) {
        float moveDirection = /*ball.areControlsReversed() ? -1.0f :*/ 1.0f;

        if (isBallLaunched && sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            if (moveDirection > 0) {
                pad.moveLeft(deltaTime);
            }
            else {
                pad.moveRight(deltaTime);
            }
        }
        if (isBallLaunched && sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            if (moveDirection > 0) {
                pad.moveRight(deltaTime);
            }
            else {
                pad.moveLeft(deltaTime);
            }
        }

        if (!isBallLaunched) {
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                float directionX;
                float directionY = -1.0f; 
                                
                do {
                    directionX = (static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX)) * 0.8f - 0.4f;
                } while (std::abs(directionX) < 0.2f || std::abs(directionX) > 0.4f);

                directionY = -std::sqrt(1 - directionX * directionX);

                ball.setDirection(directionX, directionY);
                isBallLaunched = true;
            }
        }
        else {
                        for (auto& ball : activeBalls) {
                ball.move(deltaTime, padShape, bricks, pad);
            }

            checkLife();
            checkVictoryCondition();
        }

        padShape.setPosition(pad.getPosition().first, pad.getPosition().second);

        for (size_t i = 0; i < bricks.size(); ++i) {
            if (bricks[i].isBroken()) {
                int randomEffectIndex = rand() % 22;
                applyEffect(randomEffectIndex);
                hud.updateScore(10);
                bricks.erase(bricks.begin() + i);
                break;
            }
        }
        for (auto& effect : activeBallEffects) {
            effect->update(deltaTime);
        }

        activeBallEffects.erase(
            std::remove_if(
                activeBallEffects.begin(),
                activeBallEffects.end(),
                [](const std::unique_ptr<BallEffect>& effect) {
                    return !effect->isEffectActive();
                }
            ),
            activeBallEffects.end()
        );

    }
}

void Game::checkVictoryCondition() {
    bool allBroken = true;
    for (Brick& brick : bricks) {
        if (!brick.isBroken()) {
            allBroken = false;
            break;
        }
    }

    if (allBroken) {
        isVictory = true;
        isMainMenuActive = true;
        std::cout << "You win!" << std::endl;
    }
}

void Game::applyEffect(int effectIndex) {
    std::unique_ptr<BallEffect> newEffect;
    int duration = BallEffect::getEffectDuration();

    for (const auto& effect : activeBallEffects) {
        if (effect->getType() == static_cast<BallEffectType>(effectIndex)) {
            effect->resetDuration();             return;
        }
    }

    switch (effectIndex) {
    case 0:         newEffect = std::make_unique<BallSpeedBoost>(ball, activeBalls, duration);
        break;
    case 1:         newEffect = std::make_unique<BallSpeedNerf>(ball, activeBalls, duration);
        break;
    case 2:         newEffect = std::make_unique<BallSizeBoost>(ball, activeBalls, duration);
        break;
    case 3:         newEffect = std::make_unique<BallSizeNerf>(ball, activeBalls, duration);
        break;
    case 4:         newEffect = std::make_unique<BallPiercing>(ball, activeBalls, duration);
        break;
    case 5:         newEffect = std::make_unique<BallRandomDirection>(ball, activeBalls);
        break;
    case 6:         newEffect = std::make_unique<BallMultiplier>(ball, activeBalls, duration, 2);
        break;
    case 7:         newEffect = std::make_unique<BallReverse>(ball, activeBalls, duration);
        break;
    case 8:         newEffect = std::make_unique<BallTeleport>(ball, activeBalls);
        break;
    case 9:         newEffect = std::make_unique<BallChaos>(ball, activeBalls, padShape, duration);
        break;
    case 10:         newEffect = std::make_unique<BallInvisible>(ball, activeBalls, duration);
        break;
    case 11:         newEffect = std::make_unique<BallSplit>(ball, activeBalls, duration);
        break;
    /*case 12:         newEffect = std::make_unique<BallExplosive>(ball, bricks, duration);
        break;
    case 13:         newEffect = std::make_unique<BallPathPredictor>(ball, window, duration);
        break;*/
    default:
        return;
    }

    bool alreadyActive = false;
    for (const auto& effect : activeBallEffects) {
        if (typeid(*effect) == typeid(*newEffect)) {
            alreadyActive = true;
            effect->resetDuration();
            break;
        }
    }

    if (newEffect) {
        newEffect->applyEffect(); 
        if (newEffect->isEffectActive()) { 
            activeBallEffects.push_back(std::move(newEffect));
        }
    }
}

void Game::render() {
    window.clear();

    hud.draw(window, isMainMenuActive);

    if (!isMainMenuActive && !isPaused && !isGameOver) {

        for (auto& heart : hearts) {
            window.draw(heart);
        }
        window.draw(padShape);
        for (auto& ball : activeBalls) {
            window.draw(ball.getShape());
        }
        for (Brick& brick : bricks) {
            if (!brick.isBroken()) {
                window.draw(brick.getShape());
            }
        }
                                                    }

    window.display();
}