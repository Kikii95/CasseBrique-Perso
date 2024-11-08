#pragma once
#include <SFML/Audio.hpp>
#include <string>

class Music {
public:
    Music();
    ~Music();

    bool loadFromFile(const std::string& filename);
    void play();
    void stop();
    void setLoop(bool loop);
    void setVolume(float volume);

private:
    sf::Music backgroundMusic;
};
