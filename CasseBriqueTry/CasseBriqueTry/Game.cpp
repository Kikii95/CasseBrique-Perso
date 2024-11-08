#include "Game.h"

#include <memory>

#include "FileUtils.h"  
#include <fstream>
#include <iostream>
#include "BallEffectList.h"
#include "json.hpp"
#include <filesystem>
#include "BackgroundShader.h"

using json = nlohmann::json;


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


    if (!pad.loadTexture("50-Breakout-Tiles.png")) {
        std::cerr << "Erreur : Impossible de charger la texture du pad." << std::endl;
    }

    // Charger le shader depuis le fichier
    if (!backgroundShader.loadFromMemory(fragmentShaderCode, sf::Shader::Fragment)) {
        std::cerr << "Erreur : impossible de charger le shader d'arrière-plan depuis la mémoire" << std::endl;
    }
    else {
        std::cout << "Shader chargé avec succès depuis la mémoire" << std::endl;
    }


    initializeMusic();
    loadBrickTexture();

    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    padShape.setFillColor(sf::Color::Blue);
    Brick::loadTextures(); // Charger toutes les textures de briques une fois au démarrage
    createInitialBricks();
}

void Game::createInitialBricks() {
    int rows = 3;   // Nombre de lignes de briques
    int cols = 16;  // Nombre de colonnes de briques pour ajuster la largeur de l'écran
    int startX = 0; // Position de départ en X
    int startY = 50; // Position de départ en Y

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int xPos = startX + j * 120; // Largeur de chaque brique
            int yPos = startY + i * 40;  // Hauteur de chaque brique
            Brick newBrick(xPos, yPos, 120, 40);
            bricks.push_back(newBrick);
        }
    }
}


void Game::loadBricksFromJson() {
    std::ifstream file("level_3.json");
    if (!file.is_open()) {
        std::cerr << "Erreur : impossible de charger le fichier JSON level_3.json" << std::endl;
        return;
    }

    json levelData;
    file >> levelData;

    for (const auto& brickData : levelData["bricks"]) {
        int posX = brickData["positionX"];
        int posY = brickData["positionY"];
        int width = brickData["sizeX"];
        int height = brickData["sizeY"];

        // Création de la brique avec les données du fichier JSON
        bricks.emplace_back(posX, posY, width, height);

        // Affichage de débogage pour chaque brique
        std::cout << "Brique chargée : Position (" << posX << ", " << posY
            << "), Taille (" << width << ", " << height << ")" << std::endl;
    }

    std::cout << "Toutes les briques ont été chargées depuis level_3.json" << std::endl;
}


void Game::run() {
    while (window.isOpen()) {
        processEvents();
        float deltaTime = clock.restart().asSeconds();

        if (isLevelEditorActive) {  // Quand l'éditeur est actif
            window.clear();
            levelGenerator.drawGrid(window);  // Affiche le quadrillage
            window.display();
        }
        else if (!isMainMenuActive && !isPaused && !isGameOver) {
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

        if (isGameOver) {
            if (gameOverScreen.handleEvent(event)) {
                isGameOver = false;
            }
        }
        else if (isMainMenuActive) {
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
                        // "Démarrer le jeu" => Mode éditeur de niveau vide
                        isMainMenuActive = false;
                        isGameActive = true;  // Utiliser isGameActive pour l'affichage
                    }
                    else if (selectedOption == 2) {
                        // "Level Generator" => Mode éditeur complet avec ajout de briques
                        isMainMenuActive = false;
                        isLevelEditorActive = true;
                    }
                    else if (selectedOption == 3) {
                        window.close();
                    }
                }
            }
        }
        else if (isLevelEditorActive) {  // Mode éditeur de niveau
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    levelGenerator.handleMouseClick(mousePos); // Place une brique
                }
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::S) {
                    levelGenerator.saveLevel(); // Sauvegarde le niveau en JSON
                }
                else if (event.key.code == sf::Keyboard::Escape) {
                    isLevelEditorActive = false;
                    isMainMenuActive = true;  // Retour au menu principal
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
                    if (selectedOption == 0) {
                        isPaused = false;
                    }
                    else if (selectedOption == 1) {
                        LevelType currentLevel = levelManager.getCurrentLevel();
                        levelManager.initializeLevel(currentLevel, pad, ball, bricks);

                        lives = 3;
                        for (size_t i = 0; i < hearts.size(); ++i) {
                            hearts[i].setTexture(heartTexture);
                        }

                        isBallLaunched = false;
                        isPaused = false;
                    }
                    else if (selectedOption == 3) {
                        isMainMenuActive = true;
                        isPaused = false;
                    }
                }
            }
        }


void Game::updateLevelEditor() {
    levelGenerator.drawGrid(window);
}

void Game::render() {
    window.clear();


    if (isLevelEditorActive) {
        // Mode éditeur : affiche un fond noir sans appliquer de shader
        window.clear(sf::Color::Black);
        levelGenerator.drawGrid(window);  // Affiche le quadrillage
    }else{
    // Met à jour le temps pour le shader
    // Met à jour `iTime` à chaque frame
    backgroundShader.setUniform("iTime", clock.getElapsedTime().asSeconds());
    //std::cout << "Temps passé : " << clock.getElapsedTime().asSeconds() << std::endl;
    sf::Vector2f resolution(window.getSize());
    backgroundShader.setUniform("iResolution", sf::Glsl::Vec2(1920.0f, 1080.0f));

    sf::RectangleShape background(sf::Vector2f(resolution.x, resolution.y));
    background.setPosition(0, 0);
    window.draw(background, &backgroundShader);


    // Affichage des autres éléments de l'interface
    if (isMainMenuActive) {
        hud.draw(window, isMainMenuActive);
    }
    else if (isGameActive) {
        hud.draw(window, isMainMenuActive);
        for (auto& heart : hearts) {
            window.draw(heart);
        }
        window.draw(ball.getShape());
        window.draw(pad.getShape());
        for (auto& ball : activeBalls) {
            window.draw(ball.getShape());
        }
        for (Brick& brick : bricks) {
            if (!brick.isBroken()) {
                window.draw(brick.getShape());
            }
        }
    }
    else if (isGameOver) {
        gameOverScreen.display();
    }

    window.display();
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



void Game::initializeLevelManager() {
    if (!levelManager.selectLevel(window, LevelType::LEVEL_1)) {
        std::cerr << "Erreur lors de la sélection du niveau" << std::endl;
        window.close();
        return;
    }

    levelManager.initializeLevel(levelManager.getCurrentLevel(), pad, ball, bricks);
}

void Game::resetBall() {
    ball.setPosition(pad.getPosition().first + pad.getSize().first / 2, pad.getPosition().second - ball.getSize() / 2);
    ball.getShape().setPosition(ball.getPosition().first, ball.getPosition().second);
    ball.setSpeed(400);

    float directionX;
    do {
        directionX = (static_cast<float>(std::rand()) / RAND_MAX) * 0.8f - 0.4f;
    } while (std::abs(directionX) < 0.1f);

    ball.setDirection(directionX, -1.0f);
    isBallLaunched = false;
}

void Game::saveLevel() {
    int levelNumber = getNextLevelNumber();
    std::string fileName = "level_" + std::to_string(levelNumber) + ".lvl";
    std::ofstream levelFile(fileName);

    if (levelFile.is_open()) {
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
        }
        }

void Game::loadBrickTexture() {
   /* if (!Brick::brickTexture.loadFromFile("path_to_your_brick_texture.png")) {
        std::cerr << "Erreur : Impossible de charger la texture des briques" << std::endl;
    }*/
}

int Game::getNextLevelNumber() {
    int level = 1;
    std::string filename;

    // Boucle pour trouver le prochain numéro de fichier disponible
    do {
        filename = "level_" + std::to_string(level) + ".json";
        std::ifstream file(filename);
        if (!file) {
            break; // Si le fichier n'existe pas, on a trouvé le prochain numéro disponible
        }
        level++;
    } while (true);

    return level;
}

void Game::applyEffect(int effectIndex) {
    std::unique_ptr<BallEffect> newEffect;

    switch (effectIndex) {
    case 0:
        newEffect = std::make_unique<BallSpeedBoost>(ball, 5000);
        ball.getShape().setFillColor(sf::Color::Red);
        break;
    case 1:
        newEffect = std::make_unique<BallSpeedNerf>(ball, 5000);
        ball.getShape().setFillColor(sf::Color::Blue);
        break;
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


