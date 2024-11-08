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
#include "GameOver.h"
#include <cstdlib>  
#include <ctime>   
#include "LevelManager.h"
#include <memory>
#include "PadEffect.h"
#include "BallEffect.h"
#include <functional>
#include "Music.h"
#include "LevelManager.h"
#include "BallSpeedBoost.h"
#include "PadSpeedBoost.h"
#include "OptionsMenu.h"


#define SCREEN_WIDTH 2560
#define SCREEN_HEIGHT 1440

class Game {
public:
    Game();
    void run();
    void restartGame();
    void applyEffect(int effectIndex);
    std::vector<std::unique_ptr<BallEffect>> activeBallEffects;
    bool isGameOver;
    sf::RenderWindow window;
    bool isMainMenuActive;
    bool isPaused;
    bool isOptionsMenuActive;
    

protected: 
    
    HUD hud;
    Pad pad;
    Ball ball;
    std::vector<Brick> bricks;
    int score = 0; 
    int bonusCount = 0; 
    std::vector<sf::Sprite> hearts; 
    sf::Texture heartTexture; 
    sf::Texture heartLostTexture; 
    
   
    


private:
    void processEvents();
    void resetBall();
    void loadBrickTexture();
    void initializeLevelManager();
    void initializeMusic();
    void update(float deltaTime);
    void render();

    void updateLevelEditor();
    void saveLevel();
    int getNextLevelNumber() ;
    int lives = 3;
    bool isBallLaunched = false;
    bool isLevelEditorActive = false;
    sf::RectangleShape padShape;
    sf::Clock clock;
    Music music;
    sf::Event event;
    LevelManager levelManager;
    EndMenu endMenu;
    OptionsMenu* optionsMenu;
    bool isVolumeChanged;
    bool isResolutionChanged;
    float volume; // Volume initial
    int resolutionWidth;
    int resolutionHeight;
};
