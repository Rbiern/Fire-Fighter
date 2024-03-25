#ifndef FIRE_FIGHTER_BARRIER_H
#define FIRE_FIGHTER_BARRIER_H

#include "entity.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class Barrier : public Entity {
private:
    float size;
    float initialSize;
    float xPosition;
    float yPosition;

public:
    // Constructor
    Barrier(float startX, float startY);
    bool enemyCollision(const sf::Sprite& enemySprite) const;
    bool bulletCollision(const sf::Sprite& bulletSprite) const;
    void shrink();
    void reset();
    void spawn(float newX, float newY);
    void draw(sf::RenderWindow& window);

    sf::Vector2f getSize() const;
    sf::Vector2f getPosition() const;

    virtual ~Barrier();
};

#endif //FIRE_FIGHTER_BARRIER_H
