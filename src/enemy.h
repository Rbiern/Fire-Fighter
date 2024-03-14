#ifndef ENEMY_H
#define ENEMY_H

#include "entity.h" // Make sure this path is correct
#include <SFML/Graphics.hpp>
#include <cmath>

class Enemy : public Entity { // This line changes to inherit from Entity
public:
    Enemy(float startX, float startY, float screenWidth);
    void update(const sf::Time& deltaTime);
    void draw(sf::RenderWindow& window);
    void moveTowardsPlayer(const sf::Vector2f& playerPosition, const sf::Time& deltaTime);
    sf::Vector2u getSize() const;


private:
    sf::Sprite sprite;
    sf::Texture texture;
    float movementSpeed;
    float verticalMovementSpeed;
    float startY;
    float time;
    float screenWidth;

    void loadTexture(const std::string& path);

};

#endif // ENEMY_H
