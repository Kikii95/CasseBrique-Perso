#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <SFML/Audio.hpp>
#include "Music.h"
#include "Hud.h"

class OptionsMenu {
public:
    OptionsMenu(sf::RenderWindow& window);

    void display(sf::RenderWindow& window);
    void moveUp();  // Se déplacer vers le haut dans les options
    void moveDown();  // Se déplacer vers le bas dans les options
    int getSelectedItemIndex();
    void applySettings();
    void selectItemByMouse(sf::Vector2f& mousePos);
    void reset();
    void updateVolumeSlider(const sf::Vector2f& mousePos);
    void increaseVolume();
    void decreaseVolume();
    void changeResolution(int width, int height);
    void adjustForResolution(const sf::Vector2u& newSize);
    sf::Text volumeOption;
    sf::RectangleShape& getVolumeBar();    // Getter pour la barre de volume
    void setVolume(float newVolume);
    

private:
    sf::RenderWindow& window;
    int selectedItemIndex;
    sf::Font font;
    std::vector<sf::Text> menuItems;
    sf::SoundBuffer clickSoundBuffer;
    sf::Sound clickSound;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::RectangleShape volumeBar;  // Barre du volume
    sf::CircleShape volumeSlider;
    bool isHighResolution;
    
    
    
    // Exemple d'options à modifier
    float volume;  // Volume du jeu (par exemple)
    int resolutionWidth, resolutionHeight;
    Music music;


};
