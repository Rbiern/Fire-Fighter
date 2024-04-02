/**
 * @file Enemywave.h
 * @brief Declaration of the Enemywave class.
 */

#ifndef FIRE_FIGHTER_ENEMYWAVE_H
#define FIRE_FIGHTER_ENEMYWAVE_H

#pragma once
#include <vector>
#include <string>
#include "bullet.h"
#include "enemy.h"
#include <cmath>
#include <iostream>

/**
 * @class Enemywave
 * @brief Represents a enemy movement object in the game.
 *
 * This class is responsible for creating, managing, and updating enemy waves within the game. It handles the
 * initialization of enemies based on the game window size and resolution, and provides functionality to update
 * enemy positions and behaviors over time.
 */
class EnemyWave {

public:
    /**
     *Constructor: Initializes an enemy wave within the game environment, setting up initial positions, spacing,
     *and creating enemies based on the game's window size, resolution, and UI metrics bar height.

    * @param window
     * @param resolution
     * @param metricsBarHeight
     */
    EnemyWave(sf::RenderWindow& window, const sf::Vector2u& resolution, float metricsBarHeight);
    void update(sf::Time deltaTime);
    void draw(sf::RenderWindow& window);
    Enemy& getEnemy(int row, int column);
    int getRows() const;
    int getColumns() const;
    void adjustSpacingForResolution(const sf::Vector2u& resolution);
    sf::RenderWindow& window;
    void respawnEnemies(int flag);
    bool allEnemiesDead() const;
    int getTotalSpawned() const;
    void update(float metricsBarHeight);


private:
    std::vector<std::vector<Enemy>> enemyGrid;
    int rows;
    int columns;
    float spacingX;
    float spacingY;
    float startX;
    float startY;
    int totalSpawned = 0;
};

#endif FIRE_FIGHTER_ENEMYWAVE_H
