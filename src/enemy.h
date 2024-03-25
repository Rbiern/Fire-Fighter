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
    void adjustForResolution(const sf::Vector2u& resolution);


private:
    sf::Sprite sprite;
    sf::Texture texture;
    float movementSpeed;
    unsigned int screenWidth;
};

class EnemyWave {
public:
    EnemyWave(sf::RenderWindow& window);
    void update(sf::Time deltaTime);
    void draw(sf::RenderWindow& window);

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
};
