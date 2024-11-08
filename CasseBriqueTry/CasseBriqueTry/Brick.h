#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Brick {
public:
    Brick(int x, int y, int width, int height);

    void takeHit();                     // Gère les coups reçus par la brique
    bool isBroken() const;              // Vérifie si la brique est complètement cassée
    const sf::RectangleShape& getShape() const;
    static void loadTextures();         // Charge toutes les textures au démarrage

    bool checkCollision(const sf::Shape& other); // Vérifie la collision avec un objet générique
    void destroy();                     // Marque la brique comme cassée

    // Méthodes pour obtenir la position et la taille
    float getPositionX() const;
    float getPositionY() const;
    float getSizeX() const;
    float getSizeY() const;

    bool isDestroyed() const; // Ajoute cette méthode pour vérifier si la brique est complètement détruite




private:
    sf::RectangleShape shape;
    int hitsRemaining; // Nombre de coups restants pour détruire la brique

    static std::vector<sf::Texture> normalTextures;
    static std::vector<sf::Texture> damagedTextures;
};
