#ifndef FIRE_FIGHTER_ENEMY_H
#define FIRE_FIGHTER_ENEMY_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include "bullet.h"
#include "entity.h"

class Enemy : public Entity {
public:
    Enemy(float startX, float startY, unsigned int screenWidth, const sf::Vector2u& resolution);
    void update(const sf::Time& deltaTime);
    void draw(sf::RenderWindow& window);
    void setTexture(const std::string& texturePath);
    sf::Vector2u getSize() const;
    sf::FloatRect getGlobalBounds() const;
    void kill();
    bool getIsAlive() const;
    static int getTotalDeath();
    void shoot();
    std::vector<Bullet>& getBullets();
    void setIsAlive(bool alive);
    void increaseSpeed(float factor);
    void removeBullet();

private:
    std::vector<Bullet> bullets;
    float movementSpeed;
    unsigned int screenWidth;
    bool isAlive;
    static int totalDeath;
    sf::Vector2u res1;
};

#endif // FIRE_FIGHTER_ENEMY_H
