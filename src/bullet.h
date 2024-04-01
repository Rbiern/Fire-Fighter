/**
 * @file bullet.h
 * @author Sungmin Lee, Prachi Ghevaria
 * @brief Declaration of the Bullet class.
 */

#ifndef FIRE_FIGHTER_BULLET_H
#define FIRE_FIGHTER_BULLET_H

#include <SFML/Graphics.hpp>
#include <iostream>

/**
 * @class Bullet
 * @brief Represents a bullet object in the game.
 *
 * The Bullet class manages the properties and behavior of a bullet object within the game environment.
 * Bullets can be fired by players or enemies and move horizontally across the screen.
 */
class Bullet {

public:
    /**
     * @brief Constructs a Bullet object with specified parameters.
     *
     * This constructor initializes a Bullet object with the given starting position, type, and game resolution.
     * It loads the appropriate texture for the bullet based on its type and sets its initial position and scale.
     * The speed of the bullet is set to a default value of 300 units per second.
     *
     * @param startX The starting x-coordinate of the bullet.
     * @param startY The starting y-coordinate of the bullet.
     * @param type The type of bullet ("player" or "enemy").
     * @param res The resolution of the game window.
     */
    Bullet(float startX, float startY, const std::string &type, sf::Vector2u res);

    /**
     * @brief Destructor for the Bullet class.
     */
    ~Bullet();

    /**
     * @brief Updates the bullet's position based on its type and elapsed time.
     *
     * This function updates the position of the bullet sprite based on its type ("player" or "enemy")
     * and the elapsed time since the last update. For "enemy" bullets, it moves the bullet sprite
     * to the right, while for "player" bullets, it moves the bullet sprite to the left.
     *
     * @param delta The elapsed time since the alst update.
     * @param type The type of bullet ("player" or "enemy").
     */
    void update(const sf::Time& delta, const std::string &type);

    /**
     * @brief Draws the bullet sprite on the specified render window.
     *
     * This function draws the bullet sprite on the provided SFML render window.
     * It first loads the appropriate texture for the bullet based on its type,
     * then draws the bullet sprite onto the render window.
     *
     * @param window The SFML render window to draw the bullet on.
     * @param type The type of bullet ("player" or "enemy").
     */
    void draw(sf::RenderWindow& window, const std::string &type);

    /**
    * @brief Returns the global bounding rectangle of the bullet sprite.
    *
    * This function returns the global bounding rectangle of the bullet sprite,
    * which represents the position and size of the sprite in global coordinates.
    *
    * @return The global bounding rectangle of the bullet sprite.
    */
    sf::FloatRect getGlobalBounds() const;

    /**
     * @brief Returns the bullet sprite.
     *
     * This function returns a constant reference to the bullet sprite,
     * allowing external access to the sprite without modifying it.
     * @return A constant reference to the bullet sprite.
     */
    const sf::Sprite& getSprite() const;

private:
    sf::Sprite bulletSprite; /**< The sprite representing the bullet. */
    sf::Texture bulletTexture; /**< The texture of the bullet sprite. */
    float speed; /**< The speed of the bullet. */

    /**
     * @brief Loads the appropriate texture for the bullet based on its type.
     *
     * This function loads the appropriate texture for the bullet sprite based on its type.
     * If the type is "player", it loads the droplet texture. If the type is "enemy",
     * it loads the fireball texture. If the texture loading fails, an error message is printed.
     *
     * @param type The type of bullet ("player" or "enemy").
     */
    void loadTexture(const std::string& type);
};

#endif //FIRE_FIGHTER_BULLET_H
