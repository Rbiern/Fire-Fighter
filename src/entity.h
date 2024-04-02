#ifndef FIRE_FIGHTER_ENTITY_H
#define FIRE_FIGHTER_ENTITY_H

#include <SFML/Graphics.hpp>
#include "bullet.h"

/**
 * @brief The base class for game entities.
 * @author Sungmin Lee
 * Enemy, Bullet, and Player classes are inherited from Entity
 */
class Entity {
protected:
    sf::Sprite sprite; /**< The sprite representing the entity. */
    sf::Texture texture; /**< The texture of the entity. */
    std::vector<Bullet>  bullet;  /**< Vector of bullets fired by the entity. */

public:
    /**
     * @brief Default constructor.
     */
    Entity();
    /**
    * @brief Virtual destructor.
    */
    virtual ~Entity() {}
    /**
     * @brief Set the position of the entity.
     * @param x The x-coordinate of the position.
     * @param y The y-coordinate of the position.
     */
    void setPosition(float x, float y);

    /**
     * @brief Get the position of the entity.
     * @return The position of the entity as a 2D vector.
     */
    sf::Vector2f getPosition() const;

    /**
     * @brief Move the entity by a specified amount.
     * @param deltaX The amount to move along the x-axis.
     * @param deltaY The amount to move along the y-axis.
     */
    void move(float deltaX, float deltaY);

    /**
     * @brief Get the sprite of the entity.
     * @return A reference to the entity's sprite.
     */
    sf::Sprite& getSprite();
    /**
     * @brief Draw the entity on a render window.
     * @param window The render window to draw the entity on.
     */
    void draw(sf::RenderWindow& window) const;
    /**
     * @brief Set the texture of the entity.
     * @param texturePath The path to the texture file.
     * @return True if the texture was successfully loaded, false otherwise.
     */
    bool setTexture(const std::string& texturePath);
    /**
     * @brief Set the scale of the entity.
     * @param scaleX The scale factor along the x-axis.
     * @param scaleY The scale factor along the y-axis.
     */
    void setScale(float scaleX, float scaleY);
};

#endif //FIRE_FIGHTER_ENTITY_H
