#include "PauseMenu.h"
#include <iostream>

PauseMenu::PauseMenu(sf::RenderWindow& window) :  window(window) {
    overlay.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
    overlay.setFillColor(sf::Color(0, 0, 0, 150));

    if (!font.loadFromFile("timesnewarial.ttf")) {
        std::cerr << "Erreur : impossible de charger la police." << std::endl;
    }

    if (!clickSoundBuffer.loadFromFile("clic.ogg")) {  // Remplace "click_sound.wav" par le chemin de ton fichier
        std::cerr << "Erreur : impossible de charger le son du clic." << std::endl;
    }
    clickSound.setBuffer(clickSoundBuffer);  // Lier le son au buffer

    if (!backgroundTexture.loadFromFile("background2.png")) {  // Remplace "background.jpg" par ton fichier image
        throw std::runtime_error("Impossible de charger l'image de fond !");
    }
    backgroundSprite.setTexture(backgroundTexture);

    // Ajuster l'image pour qu'elle couvre toute la fenêtre
    backgroundSprite.setScale(
        static_cast<float>(SCREEN_WIDTH) / backgroundTexture.getSize().x,
        static_cast<float>(SCREEN_HEIGHT) / backgroundTexture.getSize().y
    );

    PauseText.setFont(font);
    PauseText.setString("Game Pause");
    PauseText.setCharacterSize(150);
    PauseText.setFillColor(sf::Color::Red);


    sf::FloatRect PauseMenuBounds = PauseText.getLocalBounds();
    PauseText.setOrigin(PauseMenuBounds.width / 2, PauseMenuBounds.height / 2);
    PauseText.setPosition(SCREEN_WIDTH / 2, 200);

    std::vector<std::string> menuLabels = { "Continuer", "Options", "Quitter" };
    for (int i = 0; i < menuLabels.size(); ++i) {
        sf::Text button;
        button.setFont(font);
        button.setString(menuLabels[i]);
        button.setCharacterSize(100);
        button.setFillColor(i == 0 ? sf::Color::Red : sf::Color::White);

        sf::FloatRect bounds = button.getLocalBounds();
        button.setOrigin(bounds.width / 2, bounds.height / 2);
        button.setPosition(SCREEN_WIDTH / 2, 500 + i * 200);

        menuItem.push_back(button);
    }

    selectedItemIndex = 0;

}

void PauseMenu::display(sf::RenderWindow& window) {
    window.draw(backgroundSprite);
    window.draw(overlay);
    window.draw(PauseText);
    for (const auto& item : menuItem) {
        window.draw(item);
    }
}


bool PauseMenu::handleEvent(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            return true;
        }
        else if (event.key.code == sf::Keyboard::Up) {
            moveUp();
        }
        else if (event.key.code == sf::Keyboard::Down) {
            moveDown();
        }
        else if (event.key.code == sf::Keyboard::Enter) {

            if (selectedItemIndex == 0) {
                return true;
            }
            else if (selectedItemIndex == 1) {

            }
            else if (selectedItemIndex == 2) {
                window.close();
            }
        }
    }
    return false;
}

void PauseMenu::moveUp() {
    if (selectedItemIndex - 1 >= 0) {
        menuItem[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        menuItem[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

void PauseMenu::moveDown() {
    if (selectedItemIndex + 1 < menuItem.size()) {
        menuItem[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        menuItem[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

void PauseMenu::selectItemByMouse(sf::Vector2f& mousepos)
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

void PauseMenu::playClickSound() {
    clickSound.play();  // Joue le son du clic
}

sf::Sound& PauseMenu::getClickSound() {
    return clickSound;  // Renvoie le son du clic
}