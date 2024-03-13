#ifndef FIRE_FIGHTER_ENEMY_H
#define FIRE_FIGHTER_ENEMY_H
#include "entity.h"
#include <SFML/Graphics.hpp>
#include <cmath> // For sin function

class Enemy {
public:
    Enemy(float startX, float startY, float screenWidth); // Modified constructor
    void update(const sf::Time& deltaTime);
    void draw(sf::RenderWindow& window);
    void moveTowardsPlayer(const sf::Vector2f& playerPosition, const sf::Time& deltaTime);


private:
    sf::Sprite sprite;
    sf::Texture texture;
    float movementSpeed;
    float verticalMovementSpeed;
    float startY; // Starting Y position for oscillation
    float time; // To control the oscillation over time
    float screenWidth;




    void loadTexture(const std::string& path);
};

#endif // FIRE_FIGHTER_ENEMY_H
