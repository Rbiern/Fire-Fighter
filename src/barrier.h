#ifndef FIRE_FIGHTER_BARRIER_H
#define FIRE_FIGHTER_BARRIER_H

#include "entity.h"
#include "enemy.h"
#include "bullet.h"
#include "settings.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

class Barrier : public Entity {
private:
    float size;
    float barrierX;
    float barrierY;
    float scaleFactor;
    float barrierSpacing;
    float minimumSize;
    const float referenceWidth;
    const float referenceHeight;
    settings gameSettings;
    sf::Vector2u resolution;
    sf::SoundBuffer shrinkBuffer;
    sf::Sound shrinkSound;

public:
    Barrier(float barrierX, float barrierY, sf::RenderWindow& window, settings gameSettings);
    bool bulletCollision(const sf::Sprite& bulletSprite) const;

    void shrink();
    void reset(const sf::Vector2u& resolution);
    void spawn(float newX, float newY);
    void draw(sf::RenderWindow& window);
    float getBarrierSpacing();
    void adjustForResolution(const sf::Vector2u& resolution);
    void adjustSpacingForResolution(const sf::RenderWindow& window, const sf::Vector2u& resolution);

    std::vector<Barrier> barriers;
    sf::Vector2f getSize() const;
    sf::Vector2f getPosition() const;

    virtual ~Barrier();
};

#endif //FIRE_FIGHTER_BARRIER_H
