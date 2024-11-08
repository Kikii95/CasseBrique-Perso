#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "LevelGenerator.h"
#include "HUD.h"
#include "Pad.h"
#include "Ball.h"
#include "Brick.h"
#include "MainMenu.h"
#include "PauseMenu.h"
#include "GameOver.h"
#include "Music.h"
#include "LevelManager.h"
#include "BallEffect.h"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

class Game {
public:
    Game();
    void run();

private:
    sf::RenderWindow window;
    HUD hud;
    Pad pad;
    Ball ball;
    std::vector<Brick> bricks;
    int lives = 3;
    bool isGameOver = false;
    bool isMainMenuActive = true;
    bool isPaused = false;
    bool isGameActive = false;  // Ajout de la variable pour suivre l'état de jeu
    bool isLevelEditorActive = false;
    bool isBallLaunched = false;
    sf::RectangleShape padShape;
    sf::Clock clock;
    Music music;
    GameOver gameOverScreen;
    LevelManager levelManager;
    sf::RectangleShape background; // Rectangle pour remplir l'écran
    sf::Texture heartTexture;
    sf::Texture heartLostTexture;
    std::vector<sf::Sprite> hearts;


    // Ajout de LevelGenerator pour gérer le quadrillage et le placement des briques
    LevelGenerator levelGenerator;

    // Liste des effets actifs sur la balle
    std::vector<std::unique_ptr<BallEffect>> activeBallEffects;

    sf::Shader backgroundShader; // Shader pour l'arrière-plan
    void createInitialBricks(); // Fonction pour créer des briques initiales
    void processEvents();
    void update(float deltaTime);
    void render();
    void resetBall();
    void applyEffect(int effectIndex);

    // Méthodes supplémentaires
    void initializeMusic();
    void loadBrickTexture();
    void initializeLevelManager();
    void updateLevelEditor();
    void saveLevel();
    int getNextLevelNumber();



    // Méthode pour charger les briques depuis un fichier JSON
    void loadBricksFromJson();
};
