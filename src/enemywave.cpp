#include "enemywave.h"

    /**
     *Constructor: Initializes an enemy wave within the game environment, setting up initial positions, spacing,
     *and creating enemies based on the game's window size, resolution, and UI metrics bar height.
     * @param window
     * @param resolution
     * @param metricsBarHeight
     * @author Juyoung Lee, Sungmin Lee
     */
EnemyWave::EnemyWave(sf::RenderWindow& window, const sf::Vector2u& resolution, float metricsBarHeight)
        : window(window),
          rows(5), columns(4), spacingX(100.0f), spacingY(70.0f),
          startX(0.0f),  startY(75.0f + metricsBarHeight) {
    adjustSpacingForResolution(resolution); // Adjust spacing based on resolution
    enemyGrid.resize(rows, std::vector<Enemy>(columns, Enemy(0, 0, window.getSize().x, resolution)));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            float positionX = startX + j * spacingX;
            float positionY = startY + i * spacingY;
            enemyGrid[i][j] = Enemy(positionX, positionY, window.getSize().x, resolution);
            enemyGrid[i][j].setTexture("../../resource/img/fire.png");
            totalSpawned++;
        }
    }
}

    /**
    * Dynamically adjusts enemy spacing based on screen resolution.
    *
    * @param resolution The screen resolution to adapt enemy spacing for.
    */
void EnemyWave::adjustSpacingForResolution(const sf::Vector2u& resolution) {
    if (resolution == sf::Vector2u(640, 360)) {
        spacingX = 70.0f; // Smaller resolution, reduce spacing
        spacingY = 40.0f;
    } else if (resolution == sf::Vector2u(1280, 720)) {
        spacingX = 100.0f; // Base resolution, base spacing
        spacingY = 70.0f;
    } else if (resolution == sf::Vector2u(1920, 1080)) {
        spacingX = 130.0f; // Higher resolution, increase spacing
        spacingY = 90.0f;
    } else if (resolution == sf::Vector2u(3840, 2160)) {
        spacingX = 160.0f; // 4K resolution, further increase spacing
        spacingY = 110.0f;
    } else {

    }
}

    /**
     *Updates the position and state of all enemies in the wave.
     *
     * @param metricsBarHeight The height of the metrics bar, used to prevent enemies from overlapping it.
     */
void EnemyWave::update(float metricsBarHeight) {
    float moveRightDistance = 50.0f;
    static bool movingDown = true;
    static bool hasMovedRightAfterReach = false;
    static bool firstUpdate = true;

    bool bottomReached = false;
    bool topReached = false;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            Enemy& enemy = enemyGrid[i][j];
            if (enemy.getPosition().y + enemy.getGlobalBounds().height > window.getSize().y) {
                bottomReached = true;
                break;
            }
            if (enemy.getPosition().y <= metricsBarHeight) {
                topReached = true;
                break;
            }
        }
        if (bottomReached || topReached) break;
    }

    if (firstUpdate) {
        movingDown = true;
        firstUpdate = false;

    } else if ((bottomReached || topReached) && !hasMovedRightAfterReach) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                Enemy& enemy = enemyGrid[i][j];
                enemy.setPosition(enemy.getPosition().x + moveRightDistance, enemy.getPosition().y);
            }
        }
        hasMovedRightAfterReach = true;
        movingDown = !movingDown;
    } else {
        float moveDistance = movingDown ? 1 : -1;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < columns; ++j) {
                Enemy& enemy = enemyGrid[i][j];
                enemy.setPosition(enemy.getPosition().x, enemy.getPosition().y + moveDistance);
            }
        }
        if (hasMovedRightAfterReach && (bottomReached || topReached)) {
            hasMovedRightAfterReach = false;
        }
    }
}

    /**
     * Draws all enemies in the wave to the provided render window.
     *
     * @param window The window where enemies will be drawn.
     */
void EnemyWave::draw(sf::RenderWindow& window) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            enemyGrid[i][j].draw(window);
        }
    }
}

    /**
     * Accesses a specific enemy in the grid.
     *
     * @param row The row index of the enemy.
     * @param column The column index of the enemy.
     * @return Reference to the Enemy object at the specified grid location.
     */
Enemy& EnemyWave::getEnemy(int row, int column) {
    return enemyGrid[row][column];
}

    /**
     * Gets the number of rows in the enemy grid.
     *
     * @return The total number of rows.
     */
int EnemyWave::getRows() const {
    return rows;
}
    /**
    * Gets the number of columns in the enemy grid.
    *
    * @return The total number of columns.
    */
int EnemyWave::getColumns() const {
    return columns;
}

    /**
     * Checks if all enemies in the wave are defeated.
     *
     * @return True if all enemies are dead, false otherwise.
     */
bool EnemyWave::allEnemiesDead() const {
    for (const auto& row : enemyGrid) {
        for (const auto& enemy : row) {
            if (enemy.getIsAlive()) {
                return false; // If any enemy is alive, return false
            }
        }
    }
    return true; // All enemies are dead
}

/**
     * Respawns enemies with potential modifications for difficulty.
     *
     * @param flag Indicates how enemies should be modified on respawn.
     */
void EnemyWave::respawnEnemies(int flag) {
    float speedIncreaseFactor = 2.0f; //enemy speed increase factor
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            float positionX = startX + j * spacingX;
            float positionY = startY + i * spacingY;
            enemyGrid[i][j].setPosition(positionX, positionY);
            enemyGrid[i][j].setIsAlive(true);
            if(flag == 0){
                enemyGrid[i][j].increaseSpeed(speedIncreaseFactor);
            }else{

            }
        }
    }
}

/**
     *Retrieves the total number of enemies spawned by this wave.
     *
     * @return The total number of enemies spawned.
     */
int EnemyWave::getTotalSpawned() const {
    return totalSpawned;
}
