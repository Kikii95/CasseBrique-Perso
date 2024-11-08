#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include "HUD.h"
#include "Pad.h"
#include "Ball.h"
#include "Brick.h"
#include "MainMenu.h"
#include "PauseMenu.h"
#include <cstdlib>  
#include <ctime>   
#include "LevelManager.h"
#include <memory>
#include "PadEffect.h"
#include "BallEffect.h"
#include <functional>
#include "Music.h"
#include "LevelManager.h"



#define SCREEN_WIDTH 3840
#define SCREEN_HEIGHT 2160

class Game {
public:
    Game();
    void run();

    std::vector<std::unique_ptr<BallEffect>> activeBallEffects;
    void applyEffect(int effectIndex);
    bool isVictory = false;

protected: 
    sf::RenderWindow window;
    HUD hud;
    Pad pad;
    Ball ball;
    std::vector<Brick> bricks;
    int score = 0; 
    int bonusCount = 0; 
    std::vector<sf::Sprite> hearts; 
    sf::Texture heartTexture; 
    sf::Texture heartLostTexture; 
    bool isGameOver = false;
    


private:
    void processEvents();
    void resetBall();
    void loadBrickTexture();
    void initializeLevelManager();
    void initializeMusic();
    void update(float deltaTime);
    void checkVictoryCondition();
    void render();

    void updateLevelEditor();
    void saveLevel();
    int getNextLevelNumber() ;

    int lives = 3;
    bool isBallLaunched = false;
    bool isMainMenuActive;
    bool isPaused;
    bool isLevelEditorActive = false;
    sf::RectangleShape padShape;
    sf::Clock clock;
    Music music;
    sf::Event event;
    LevelManager levelManager;
    std::vector<Ball> activeBalls;
    void checkLife();
};
