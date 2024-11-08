#include "GameOver.h"
#include <iostream>

GameOver::GameOver(sf::RenderWindow& window) : MainMenu(window), window(window) {
    overlay.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
    overlay.setFillColor(sf::Color(0, 0, 0, 150));

    if (!font.loadFromFile("timesnewarial.ttf")) {
        std::cerr << "Erreur : impossible de charger la police." << std::endl;
    }

    gameOverText.setFont(font);
    gameOverText.setString("GAME OVER");
    gameOverText.setCharacterSize(100);
    gameOverText.setFillColor(sf::Color::Red);

    // Centrer horizontalement
    sf::FloatRect gameOverBounds = gameOverText.getLocalBounds();
    gameOverText.setOrigin(gameOverBounds.width / 2, gameOverBounds.height / 2);
    gameOverText.setPosition(SCREEN_WIDTH / 2, 100);

    bricksRemainingText.setFont(font);
    bricksRemainingText.setString("Bricks remaining: 0"); // Exemple de texte
    bricksRemainingText.setCharacterSize(50);
    bricksRemainingText.setFillColor(sf::Color::White);

    sf::FloatRect bricksBounds = bricksRemainingText.getLocalBounds();
    bricksRemainingText.setOrigin(bricksBounds.width / 2, bricksBounds.height / 2);
    bricksRemainingText.setPosition(SCREEN_WIDTH / 2, 250);

    bonusText.setFont(font);
    bonusText.setString("Bonuses collected: 0"); // Exemple de texte
    bonusText.setCharacterSize(50);
    bonusText.setFillColor(sf::Color::White);

    sf::FloatRect bonusBounds = bonusText.getLocalBounds();
    bonusText.setOrigin(bonusBounds.width / 2, bonusBounds.height / 2);
    bonusText.setPosition(SCREEN_WIDTH / 2, 350);

    scoreText.setFont(font);
    scoreText.setString("Total score: 0"); // Exemple de texte
    scoreText.setCharacterSize(50);
    scoreText.setFillColor(sf::Color::White);

    sf::FloatRect scoreBounds = scoreText.getLocalBounds();
    scoreText.setOrigin(scoreBounds.width / 2, scoreBounds.height / 2);
    scoreText.setPosition(SCREEN_WIDTH / 2, 450);
}

void GameOver::display() {
    window.draw(overlay);
    window.draw(gameOverText);
    window.draw(bricksRemainingText);
    window.draw(bonusText);
    window.draw(scoreText);
}


bool GameOver::handleEvent(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            // Logique pour g�rer l'appui sur Escape (retour au menu principal)
            return true; // Retourne true pour indiquer un �v�nement trait�
        }
    }
    return false; // Aucun �v�nement pertinent trait�
}
