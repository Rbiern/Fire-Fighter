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
 *
 * The Enemy class extends the Entity class to represent enemies in the game.
 * It manages enemy movement, rendering, and interactions, such as shooting and being killed.
 */
class Enemy : public Entity {
public:
    /**
     * Constructor for an Enemy.
     * @brief Initializes an enemy with a starting position, screen width for boundary checks, and resolution for scaling.
     *
     * @param startX The starting X position of the enemy.
     * @param startY The starting Y position of the enemy.
     * @param screenWidth The width of the screen, used for boundary checks.
     * @param resolution The screen resolution, used for scaling enemy size.
     */
    Enemy(float startX, float startY, unsigned int screenWidth, const sf::Vector2u& resolution);
    /**
     * @brief Updates the enemy's state. This includes moving the enemy and updating the position of its bullets.
     * @param deltaTime The time elapsed since the last update.
     */
    void update(const sf::Time& deltaTime);
    /**
     * @brief Draws the enemy on the provided window.
     * @param window Reference to the SFML window where the enemy will be drawn.
     */
    void draw(sf::RenderWindow& window);

    /**
     * @brief Sets the texture of the enemy.
     * @param texturePath Path to the texture file.
     */
    void setTexture(const std::string& texturePath);
    /**
     * @brief Gets the size of the enemy sprite.
     * @return The size of the enemy as an sf::Vector2u.
     */
    sf::Vector2u getSize() const;
    /**
     * Gets the global bounds of the enemy sprite.
     * Useful for collision detection.
     *
     * @return The global bounds of the enemy as an sf::FloatRect.
     */
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
