#pragma once
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "Brick.h"

class LevelGenerator {
public:
    LevelGenerator();

    // Méthode pour ajouter une brique au niveau actuel
    void addBrick(int x, int y, int width, int height);

    // Sauvegarder le niveau dans un fichier
    void saveLevel();

    // Charger le prochain numéro de niveau disponible
    int getNextLevelNumber() ;

private:
    std::vector<Brick> bricks;
    int levelNumber;

    // Génère le nom de fichier basé sur le numéro de niveau
    std::string generateLevelFileName(int levelNum) ;
};
