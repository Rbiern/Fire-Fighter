#ifndef FIRE_FIGHTER_BULLET_H
#define FIRE_FIGHTER_BULLET_H

#include <SFML/Graphics.hpp>
#include "settings.h"

class Bullet {
public:
    Bullet(float startX, float startY, const std::string &type);
    void update(const sf::Time& delta, const std::string &type);
    void draw(sf::RenderWindow& window, const std::string &type);
    void adjustForResolution(const sf::Vector2u& resolution);
    sf::FloatRect getGlobalBounds() const;
    const sf::Sprite &getSprite() const;

private:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Vector2u resolution;
    settings gameSettings;
    float speed;

    void loadTexture(const std::string& type);
    //const sf::Sprite &getSprite() const;
};

#endif //FIRE_FIGHTER_BULLET_H
