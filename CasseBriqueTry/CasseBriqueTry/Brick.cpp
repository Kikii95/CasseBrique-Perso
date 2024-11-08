#include "Brick.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

// Initialisation des textures statiques
std::vector<sf::Texture> Brick::normalTextures;
std::vector<sf::Texture> Brick::damagedTextures;

Brick::Brick(int x, int y, int width, int height)
    : hitsRemaining(2) // Chaque brique nécessite 2 coups pour être cassée
{
    shape.setSize(sf::Vector2f(width, height));
    shape.setPosition(x, y);

    // Sélection aléatoire d'une texture parmi les textures normales
    int textureIndex = rand() % 10;
    shape.setTexture(&normalTextures[textureIndex]);
}

// Charge les textures des briques (normales et endommagées)
void Brick::loadTextures() {
    normalTextures.clear();
    damagedTextures.clear();

    for (int i = 1; i <= 10; ++i) {  // Charge les dix textures disponibles
        std::string indexStr = (i < 10) ? "0" + std::to_string(i) : std::to_string(i);

        sf::Texture texture;
        if (!texture.loadFromFile(indexStr + "-Breakout-Tiles.png")) {
            std::cerr << "Erreur de chargement de la texture " << indexStr << "-Breakout-Tiles.png" << std::endl;
        }
        normalTextures.push_back(texture);

        sf::Texture damagedTexture;
        if (!damagedTexture.loadFromFile(indexStr + "B-Breakout-Tiles.png")) {
            std::cerr << "Erreur de chargement de la texture " << indexStr << "B-Breakout-Tiles.png" << std::endl;
        }
        damagedTextures.push_back(damagedTexture);
    }
}

// Fonction pour gérer les coups reçus par la brique
void Brick::takeHit() {
    hitsRemaining--;

    if (hitsRemaining == 1) {
        // Passe à la texture endommagée après le premier coup
        int textureIndex = -1;
        for (size_t i = 0; i < normalTextures.size(); ++i) {
            if (&normalTextures[i] == shape.getTexture()) { // Compare les adresses des textures
                textureIndex = i;
                break;
            }
        }
        if (textureIndex != -1) {
            shape.setTexture(&damagedTextures[textureIndex]);
        }
    }
}

bool Brick::isBroken() const {
    return hitsRemaining <= 0;
}

const sf::RectangleShape& Brick::getShape() const {
    return shape;
}

bool Brick::isDestroyed() const {
    return hitsRemaining <= 0;
}


// Méthodes pour obtenir la position et la taille de la brique
float Brick::getPositionX() const {
    return shape.getPosition().x;
}

float Brick::getPositionY() const {
    return shape.getPosition().y;
}

float Brick::getSizeX() const {
    return shape.getSize().x;
}

float Brick::getSizeY() const {
    return shape.getSize().y;
}

// Vérifie la collision entre la brique et un autre objet
bool Brick::checkCollision(const sf::Shape& other) {
    return shape.getGlobalBounds().intersects(other.getGlobalBounds());
}
// Marque la brique comme cassée
void Brick::destroy() {
    hitsRemaining = 0; // Marque la brique comme cassée
}
