/**
 * @file EnemyWave.h
 * @brief Handles the organization and behavior of enemy waves in the game.
 *
 * The EnemyWave class manages the spawning, organization, and movement of enemy units within the game.
 * It calculates the positioning and spacing of enemies based on the game window's size and resolution,
 * adjusting dynamically to fit a variety of screen sizes. The class also handles enemy wave updates,
 * including movement patterns and respawn mechanisms, to maintain gameplay challenge and variety.
 *
 * @details The class uses a grid to organize enemies, allowing for easy management of enemy positions
 * and states. EnemyWave is responsible for drawing all enemies onto the game window, updating their
 * positions according to predefined patterns, and checking for conditions such as all enemies being defeated.
 * It supports varying resolutions by adjusting the spacing between enemies, ensuring that the game
 * looks consistent across different devices.
 *
 * @author Juyoung Lee, Sungmin Lee
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
    /**
     * @brief Updates the positions and states of all enemies in the wave.
     *
     * Moves enemies according to their behavior patterns and checks for game events like reaching
     * the screen edge or player interactions.
     *
     * @param deltaTime The time elapsed since the last frame.
     */
    void update(sf::Time deltaTime);

    /**
     * @brief Draws all enemies in the wave to the provided render window.
     *
     * @param window The window where enemies will be drawn.
     */
    void draw(sf::RenderWindow& window);

    /**
     * @brief Accesses a specific enemy in the grid.
     *
     * @param row The row index of the enemy.
     * @param column The column index of the enemy.
     * @return Reference to the Enemy object at the specified grid location.
     */
    Enemy& getEnemy(int row, int column);

    /**
     * @brief Gets the number of rows in the enemy grid.
     *
     * @return The total number of rows.
     */
    int getRows() const;

    /**
    * @brief Gets the number of columns in the enemy grid.
    *
    * @return The total number of columns.
    */
    int getColumns() const;

    /**
    * @brief Dynamically adjusts enemy spacing based on screen resolution.
    *
    * @param resolution The screen resolution to adapt enemy spacing for.
    */
    void adjustSpacingForResolution(const sf::Vector2u& resolution);

    /**
     * @brief Respawns enemies with potential modifications for difficulty.
     *
     * Can increase speed or change patterns based on the flag parameter.
     *
     * @param flag Indicates how enemies should be modified on respawn.
     */
    void respawnEnemies(int flag);

    /**
     * @brief Checks if all enemies in the wave are defeated.
     *
     * @return True if all enemies are dead, false otherwise.
     */
    bool allEnemiesDead() const;

    /**
     * @brief Retrieves the total number of enemies spawned by this wave.
     *
     * @return The total number of enemies spawned.
     */
    int getTotalSpawned() const;

    /**
     * @brief Updates the position and state of all enemies in the wave.
     *
     * Moves the enemies down or up and sideways once they reach the bottom or top of the play area.
     * This creates a wave-like motion. Also handles the logic for moving enemies right after they
     * reach the top or bottom.
     *
     * @param metricsBarHeight The height of the metrics bar, used to prevent enemies from overlapping it.
     */
    void update(float metricsBarHeight);


private:
    sf::RenderWindow& window; ///< Reference to the main game window.
    std::vector<std::vector<Enemy>> enemyGrid; ///< 2D vector holding the grid of enemies.
    int rows; ///< Number of rows in the enemy grid.
    int columns; ///< Number of columns in the enemy grid.
    float spacingX; ///< Horizontal spacing between enemies.
    float spacingY; ///< Vertical spacing between enemies.
    float startX; ///< X-coordinate for the first enemy in the grid.
    float startY; ///< Y-coordinate for the first enemy, adjusted for the UI's metrics bar.
    int totalSpawned = 0; ///< Counter for the total number of enemies spawned in the wave.
};

#endif FIRE_FIGHTER_ENEMYWAVE_H
