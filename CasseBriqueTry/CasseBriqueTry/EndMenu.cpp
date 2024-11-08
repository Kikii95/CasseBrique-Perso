#include "EndMenu.h"
#include <stdexcept>
#include <iostream>

EndMenu::EndMenu(sf::RenderWindow& window)
    : MainMenu(window), window(window), selectedIndex(0) {

    if (!font.loadFromFile("timesnewarial.ttf")) {
        throw std::runtime_error("Impossible de charger la police !");
    }

    if (!clickSoundBuffer.loadFromFile("clic.ogg")) {  // Remplace "click_sound.wav" par le chemin de ton fichier
        std::cerr << "Erreur : impossible de charger le son du clic." << std::endl;
    }
    clickSound.setBuffer(clickSoundBuffer);  // Lier le son au buffer

    if (!backgroundTexture.loadFromFile("background3.png")) {  // Remplace "background.jpg" par ton fichier image
        throw std::runtime_error("Impossible de charger l'image de fond !");
    }
    backgroundSprite.setTexture(backgroundTexture);

    // Ajuster l'image pour qu'elle couvre toute la fenêtre
    backgroundSprite.setScale(
        static_cast<float>(SCREEN_WIDTH) / backgroundTexture.getSize().x,
        static_cast<float>(SCREEN_HEIGHT) / backgroundTexture.getSize().y
    );


    gameOverText.setFont(font);
    gameOverText.setString("Game Over");
    gameOverText.setCharacterSize(70);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setStyle(sf::Text::Bold);
    gameOverText.setPosition(window.getSize().x / 2.f - gameOverText.getGlobalBounds().width / 2.f, 100.f);

   

    bricksRemainingText.setFont(font);
    bricksRemainingText.setString("Bricks Remaining: 0");
    bricksRemainingText.setCharacterSize(40);
    bricksRemainingText.setFillColor(sf::Color::White);
    bricksRemainingText.setPosition(window.getSize().x / 2.f - bricksRemainingText.getGlobalBounds().width / 2.f, 200.f);

    bonusText.setFont(font);
    bonusText.setString("Bonus Collected: 0");
    bonusText.setCharacterSize(40);
    bonusText.setFillColor(sf::Color::White);
    bonusText.setPosition(window.getSize().x / 2.f - bonusText.getGlobalBounds().width / 2.f, 300.f);

    scoreText.setFont(font);
    scoreText.setString("Final Score: 0");
    scoreText.setCharacterSize(40);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(window.getSize().x / 2.f - scoreText.getGlobalBounds().width / 2.f, 400.f);


    sf::Text retryOption;
    retryOption.setFont(font);
    retryOption.setString("Retry");
    retryOption.setCharacterSize(60);
    retryOption.setFillColor(sf::Color::White);
    retryOption.setPosition(window.getSize().x / 2.f - retryOption.getGlobalBounds().width / 2.f, 600.f);

    sf::Text optionOption;
    optionOption.setFont(font);
    optionOption.setString("Options");
    optionOption.setCharacterSize(60);
    optionOption.setFillColor(sf::Color::White);
    optionOption.setPosition(window.getSize().x / 2.f - optionOption.getGlobalBounds().width / 2.f, 700.f);

    sf::Text quitOption;
    quitOption.setFont(font);
    quitOption.setString("Quit");
    quitOption.setCharacterSize(60);
    quitOption.setFillColor(sf::Color::White);
    quitOption.setPosition(window.getSize().x / 2.f - quitOption.getGlobalBounds().width / 2.f, 800.f);

    // Ajout des options dans le vecteur
    menuItems.push_back(retryOption);
    menuItems.push_back(optionOption);
    menuItems.push_back(quitOption);

    

    if (!clickSoundBuffer.loadFromFile("clic.ogg")) {
        throw std::runtime_error("Impossible de charger le son de clic !");
    }
    clickSound.setBuffer(clickSoundBuffer);

    // Configuration initiale : première option sélectionnée
    menuItems[selectedIndex].setFillColor(sf::Color::Yellow);
}

void EndMenu::display() {
    
    window.draw(backgroundSprite);
    window.draw(gameOverText);
    window.draw(bricksRemainingText);
    window.draw(bonusText);
    window.draw(scoreText);
    window.draw(overlay);

    for (const auto& item : menuItems) {
        window.draw(item);
    }
    
}

bool EndMenu::handleEvent(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up) {
            moveUp();
        }
        else if (event.key.code == sf::Keyboard::Down) {
            moveDown();
        }
        else if (event.key.code == sf::Keyboard::Enter) {
            return true; 
        }
    }
    return false;
}

void EndMenu::moveUp() {
    if (selectedIndex - 1 >= 0) {
        menuItems[selectedIndex].setFillColor(sf::Color::White); // Désélectionner l'option actuelle
        selectedIndex--;
        menuItems[selectedIndex].setFillColor(sf::Color::Yellow); // Sélectionner l'option précédente
    }
}

void EndMenu::moveDown() {
    if (selectedIndex + 1 < menuItems.size()) {
        menuItems[selectedIndex].setFillColor(sf::Color::White); // Désélectionner l'option actuelle
        selectedIndex++;
        menuItems[selectedIndex].setFillColor(sf::Color::Yellow); // Sélectionner l'option suivante
    }
}

int EndMenu::getSelectedItemIndex() const {
    return selectedIndex; // Retourne l'index de l'option actuellement sélectionnée
}

void EndMenu::selectItemByMouse(sf::Vector2f& mousepos) {
    for (size_t i = 0; i < menuItems.size(); ++i) {
        sf::FloatRect itemBounds = menuItems[i].getGlobalBounds();
        if (itemBounds.contains(mousepos)) {
            if (selectedIndex != i) {
                menuItems[selectedIndex].setFillColor(sf::Color::White);
                menuItems[i].setFillColor(sf::Color::Yellow);
                selectedIndex = i;
            }
            break;
        }
    }
}

void EndMenu::playClickSound() {
    clickSound.play();
}
