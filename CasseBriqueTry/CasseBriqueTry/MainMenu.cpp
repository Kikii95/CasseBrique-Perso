#include "MainMenu.h"
#include <SFML/Graphics.hpp>
#include <iostream>

MainMenu::MainMenu(sf::RenderWindow& window) {
    if (!font.loadFromFile("timesnewarial.ttf")) {
        std::cerr << "Erreur : impossible de charger la police." << std::endl;
    }
    
    if (!clickSoundBuffer.loadFromFile("clic.ogg")) {  // Remplace "click_sound.wav" par le chemin de ton fichier
        std::cerr << "Erreur : impossible de charger le son du clic." << std::endl;
    }
    clickSound.setBuffer(clickSoundBuffer);  // Lier le son au buffer
    
    if (!backgroundTexture.loadFromFile("background.png")) {  // Remplace par ton fichier image
        throw std::runtime_error("Impossible de charger l'image de fond !");
    }
    backgroundSprite.setTexture(backgroundTexture);

    // Mettre la taille du sprite à la taille de la fenêtre
    backgroundSprite.setScale(
        window.getSize().x / backgroundTexture.getSize().x,  // Mise à l'échelle en X
        window.getSize().y / backgroundTexture.getSize().y   // Mise à l'échelle en Y
    );

    float scaleX = static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x;
    float scaleY = static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y;

    // On prend le facteur d'échelle le plus grand pour remplir l'écran
    float scaleFactor = std::max(scaleX, scaleY);

    // Appliquer l'échelle en fonction du facteur choisi
    backgroundSprite.setScale(scaleFactor, scaleFactor);

    sf::Text play("Demarrer le jeu", font, 100);
    play.setFillColor(sf::Color::Red);
    play.setPosition(sf::Vector2f(SCREEN_WIDTH / 2 - 350, SCREEN_HEIGHT / 2 - 500));
    menuItem.push_back(play);

    sf::Text option("Option", font, 100);
    option.setFillColor(sf::Color::White);
    option.setPosition(sf::Vector2f(SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2 - 300));
	menuItem.push_back(option);

	sf::Text levelGen("Level Generator", font, 100);
	levelGen.setFillColor(sf::Color::White);
	levelGen.setPosition(sf::Vector2f(SCREEN_WIDTH / 2 - 330, SCREEN_HEIGHT / 2 - 100));
	menuItem.push_back(levelGen);


    sf::Text quit("Quitter", font, 100);
    quit.setFillColor(sf::Color::White);
    quit.setPosition(sf::Vector2f(SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2 + 100 ));
    menuItem.push_back(quit);

    selectedItemIndex = 0;
}



void MainMenu::draw(sf::RenderWindow& window) {
    
    window.draw(backgroundSprite);
    for ( auto& item : menuItem) {
        window.draw(item);
    }
}

void MainMenu::moveUp() {
    if (selectedItemIndex - 1 >= 0) {
        menuItem[selectedItemIndex].setFillColor(sf::Color::White); 
        selectedItemIndex--;
        menuItem[selectedItemIndex].setFillColor(sf::Color::Red); 
    }
}

void MainMenu::moveDown() {
    if (selectedItemIndex + 1 < menuItem.size()) {
        menuItem[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        menuItem[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}


int MainMenu::getSelectedItemIndex()
{
	return selectedItemIndex;
}

void MainMenu::selectItemByMouse( sf::Vector2f& mousepos)
{
    for (size_t i = 0; i < menuItem.size(); ++i) {
        // Récupère les bounds (limites) de chaque texte (ou bouton)
        sf::FloatRect itemBounds = menuItem[i].getGlobalBounds();

        // Vérifie si la souris est dans les limites de ce texte
        if (itemBounds.contains(mousepos)) {
            // Change la couleur de l'élément survolé
            if (selectedItemIndex != i) {
                menuItem[selectedItemIndex].setFillColor(sf::Color::White); // Réinitialise la couleur de l'élément précédemment sélectionné
                menuItem[i].setFillColor(sf::Color::Red);  // Met en surbrillance l'élément survolé
                selectedItemIndex = i; // Met à jour l'élément sélectionné
            }
            break; // On arrête de parcourir les autres éléments une fois que la souris en survole un
        }
    }
}

void MainMenu::reset() {
    selectedItemIndex = 0;  // Réinitialise l'index à "Jouer" par défaut
}

void MainMenu::playClickSound() {
    clickSound.play();  // Joue le son du clic
}

sf::Sound& MainMenu::getClickSound() {
    return clickSound;  // Renvoie le son du clic
}



MainMenu::~MainMenu()
{
}
