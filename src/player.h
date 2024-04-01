#ifndef FIRE_FIGHTER_PLAYER_H
#define FIRE_FIGHTER_PLAYER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "entity.h"
#include "bullet.h"
#include <SFML/Audio.hpp>
#include "settings.h"
#include "barrier.h"
#include "enemy.h"
#include "metrics.h"
#include <iostream>
#include <string>

/**
 * @class Player
 * @brief Manages the player's behavior and state in the game.
 *
 * The Player class is responsible for controlling the player's movements, handling shooting mechanics,
 * detecting collisions with enemies and barriers, and managing the player's health and speed.
 * It extends the Entity class, utilizing its position and texture properties.
 */
class Player : public Entity {
public:
    /**
     * @brief Constructs a Player object with initial position and game resolution.
     * @param startX Starting X coordinate of the player.
     * @param startY Starting Y coordinate of the player.
     * @param resolution The current game screen resolution, used for scaling the player's bulletSprite.
     *
     * Initializes player's properties such as movement speed, health, and sets up the sound effects for shooting.
     */
    Player(float startX, float startY, const sf::Vector2u& resolution);

    /**
     * @brief Destructor for Player, cleans up allocated resources.
     */
    virtual ~Player();

    /**
     * @brief Fires a bullet, adding it to the bullets vector.
     *
     * Creates a Bullet instance at the player's current position and plays a shooting sound effect if enabled.
     */
    void shoot();

    /**
     * @brief Updates the state and position of bullets, checks for collisions with enemies.
     * @param delta Time elapsed since the last frame.
     * @param enemyWave The current wave of enemies to check for collisions.
     * @param metrics Metrics object for updating game statistics like score.
     */
    void updateBullets(const sf::Time& delta, EnemyWave& enemyWave, Metrics& metrics);

    /**
     * @brief Updates bullets for collisions with barriers and handles the barrier shrinking.
     * @param delta Time elapsed since the last frame.
     * @param barrier The barrier instance to check for bullet collisions.
     */
    void updateBarrier(const sf::Time delta, Barrier& barrier);

    /**
     * @brief Draws bullets on the given render window.
     * @param window The window where bullets will be drawn.
     */
    void drawBullets(sf::RenderWindow& window);

    /**
     * @brief Moves the player in the given direction.
     * @param direction The vector indicating direction and magnitude of the movement.
     */
    void move(const sf::Vector2f& direction);

    /**
     * @brief Draws the player bulletSprite on the specified window.
     * @param window The render window to draw the player on.
     */
    void draw(sf::RenderWindow& window);

    /**
     * @brief Sets the player's movement speed.
     * @param speed New movement speed.
     */
    void setSpeed(float speed);

    /**
     * @brief Retrieves the player's current movement speed.
     * @return The current movement speed of the player.
     */
    float getSpeed() const;

    /**
     * @brief Gets the size of the player's bulletSprite.
     * @return The size of the player's bulletSprite as an sf::Vector2f.
     */
    sf::Vector2f getSize() const;

    /**
     * @brief Sets the player's life count.
     * @param lives New number of lives for the player.
     */
    void setLives(int lives);

    /**
     * @brief Retrieves the current number of lives the player has.
     * @return Current number of lives.
     */
    int getLives() const;

    /**
     * @brief Decreases the player's life count by one.
     */
    void decreaseLife();

    /**
     * @brief Increases the player's life count by one, not exceeding the maximum.
     */
    void increaseLife();

    /**
     * @brief Checks for collision between the player and an enemy bulletSprite.
     * @param enemySprite The bulletSprite of the enemy to check for collision.
     * @return True if the player is colliding with the enemy bulletSprite, false otherwise.
     */
    bool isCollidingWithEnemy(const sf::Sprite& enemySprite) const;

    /**
     * @brief Sets the texture for the player's bulletSprite.
     * @param t The file path to the texture.
     */
    void setPlayerTexture(char *t);

private:
    float movementSpeed; ///< The player's movement speed.
    int lives; ///< The number of lives the player has.
    sf::SoundBuffer shootBuffer; ///< Buffer for the shooting sound effect.
    sf::Sound shootSound; ///< Sound effect for shooting.
    std::vector<Bullet> bullets; ///< Container for bullets fired by the player.
    settings *options; ///< Pointer to game settings, used for sound toggling.

    /**
     * @brief Sets the scale factor for the player's bulletSprite.
     * @param scaleFactor The factor by which to scale the bulletSprite.
     */
    void setScale(float scaleFactor);

    /**
     * @brief Adjusts the player's bulletSprite and speed based on the game's resolution.
     * @param resolution The current game screen resolution.
     */
    void adjustForResolution(const sf::Vector2u &resolution);
};

#endif //FIRE_FIGHTER_PLAYER_H
