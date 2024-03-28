// Enemy.h
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

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


private:
    sf::Sprite sprite;
    sf::Texture texture;
    float movementSpeed;
    unsigned int screenWidth;
    bool isAlive;
    static int totalDeath; // Already correct
};

class EnemyWave {
public:
    EnemyWave(sf::RenderWindow& window, const sf::Vector2u& resolution);
    void update(sf::Time deltaTime);
    void draw(sf::RenderWindow& window);
    void removeEnemy(int row, int column);
    Enemy& getEnemy(int row, int column);
    int getRows() const;
    int getColumns() const;
    void adjustSpacingForResolution(const sf::Vector2u& resolution);

    //enemy count
    void enemyHit(int row, int column); // Method to call when an enemy is hit
    int getTotalSpawned() const { return totalSpawned; }


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
