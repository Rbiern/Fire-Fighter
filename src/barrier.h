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
    float barrierSpacing;

public:
    Barrier(float startX, float startY, const sf::Vector2u& resolution);

    bool enemyCollision(const Enemy& enemy) const;
    bool bulletCollision(const sf::Sprite& bulletSprite) const;

    void shrink(const sf::Vector2u& resolution);
    void reset(const sf::Vector2u& resolution);
    void spawn(float newX, float newY);
    void draw(sf::RenderWindow& window);
    void adjustForResolution(const sf::Vector2u& resolution);
    float adjustSpacingForResolution(const sf::Vector2u& resolution);

    sf::Vector2f getSize() const;
    sf::Vector2f getPosition() const;

    virtual ~Barrier();


};

//class BarrierWave {
//private:
//    int barrierRows;
//    int barrierColumns;
//    float barrierSpacing;
//public:
//    BarrierWave(sf::RenderWindow& window, const sf::Vector2u& resolution);
//    float adjustSpacingForResolution(const sf::Vector2u& resolution);
//};

#endif //FIRE_FIGHTER_BARRIER_H
