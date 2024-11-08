#include "OptionsMenu.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Utils.h"


OptionsMenu::OptionsMenu(sf::RenderWindow& window) : window(window),volume(50.0f), resolutionWidth(1920), resolutionHeight(1080), isHighResolution(true) {
    if (!font.loadFromFile("timesnewarial.ttf")) {
        std::cerr << "Erreur : impossible de charger la police." << std::endl;
    }

    if (!clickSoundBuffer.loadFromFile("clic.ogg")) {
        std::cerr << "Erreur : impossible de charger le son du clic." << std::endl;
    }
    clickSound.setBuffer(clickSoundBuffer);

    if (music.loadFromFile("medievale.ogg")) {  // Remplace le chemin par le fichier de musique correct
        music.play();
        music.setVolume(volume);  // Appliquer le volume initial
    }

    volumeOption.setString("Volume: " + std::to_string(static_cast<int>(volume)));
    volumeOption.setFont(font);
    volumeOption.setCharacterSize(50);
    volumeOption.setFillColor(sf::Color::White);
    volumeOption.setPosition(200, 200);
    menuItems.push_back(volumeOption);

    sf::Text resolutionOption("Resolution: " + std::to_string(resolutionWidth) + "x" + std::to_string(resolutionHeight), font, 100);
    resolutionOption.setFillColor(sf::Color::White);
    resolutionOption.setPosition(200, 400);
    menuItems.push_back(resolutionOption);

    volumeBar.setSize(sf::Vector2f(300, 20)); // Taille de la barre
    volumeBar.setFillColor(sf::Color::Green);
    volumeBar.setPosition(200, 300);

    // Curseur de volume
    volumeSlider.setRadius(10); // Taille du curseur
    volumeSlider.setFillColor(sf::Color::Blue);
    volumeSlider.setPosition(200 + volume * 3, 295);

    sf::Text backOption("Back", font, 100);
    backOption.setFillColor(sf::Color::Yellow);
    backOption.setPosition(200, 600);
    menuItems.push_back(backOption);

    selectedItemIndex = 0;
}

void OptionsMenu::display(sf::RenderWindow& window) {
   

    for (const auto& item : menuItems) {
        window.draw(item);
    }
    window.draw(volumeBar);    // Dessiner la barre de volume
    window.draw(volumeSlider);
    window.draw(volumeOption);
}

void OptionsMenu::moveUp() {
    if (selectedItemIndex - 1 >= 0) {
        menuItems[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex--;
        menuItems[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

void OptionsMenu::moveDown() {
    if (selectedItemIndex + 1 < menuItems.size()) {
        menuItems[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex++;
        menuItems[selectedItemIndex].setFillColor(sf::Color::Red);
    }
}

int OptionsMenu::getSelectedItemIndex() {
    return selectedItemIndex;
}

void OptionsMenu::selectItemByMouse(sf::Vector2f& mousePos) {
    for (size_t i = 0; i < menuItems.size(); ++i) {
        sf::FloatRect itemBounds = menuItems[i].getGlobalBounds();
        if (itemBounds.contains(mousePos)) {
            if (selectedItemIndex != i) {
                menuItems[selectedItemIndex].setFillColor(sf::Color::White);
                menuItems[i].setFillColor(sf::Color::Red);
                selectedItemIndex = i;
            }
            break;
        }
    }
}

void OptionsMenu::applySettings() {
    // Applique les paramètres sélectionnés
    if (selectedItemIndex == 0) {
        // Si "Volume" est sélectionné, ajuster le volume
        std::cout << "Nouveau volume : " << volume << "%" << std::endl;
        music.setVolume(volume);
        volumeOption.setString("Volume: " + std::to_string(static_cast<int>(volume)));
        // Ici, tu peux ajuster le volume dans ton jeu avec un objet `sf::Music` ou `sf::Sound`
        // Exemple : music.setVolume(volume);
    }
    else if (selectedItemIndex == 1) {
        // Si "Résolution" est sélectionnée, modifier la résolution
        std::cout << "Nouvelle résolution : " << resolutionWidth << "x" << resolutionHeight << std::endl;
        // Exemple : window.create(sf::VideoMode(resolutionWidth, resolutionHeight), "Jeu");
        window.create(sf::VideoMode(resolutionWidth, resolutionHeight), "Jeu", sf::Style::Fullscreen);
        menuItems[1].setString("Resolution: " + std::to_string(resolutionWidth) + "x" + std::to_string(resolutionHeight));
    }
    else if (selectedItemIndex == 2) {
        // Si "Retour" est sélectionné, revenir au menu précédent
        std::cout << "Retour au menu principal" << std::endl;
    }
}

void OptionsMenu::reset() {
    // Réinitialiser les paramètres aux valeurs par défaut
    volume = 50.0f;
    resolutionWidth = 1920;
    resolutionHeight = 1080;
    selectedItemIndex = 0;
}

void OptionsMenu::increaseVolume() {
    if (volume < 100.0f) {
        volume += 10.0f;
        volumeSlider.setPosition(volumeBar.getPosition().x + volume * 3, volumeSlider.getPosition().y);
        volumeOption.setString("Volume: " + std::to_string(static_cast<int>(volume)));
    }
}

void OptionsMenu::decreaseVolume() {
    if (volume > 0.0f) {
        volume -= 10.0f;
        volumeSlider.setPosition(volumeBar.getPosition().x + volume * 3, volumeSlider.getPosition().y);
        volumeOption.setString("Volume: " + std::to_string(static_cast<int>(volume)));
    }
}

void OptionsMenu::changeResolution(int width,int height) {
    if (isHighResolution) {
        if (window.getSize() != sf::Vector2u(1920, 1080)) {
            window.create(sf::VideoMode(1920, 1080), "Nom du jeu", sf::Style::Default);
            isHighResolution = false;
        }
    }
    else {
        if (window.getSize() != sf::Vector2u(2560, 1440)) {
            window.create(sf::VideoMode(2560, 1440), "Nom du jeu", sf::Style::Default);
            isHighResolution = true;
        }
    }
  
}

// Exemple de méthode dans OptionsMenu pour réadapter les éléments du menu
void OptionsMenu::adjustForResolution(const sf::Vector2u& newSize) {
    // Adapte la position, la taille des éléments graphiques ou du menu
    volumeBar.setSize(sf::Vector2f(newSize.x * 0.5f, volumeBar.getSize().y));  // Par exemple, ajuster la largeur de la barre de volume
    volumeSlider.setPosition(volumeBar.getPosition().x + volume * 3, volumeSlider.getPosition().y); // Réajuster le curseur de volume
    // Ajouter d'autres ajustements en fonction des autres éléments du menu
}



void OptionsMenu::updateVolumeSlider(const sf::Vector2f& mousePos) {
    // Vérifie si la souris est sur la barre de volume
    if (volumeBar.getGlobalBounds().contains(mousePos)) {
        // Calculer la position relative de la souris sur la barre de volume
        float newVolume = (mousePos.x - volumeBar.getPosition().x) / volumeBar.getSize().x;

        // Utiliser la fonction clamp pour limiter la valeur de volume entre 0.0 et 1.0
        newVolume = clamp(newVolume, 0.0f, 1.0f);

        // Mettre à jour le volume et le positionner sur la barre
        volume = newVolume * 100.0f;  // Convertir en pourcentage
        setVolume(newVolume * 100.0f);  // Appliquer la mise à jour du volume
        volumeSlider.setPosition(volumeBar.getPosition().x + newVolume * volumeBar.getSize().x, volumeSlider.getPosition().y);
    }
}

sf::RectangleShape& OptionsMenu::getVolumeBar() {
    return volumeBar;
}

void OptionsMenu::setVolume(float newVolume) {
    volume = newVolume;
    volumeOption.setString("Volume: " + std::to_string(static_cast<int>(volume)));
    music.setVolume(volume);
}

