/**
 * @file Powerup.h
 * @author Prachi Ghevaria
 * @brief Declaration of the Powerup class.
 */

#ifndef FIRE_FIGHTER_POWERUP_H
#define FIRE_FIGHTER_POWERUP_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include "player.h"

/**
 * @class Powerup
 * @brief Represents a Powerup object in the game.
 *
 * The Powerup class is responsible for managing the properties and behavior of a power-up object
 * within the game environment. Power-ups are typically used to provide more lives for the player.
 */
class Powerup {
public:
    /**
     * @brief Constructs a Powerup object.
     *
     * Initializes a Powerup object by loading its texture from a file and setting up its sprite.
     * The default texture for the powerup is "life.png". If the texture loading fails, an error message is printed.
     * The sprite's scale is adjusted based on the game settings.
     */
    Powerup();

    /**
     * @brief Destructs a Powerup object.
     */
    ~Powerup();

    /**
     * @brief Resets the Powerup object to its initial state.
     *
     * This function resets the Powerup object by randomizing its starting position, speed, direction,
     * appearance delay timer, and collected status. The starting position is randomized within a certain range
     * along the Y-axis. The speed is set to a default value, and the direction is initialized to move towards the right.
     * The appearance delay timer is reset to a random value between 2 and 10 seconds.
     */
    void reset();

    /**
     * @brief Updates the Powerup object based on elapsed time, player interaction, and window boundaries.
     *
     * This function updates the Powerup object's position, collision detection with the player, and behavior near window boundaries.
     * It checks if the powerup has been collected and if the player's lives are less than 3. If so, it updates the powerup's position
     * and checks for collision with the player. If the powerup collides with the player, the player's life is increased, and the powerup
     * is marked as collected. The powerup bounces off window walls and changes direction if it reaches the left or right edges of the window.
     * Additionally, it bounces off the top and bottom walls and randomly moves up or down if it hits the top or bottom edge of the window.
     * If the powerup is collected or the player's lives are at maximum (3), the powerup is reset.
     *
     * @param delta The elapsed time since the last update.
     * @param player A pointer to the Player object for collision detection.
     * @param window The SFML render window for boundary checking.
     */
    void update(const sf::Time& delta, Player* player, sf::RenderWindow& window);

    /**
     * @brief Draws the Powerup object on the specified render window.
     *
     * This function draws the Powerup object on the provided SFML render window if conditions are met.
     * It checks if the powerup has been collected, if the player's lives are less than 3, and if it's time
     * to show the powerup. If these conditions are satisfied, the powerup sprite is drawn on the window.
     *
     * @param window The SFML render window to draw the powerup on.
     * @param player A pointer to the Player object for condition checking.
     */
    void draw(sf::RenderWindow& window, Player* player);

private:
    sf::Texture texture; /**< The texture of the powerup sprite. */
    sf::Sprite sprite; /**< The sprite representing the powerup. */
    float speed; /**< The speed of the powerup. */
    sf::Vector2f direction; /**< The direction of movement for the powerup. */
    bool collected; /**< Flag indicating whether the powerup has been collected. */
    std::mt19937 gen; /**< Random number generator for powerup properties. */
    sf::Vector2u resolution; /**< The resolution of the game window. */
    Settings gameSettings; /**< The game settings object. */
    sf::Time time; /**< Elapsed time since the powerup appeared. */
    int appearanceDelay; /**< The delay before the powerup appears after it's created. */

};

#endif //FIRE_FIGHTER_POWERUP_H
