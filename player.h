//
// Created by Pc MSI on 2024-03-09.
//

#ifndef FIRE_FIGHTER_PLAYER_H
#define FIRE_FIGHTER_PLAYER_H

#include <SFML/Graphics.hpp>
#include "entity.h"

class Player : public Entity {
private:
    float movementSpeed;

public:
    Player(float startX, float startY);

    void move(const sf::Vector2f& direction);
    void draw(sf::RenderWindow& window);

    void setSpeed(float speed);
    float getSpeed() const;

    sf::Vector2f getSize() const;
    sf::Vector2f getPosition() const;
};


#endif //FIRE_FIGHTER_PLAYER_H
