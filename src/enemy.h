#ifndef FIRE_FIGHTER_ENEMY_H
#define FIRE_FIGHTER_ENEMY_H

#include <vector>
#include <string>
#include <iostream>
#include "bullet.h"
#include "entity.h"
/**
 * @class Enemy
 * @brief Manages the enemy's behavior and state in the game.
 * The Enemy class is responsible for set texture, draw enemy on win
 *
 */
class Enemy : public Entity {
public:
    /**
     * Constructor for an Enemy.
     * Initializes an enemy with a starting position, screen width for boundary checks, and resolution for scaling.
     *
     * @param startX The starting X position of the enemy.
     * @param startY The starting Y position of the enemy.
     * @param screenWidth The width of the screen, used for boundary checks.
     * @param resolution The screen resolution, used for scaling enemy size.
     */
    Enemy(float startX, float startY, unsigned int screenWidth, const sf::Vector2u& resolution);
    void update(const sf::Time& deltaTime);
    void draw(sf::RenderWindow& window);
    void setTexture(const std::string& texturePath);
    sf::Vector2u getSize() const;
    sf::FloatRect getGlobalBounds() const;
    void kill();
    bool getIsAlive() const;
    void shoot();
    std::vector<Bullet>& getBullets();
    void setIsAlive(bool alive);
    void increaseSpeed(float factor);
    void removeBullet();

private:
    float movementSpeed;
    unsigned int screenWidth;
    bool isAlive;
    static int totalDeath;
    sf::Vector2u res1;
};

#endif // FIRE_FIGHTER_ENEMY_H
