#ifndef FIRE_FIGHTER_ENTITY_H
#define FIRE_FIGHTER_ENTITY_H

#include <SFML/Graphics.hpp>

class entity {
private:
    sf::Clock shootCooldown;
    float movementSpeed = 0.5f;
    bool canShoot = true;
    sf::RectangleShape character;
public:
    entity();
    sf::RectangleShape getEntity();
    float getSpeed();
};


#endif //FIRE_FIGHTER_ENTITY_H
