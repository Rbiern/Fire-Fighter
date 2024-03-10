#ifndef FIRE_FIGHTER_ENTITY_H
#define FIRE_FIGHTER_ENTITY_H

#include <SFML/Graphics.hpp>

class Entity {
protected:
    sf::Sprite sprite;
    sf::Texture texture;

public:
    Entity();
    virtual ~Entity() {}

    virtual bool loadTexture(const std::string& filename) {
        if (texture.loadFromFile(filename)) {
            sprite.setTexture(texture);
            return true;
        }
        return false;
    }

    void setPosition(float x, float y);

    void move(float deltaX, float deltaY);

    sf::Sprite& getSprite();

    void draw(sf::RenderWindow& window) const {
        window.draw(sprite);
    }
    bool setTexture(const std::string& texturePath);
};

#endif //FIRE_FIGHTER_ENTITY_H
