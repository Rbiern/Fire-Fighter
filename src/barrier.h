#ifndef FIRE_FIGHTER_BARRIER_H
#define FIRE_FIGHTER_BARRIER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "bullet.h"
#include "settings.h"

class Barrier {
private:
    settings gameSettings;
    sf::Texture iceBlockTexture;
    sf::Sprite iceBlockSprite;
    float size;
    sf::SoundBuffer shrinkBuffer;
    sf::Sound shrinkSound;

public:
    explicit Barrier(settings gameSettings);
    virtual ~Barrier();
    void setPosition(int posX, int posY);
    bool bulletCollision(const sf::Sprite& bulletSprite) const;
    void shrink();
    void reset();
    void draw(sf::RenderWindow& window);
};

#endif //FIRE_FIGHTER_BARRIER_H
