#include "Music.h"
#include <iostream>

Music::Music() {}

Music::~Music() {}

bool Music::loadFromFile(const std::string& filename) {
    if (!backgroundMusic.openFromFile(filename)) {
        std::cerr << "Erreur : Impossible de charger le fichier de musique " << filename << std::endl;
        return false;
    }
    return true;
}

void Music::play() {
    backgroundMusic.play();
}

void Music::stop() {
    backgroundMusic.stop();
}

void Music::setLoop(bool loop) {
    backgroundMusic.setLoop(loop);
}

void Music::setVolume(float volume) {
    backgroundMusic.setVolume(volume);
}
