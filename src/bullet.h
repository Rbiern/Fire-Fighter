#ifndef FIRE_FIGHTER_BULLET_H
#define FIRE_FIGHTER_BULLET_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Bullet {
private:
    sf::Sprite bulletSprite;
    sf::Texture bulletTexture;
    float speed;
    void loadTexture(const std::string& type);
public:
    Bullet(float startX, float startY, const std::string &type, sf::Vector2u res);
    ~Bullet();
    void update(const sf::Time& delta, const std::string &type);
    void draw(sf::RenderWindow& window, const std::string &type);
    sf::FloatRect getGlobalBounds() const;
    const sf::Sprite &getSprite() const;
};

#endif //FIRE_FIGHTER_BULLET_H
