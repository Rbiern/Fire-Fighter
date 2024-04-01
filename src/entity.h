#ifndef FIRE_FIGHTER_ENTITY_H
#define FIRE_FIGHTER_ENTITY_H

#include <SFML/Graphics.hpp>
#include "bullet.h"


class Entity {
protected:
    sf::Sprite sprite;
    sf::Texture texture;
    std::vector<Bullet>  bullet;


public:
    Entity();
    virtual ~Entity() {}

    void setPosition(float x, float y);
    sf::Vector2f getPosition() const;

    void move(float deltaX, float deltaY);

    sf::Sprite& getSprite();

    void draw(sf::RenderWindow& window) const {
        window.draw(sprite);
    }
    bool setTexture(const std::string& texturePath);

    void setScale(float scaleX, float scaleY) {
        sprite.setScale(scaleX, scaleY);
    }
};

#endif //FIRE_FIGHTER_ENTITY_H
