#ifndef FIRE_FIGHTER_BULLET_H
#define FIRE_FIGHTER_BULLET_H

#include <SFML/Graphics.hpp>

class Bullet {
public:
    Bullet(float startX, float startY, const std::string &type);
    void update(const sf::Time& delta, const std::string &type);
    void draw(sf::RenderWindow& window);
    sf::FloatRect getGlobalBounds() const;
    const sf::Sprite &getSprite() const;

private:
    sf::Sprite sprite;
    sf::Texture texture;
    float speed;

    void loadTexture(const std::string& type);
    //const sf::Sprite &getSprite() const;
};

#endif //FIRE_FIGHTER_BULLET_H
