/**
 * @file Barrier.h
 * @author Chaewon Eom, Robert Andrew Biernacki
 * @brief Declaration of the Barrier class.
 */

#ifndef FIRE_FIGHTER_BARRIER_H
#define FIRE_FIGHTER_BARRIER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "bullet.h"
#include "settings.h"

/**
 * @class Barrier
 * @brief Represents a barrier object in the game.
 *
 * The Barrier class is responsible for managing the properties and behavior of a barrier object
 * within the game environment. Barriers are typically used to provide protection or obstacles
 * for the player or other game elements.
 */
class Barrier {

public:
    /**
     * @brief Constructs a Barrier object with given game settings.
     *
     * Initializes a Barrier object with default size and loads necessary resources such as textures and sound effects.
     * The size of the Barrier is set to 1.0f by default.
     *
     * @param gameSettings the game settings set by the user.
     */
    Barrier(Settings gameSettings);

    /**
     * @brief Destructs a Barrier object.
     */
    ~Barrier();

    /**
     * @brief Sets the position of the Barrier object.
     *
     * This function sets the position of the Barrier object by updating the position of its barrier sprite.
     *
     * @param posX The x-coordinate of the new position.
     * @param posY The y-coordinate of the new position.
     */
    void setPosition(int posX, int posY);

    /**
     * @brief Checks for collision between the Barrier and a bullet.
     *
     * This function determines whether there is a collision between the Barrier and a bullet sprite.
     * It uses the global bounding boxes of the Barrier and the bullet sprite to check for intersection.
     *
     * @param bulletSprite The sprite representing the bullet.
     * @return True if there is a collision, false otherwise.
     */
    bool bulletCollision(const sf::Sprite& bulletSprite) const;

    /**
     * @brief Shrinks the Barrier object.
     *
     * This function decreases the size of the Barrier object and updates its graphical representation accordingly.
     * If sound effect is enabled in the game settings, it plays a sound effect indicating the shrinking action.
     * The size is reduced by a fixed scaling factor, and it is ensured that the size doesn't go below a minimum value,
     * effectively causing the barrier to disappear when it reaches a certain size threshold.
     */
    void shrink();

    /**
     * @brief Resets the Barrier object to its default state.
     *
     * This function resets the Barrier object to its default state by setting its size back to 1.0f
     * and scaling the barrier sprite based on the resolution from the game settings.
     */
    void reset();

    /**
     * @brief Draws the Barrier object.
     *
     * This function draws the Barrier object on the specified SFML render window.
     *
     * @param window The SFML render window on which to draw the Barrier.
     */
    void draw(sf::RenderWindow& window);

private:
    Settings gameSettings; /**< The settings object used for game configuration.*/
    sf::Texture iceBlockTexture; /**< The texture for the ice block barrier.*/
    sf::Sprite iceBlockSprite; /**< The sprite representing the ice block barrier.*/
    float size; /**< The size of the barrier.*/
    sf::SoundBuffer shrinkBuffer; /**< The sound buffer for the shrink effect.*/
    sf::Sound shrinkSound; /**< The sound object for the shrink effect.*/

};

#endif //FIRE_FIGHTER_BARRIER_H
