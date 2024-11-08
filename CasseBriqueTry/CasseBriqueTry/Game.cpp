#include "Game.h"
#include "BallSpeedBoost.h"
#include "BallSpeedNerf.h"
#include "PadSpeedBoost.h"
#include <memory>
#include "EndMenu.h"
#include "FileUtils.h"  
#include <fstream>
#include <iostream>
#include <algorithm>
#include "Utils.h"




Game::Game()
    : window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Casse-Brique", sf::Style::Fullscreen),
    hud(SCREEN_WIDTH, SCREEN_HEIGHT, window),
    isGameOver(false),
    pad((0.8 * SCREEN_WIDTH), (0.2 * SCREEN_HEIGHT)),
    ball(pad.getPosition().first + pad.getSize().first / 2, pad.getPosition().second - ball.getSize(), (0.3 * SCREEN_HEIGHT), (0.01 * SCREEN_WIDTH)),
    levelManager(),
    isOptionsMenuActive(false),
    isMainMenuActive(true),
    isPaused(false),
    endMenu(window),
    resolutionWidth(SCREEN_WIDTH),  // Initialisation de la résolution
    resolutionHeight(SCREEN_HEIGHT), // Initialisation de la résolution
    volume(50.0f),
   
    
 
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

    
    loadBrickTexture();

    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    padShape.setFillColor(sf::Color::Blue);
    bricks = Brick::createBricks(5, 10, (0.06 * SCREEN_WIDTH), (0.02 * SCREEN_WIDTH));
}


void Game::restartGame() {
    // Réinitialisation des variables
    isGameOver = false;
    isMainMenuActive = true;
    isPaused = false;
    lives = 3;
    score = 0;
    bonusCount = 0;
    bricks.clear();  
    hearts.clear();  
    activeBallEffects.clear();  
    isBallLaunched = false;

    // Réinitialiser la balle et le pad
    ball.setPosition(pad.getPosition().first + pad.getSize().first / 2, pad.getPosition().second - ball.getSize() / 2);
    ball.setSpeed(400);
    loadBrickTexture();  
    bricks = Brick::createBricks(5, 10, (0.06 * SCREEN_WIDTH), (0.02 * SCREEN_WIDTH)); 

    // Réinitialiser le menu
    hud.getMainMenu().reset();  
    hud.updateScore(score);

    // Réinitialiser la musique
    

    
}


void Game::run() {
    while (window.isOpen()) {
        processEvents();
        float deltaTime = clock.restart().asSeconds();

        if (isLevelEditorActive) {
            //std::cout << "Level Generator mode activated" << std::endl;
            updateLevelEditor();
        }
        else {
            update(deltaTime);
        }

        render();
    }
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



void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (isMainMenuActive) {
            // Gérer les événements du menu principal
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
                        restartGame();
                        isMainMenuActive = false;
                    }
                    else if (selectedOption == 1) {
                        isOptionsMenuActive = true;
                        isMainMenuActive = false;
                    }
                    else if (selectedOption == 3) {
                        window.close();
                    }
                }
            }
            if (event.type == sf::Event::MouseMoved) {
                sf::Vector2f mousepos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                hud.getMainMenu().selectItemByMouse(mousepos);
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousepos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                hud.getMainMenu().selectItemByMouse(mousepos);

                int selectedOption = hud.getMainMenu().getSelectedItemIndex();
                if (selectedOption == 0) {
                    hud.getMainMenu().getClickSound().play();
                    restartGame();
                    isMainMenuActive = false;
                }
                else if (selectedOption == 1) {
                    hud.getMainMenu().getClickSound().play();
                    isOptionsMenuActive = true;
                    isMainMenuActive = false;
                }
                else if (selectedOption == 3) {
                    hud.getMainMenu().getClickSound().play();
                    window.close();
                }
            }
        }
        else if (isOptionsMenuActive) {
            // Gérer le mouvement de la souris et mettre à jour le volume en temps réel
            if (event.type == sf::Event::MouseMoved) {
                sf::Vector2i mousePixelPos = sf::Mouse::getPosition(window);
                sf::Vector2f mousePos = window.mapPixelToCoords(mousePixelPos);

                // Vérifie si la souris est au-dessus de la barre de volume
                if (hud.getOpMenu().getVolumeBar().getGlobalBounds().contains(mousePos)) {
                    // Calculer la position relative de la souris sur la barre de volume
                    float newVolume = (mousePos.x - hud.getOpMenu().getVolumeBar().getPosition().x) / hud.getOpMenu().getVolumeBar().getSize().x;

                    // Limiter la valeur du volume entre 0 et 1
                    clamp(newVolume, 0.0f, 1.0f);

                    // Mettre à jour le volume (en pourcentage)
                    hud.getOpMenu().setVolume(newVolume * 100.0f);  // Convertir en pourcentage (0-100)

                    // Déplacer le curseur de volume à la position appropriée
                    hud.getOpMenu().updateVolumeSlider(mousePos);    // Déplacer le curseur visuellement
                }

                // Sélectionner un élément du menu par la souris
                hud.getOpMenu().selectItemByMouse(mousePos);
            }

            // Gérer le clic de la souris pour d'autres actions si nécessaire
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                hud.getOpMenu().selectItemByMouse(mousePos);

                int selectedOption = hud.getOpMenu().getSelectedItemIndex();
                if (selectedOption == 1) { // Résolution (changer la résolution)
                    if (resolutionWidth == 2560 && resolutionHeight == 1440) {
                        // Change la résolution à 1920x1080
                        hud.getOpMenu().changeResolution(1920, 1080);
                        resolutionWidth = 1920;
                        resolutionHeight = 1080;
                    }
                    else {
                        // Change la résolution à 2560x1440
                        hud.getOpMenu().changeResolution(2560, 1440);
                        resolutionWidth = 2560;
                        resolutionHeight = 1440;
                    }
                }
                else if (selectedOption == 2) { // Revenir au menu principal
                    isOptionsMenuActive = false;
                    isMainMenuActive = true;
                }
            }
        }



        else if (isPaused) {
            // Gérer les événements du menu de pause
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    isPaused = false;  // Quitter le menu de pause
                }
            }
            if (event.type == sf::Event::MouseMoved) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                hud.getPauseMenu().selectItemByMouse(mousePos);
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                hud.getPauseMenu().selectItemByMouse(mousePos);

                int selectedOption = hud.getPauseMenu().getSelectedItemIndex();
                if (selectedOption == 0) { // Reprendre le jeu
                    hud.getPauseMenu().getClickSound().play();
                    isPaused = false;
                }
                else if (selectedOption == 1) { // Retourner au menu principal
                    hud.getPauseMenu().getClickSound().play();
                    isOptionsMenuActive = true;
                    isPaused = false;
                }
                else if (selectedOption == 2) { // Quitter
                    hud.getPauseMenu().getClickSound().play();
                    isMainMenuActive = true;
                    isPaused = false;
                }
            }
        }
        else if (isGameOver) {
            // Gérer les événements du menu de fin
            if (endMenu.handleEvent(event)) {
                int selectedOption = endMenu.getSelectedItemIndex();
                if (selectedOption == 0) { // "Retry"
                    endMenu.playClickSound();
                    restartGame();
                    isMainMenuActive = false;
                }
                else if (selectedOption == 1) { // "Quit"
                    endMenu.playClickSound();
                    isOptionsMenuActive = true;
                    isGameOver = false;
                }
                else if (selectedOption == 2) { // "Quit"
                    endMenu.playClickSound();
                    window.close();
                }
            }
            if (event.type == sf::Event::MouseMoved) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                endMenu.selectItemByMouse(mousePos); // Change la sélection par la souris
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                endMenu.selectItemByMouse(mousePos); // Sélectionner l'élément par souris

                int selectedOption = endMenu.getSelectedItemIndex();
                if (selectedOption == 0) { // "Retry"
                    endMenu.playClickSound();
                    restartGame();
                    isMainMenuActive = false;
                }
                else if (selectedOption == 2) { // "Quit"
                    endMenu.playClickSound();
                    window.close();
                }
            }
        }
        else {
            // Gérer les autres événements (par exemple, Échap pour revenir en pause)
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                isPaused = !isPaused; // Bascule l'état de la pause
            }
        }
    }
}




void Game::initializeMusic() {
    if (music.loadFromFile("medievale.ogg")) {
        music.setLoop(true);
        music.setVolume(volume);
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

    levelManager.initializeLevel(levelManager.getCurrentLevel(), pad, ball, bricks);
    levelManager.renderLevel(window, pad, ball, bricks);
}
void Game::updateLevelEditor() {
    //std::cout << "test update save" << std::endl;
    while (window.pollEvent(event)) {
        //std::cout << "test while events" << std::endl;
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




void Game::update(float deltaTime) {
    if (isGameOver) {
        return;
    }
    if (!isMainMenuActive && !isPaused && !isGameOver && !isOptionsMenuActive) {
        if (isBallLaunched && sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            pad.moveLeft(deltaTime);
        }
        if (isBallLaunched && sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            pad.moveRight(deltaTime);
        }

        if (!isBallLaunched && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            float directionX;
            do {
                directionX = (static_cast<float>(std::rand()) / RAND_MAX) * 0.8f - 0.4f;
            } while (std::abs(directionX) < 0.1f);

            float directionY = -1.0f;

            ball.setDirection(directionX, directionY);
            isBallLaunched = true;
        }

        if (isBallLaunched) {
            ball.move(deltaTime, padShape, bricks);
        }

        if (ball.getPosition().second > SCREEN_HEIGHT) {
            --lives;

            if (lives >= 0 && lives < hearts.size()) {
                hearts[lives].setTexture(heartLostTexture);
            }

            if (lives > 0) {
                resetBall();
            }
            if (lives <= 0) {
                isGameOver = true;
            }
        }

        padShape.setPosition(pad.getPosition().first, pad.getPosition().second);

        for (size_t i = 0; i < bricks.size(); ++i) {
            if (bricks[i].isBroken()) {
                int randomEffectIndex = rand() % 3;
                applyEffect(randomEffectIndex);
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
                []( std::unique_ptr<BallEffect>& effect) { return !effect->isEffectActive(); }
            ),
            activeBallEffects.end()
        );

        bool hasActiveEffect = !activeBallEffects.empty();
        if (!hasActiveEffect) {
            ball.getShape().setFillColor(sf::Color::White);
        }
    }
}


void Game::render() {
    window.clear();
    
    hud.draw(window, isMainMenuActive, isPaused, isGameOver, isOptionsMenuActive);

    if (!isMainMenuActive && !isPaused && !isGameOver && !isOptionsMenuActive) {

        for ( auto& heart : hearts) {
            window.draw(heart);
        }
        window.draw(padShape);
        window.draw(ball.getShape());
        for (Brick& brick : bricks) {
            if (!brick.isBroken()) {
                window.draw(brick.getShape());
            }
        }
    }
    else if (isGameOver) {
        endMenu.display();
    }
  
    window.display();
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
    for ( auto& effect : activeBallEffects) {
        if (typeid(*effect) == typeid(*newEffect)) {
            alreadyActive = true;
            break;
        }
    }

    if (!alreadyActive) {
        newEffect->applyBallEffect();
        activeBallEffects.push_back(std::move(newEffect));
    }
}
