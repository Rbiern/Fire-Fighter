#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "bullet.h"
#include "enemy.h"
#include <cmath>
#include <iostream>

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
