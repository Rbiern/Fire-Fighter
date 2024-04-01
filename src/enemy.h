#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "bullet.h"
#include <cmath>
#include <iostream>

class Enemy {
public:
    Enemy(float startX, float startY, unsigned int screenWidth, const sf::Vector2u& resolution);
    void update(const sf::Time& deltaTime);
    void draw(sf::RenderWindow& window);
    void setTexture(const std::string& texturePath);
    sf::Vector2f getPosition() const;
    void setPosition(float x, float y);
    sf::Vector2u getSize() const;
    sf::FloatRect getGlobalBounds() const;
    void kill();
    bool getIsAlive() const;
    static int getTotalDeath();
    const sf::Sprite &getSprite() const;
    void shoot(); // Function to make the enemy shoot
    std::vector<Bullet>& getBullets(); // Function to get the bullets shot by the enemy
    void setIsAlive(bool alive); // Set alive status
    void increaseSpeed(float factor); // Increase movement speed
    bool hasMovedRight = false;
    void removeBullet();

private:
    sf::Sprite sprite;
    sf::Texture texture;
    std::vector<Bullet> bullets;
    float movementSpeed;
    unsigned int screenWidth;
    bool isAlive;
    static int totalDeath;
    sf::Vector2u res1;
};

