/**
 * @file enemy.h
 * @brief Declaration of the Enemy class for representing enemy entities in the game.
 *
 * The Enemy class inherits from the Entity class and is designed to represent enemy entities within the game.
 * It includes functionalities for updating enemy movement, rendering enemies to the screen, handling enemy
 * states (alive or dead), shooting bullets, and managing collision detection.
 *
 * @author Juyoung Lee, Sungmn Lee
 */

#ifndef FIRE_FIGHTER_ENEMY_H
#define FIRE_FIGHTER_ENEMY_H

#include <vector>
#include <string>
#include <iostream>
#include "bullet.h"
#include "entity.h"


class Enemy : public Entity {
public:

    /**
     * @brief Constructs an Enemy with initial position, screen width, and resolution.
     *
     * Initializes the enemy's position, scales its sprite based on the resolution,
     * and adjusts its movement speed accordingly.
     *
     * @param startX Initial X position of the enemy.
     * @param startY Initial Y position of the enemy.
     * @param screenWidth Width of the game screen for boundary checks.
     * @param resolution Current screen resolution for sprite scaling.
     */
    Enemy(float startX, float startY, unsigned int screenWidth, const sf::Vector2u& resolution);

    /**
     * @brief Updates the enemy's position and handles bullet updates.
     *
     * Moves the enemy across the screen and updates the positions of its bullets.
     * Resets enemy position if it moves off-screen.
     *
     * @param deltaTime Time elapsed since the last frame, used for movement calculation.
     */
    void update(const sf::Time& deltaTime);

    /**
     * @brief Draws the enemy and its bullets to the specified render window.
     *
     * @param window Reference to the game window for drawing.
     */
    void draw(sf::RenderWindow& window);

    /**
     * @brief Sets the texture of the enemy from a file path.
     *
     * @param texturePath Path to the texture image file.
     */
    void setTexture(const std::string& texturePath);

    /**
     * @brief Gets the size of the enemy sprite.
     *
     * @return Size of the enemy sprite as a sf::Vector2u.
     */
    sf::Vector2u getSize() const;

    /**
     * @brief Gets the global bounds of the enemy sprite for collision detection.
     *
     * @return Global bounds of the sprite as sf::FloatRect.
     */
    sf::FloatRect getGlobalBounds() const;

    /**
     * @brief Marks the enemy as killed, incrementing the total death count.
     */
    void kill();

    /**
     * @brief Checks if the enemy is alive.
     *
     * @return True if the enemy is alive, false otherwise.
     */
    bool getIsAlive() const;

    /**
     * @brief Enemy shooting action that adds a bullet to its bullets vector.
     */
    void shoot();

    /**
     * @brief Gets a reference to the vector of bullets associated with the enemy.
     *
     * @return Reference to the vector of Bullet objects.
     */
    std::vector<Bullet>& getBullets();

    /**
     * @brief Sets the alive status of the enemy.
     *
     * @param alive Boolean indicating whether the enemy is alive.
     */
    void setIsAlive(bool alive);

    /**
     * @brief Increases the movement speed of the enemy by a specified factor.
     *
     * @param factor The factor by which to increase the movement speed.
     */
    void increaseSpeed(float factor);

    /**
     * @brief Removes bullets that have moved off-screen from the bullets vector.
     */
    void removeBullet();

private:
    std::vector<Bullet> bullets; ///< Vector holding bullets shot by the enemy.
    float movementSpeed; ///< Movement speed of the enemy.
    unsigned int screenWidth; ///< Width of the screen for boundary checks.
    bool isAlive; ///< Flag indicating whether the enemy is alive.
    static int totalDeath; ///< Static counter for total enemy deaths.
    sf::Vector2u res1; ///< Screen resolution for scaling purposes.
};

#endif // FIRE_FIGHTER_ENEMY_H
