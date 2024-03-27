#ifndef FIRE_FIGHTER_BARRIER_H
#define FIRE_FIGHTER_BARRIER_H

#include "entity.h"
#include "enemy.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class Barrier : public Entity {
private:
    float size;
    float xPosition;
    float yPosition;

public:
    Barrier(float startX, float startY, const sf::Vector2u& resolution);

    bool enemyCollision(const Enemy& enemy) const;

    void shrink();
    void reset(const sf::Vector2u& resolution);
    void spawn(float newX, float newY);
    void draw(sf::RenderWindow& window);
    void adjustForResolution(const sf::Vector2u& resolution);

    sf::Vector2f getSize() const;
    sf::Vector2f getPosition() const;

    virtual ~Barrier();


};

#endif //FIRE_FIGHTER_BARRIER_H
