// Enemy.h
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "bullet.h"

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
    void adjustForResolution(const sf::Vector2u& resolution);
    void kill();
    bool getIsAlive() const;
    static int getTotalDeath();
    const sf::Sprite &getSprite() const;
    void shoot(); // Function to make the enemy shoot
    std::vector<Bullet>& getBullets(); // Function to get the bullets shot by the enemy
    void setIsAlive(bool alive); // Set alive status
    void increaseSpeed(float factor); // Increase movement speed
    bool hasMovedRight = false;
    void removeBullet(Bullet bullet);

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

class EnemyWave {
public:
    EnemyWave(sf::RenderWindow& window, const sf::Vector2u& resolution, float metricsBarHeight);
    void update(sf::Time deltaTime);
    void draw(sf::RenderWindow& window);
    void removeEnemy(int row, int column);
    Enemy& getEnemy(int row, int column);
    int getRows() const;
    int getColumns() const;
    void adjustSpacingForResolution(const sf::Vector2u& resolution);
    sf::RenderWindow& window;
    void respawnEnemies();
    bool allEnemiesDead() const;

    //enemy count
    void enemyHit(int row, int column); // Method to call when an enemy is hit
    int getTotalSpawned() const { return totalSpawned; }
    void update(sf::Time deltaTime, float metricsBarHeight);


private:
    std::vector<std::vector<Enemy>> enemyGrid;
    float waveAmplitude;
    float waveFrequency;
    float wavePhase;
    int rows;
    int columns;
    float spacingX;
    float spacingY;
    float startX;
    float startY;
    int totalSpawned = 0;
};
