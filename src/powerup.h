#ifndef FIRE_FIGHTER_POWERUP_H
#define FIRE_FIGHTER_POWERUP_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include "player.h"

class powerup {
private:
    sf::Texture texture;
    sf::Sprite sprite;
    float speed;
    sf::Vector2f direction;
    bool collected;
    std::mt19937 gen;
    sf::Vector2u resolution;
    settings gameSettings;

public:
    powerup();
    ~powerup();
    void reset();
    void update(const sf::Time& delta, Player* player, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window, Player* player);
    void adjustForResolution(const sf::Vector2u& resolution);
};

#endif //FIRE_FIGHTER_POWERUP_H
