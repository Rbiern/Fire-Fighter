#ifndef FIRE_FIGHTER_POWERUP_H
#define FIRE_FIGHTER_POWERUP_H

#include <SFML/Graphics.hpp>
#include "player.h"

class powerup {
private:
    sf::Texture texture;
    sf::Sprite sprite;
    float speed;
    sf::Vector2f direction;
    bool collected;

public:
    powerup();
    void reset();
    void update(const sf::Time& delta, Player& player);
    void draw(sf::RenderWindow& window, Player& player);
};

#endif //FIRE_FIGHTER_POWERUP_H
