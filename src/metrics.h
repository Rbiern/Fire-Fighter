#ifndef FIRE_FIGHTER_METRICS_H
#define FIRE_FIGHTER_METRICS_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "settings.h"

/**
 * @author Prachi Ghevaria
 * @brief Metrics class for managing game metrics.
 *
 * This class handles various game metrics such as score, health, and stage information.
 * It also manages the display of these metrics on the game screen.
 */
class Metrics {
public:
    /**
     * @brief Constructs a Metrics object with specified parameters.
     *
     * Initializes a Metrics object with the given window size and optional settings.
     * It calculates the height of the infoBar as 10% of the window's height and creates an infoBar accordingly.
     * Various text elements such as score, enemy killed count, round number, and enemies remaining are initialized and positioned on the infoBar.
     * Life counter textures are loaded for displaying health status, and the health bar sprite is set up accordingly.
     *
     * @param windowSize The size of the game window.
     * @param opt Optional settings for customizing the Metrics object.
     */
    Metrics(sf::Vector2u windowSize, Settings* opt);

    /**
     * @brief Default destructor for the Metrics class.
     *
     * This destructor is defaulted, meaning it does not have custom cleanup operations.
     * It will automatically release resources and memory allocated by the Metrics class.
     */
    ~Metrics();

    /**
     * @brief Updates the health bar texture based on the player's remaining lives.
     *
     * This function updates the health bar texture based on the player's remaining lives.
     * It switches between different life counter textures depending on the number of lives.
     *
     * @param lives The number of lives remaining for the player.
     */
    void updateHealthbar(int lives);

    /**
     * @brief Draws the metrics elements on the specified render target.
     *
     * This function draws various metrics elements, such as the infoBar, separation line, score text, round text, health bar,
     * enemy killed text, and enemies remaining text, on the specified render target (window).
     *
     * @param window The render target (SFML RenderTarget) to draw the metrics elements on.
     */
    void draw(sf::RenderTarget& target);

    /**
     * @brief Draws the final score elements on the specified render target.
     *
     * This function draws the final score elements, including the score text, round text, and enemy killed text,
     * at specific positions on the specified render target (window). These elements are positioned centered horizontally
     * and vertically at one-third of the window's height.
     *
     * @param window The render target (SFML RenderTarget) to draw the final score elements on.
     */
    void drawFinalScore(sf::RenderTarget& target);

    /**
     * @brief Sets the count of remaining enemies and updates the corresponding text.
     *
     * This function sets the count of remaining enemies to the specified value and updates
     * the enemies remaining text accordingly.
     *
     * @param enemyCount The count of remaining enemies.
     */
    void setEnemyCount(int enemyCount);

    /**
     * @brief Increases the score by the specified points and updates the corresponding texts.
     *
     * This function increases the score by the specified points and updates the score text, round text,
     * enemy killed text, and enemies remaining text accordingly.
     *
     * @param points The points to be added to the score.
     */
    void increaseScore(int points);

    /**
     * @brief Updates the new highest score if current score is greater.
     *
     * This function updates the new highest score if current score is greater than the highest score saved in highestScore.txt.
     * It also stores the new highest score in the text file.
     *
     */
    void updateHighestScore();

    /**
     * @brief Returns the highest score achieved.
     *
     * This function returns the highest score achieved by the player.
     *
     * @return The highest score.
     */
    int getHighestScore() const;

    /**
     * @brief Resets the metrics to their default state.
     *
     * This function resets the metrics, including the score and various text elements,
     * to their default state. It sets the score to zero and updates the score text,
     * enemy killed text, round text, and enemies remaining text accordingly.
     */
    void reset();

    /**
     * @brief Calculates the current stage based on the score and number of enemies.
     *
     * This function calculates the current stage based on the score and number of enemies.
     * It divides the score by 10 to determine the stage progression, taking into account
     * the number of enemies defeated. The stage is incremented by 1 to start from 1.
     *
     * @return The current stage number.
     */
    int getStage();

private:
    int highestScore; /** The player's highest score. **/
    sf::RectangleShape infoBar; /**< The rectangular shape representing the info bar. */
    sf::RectangleShape separationLine; /**< The rectangular shape representing the separation line within the info bar. */
    sf::Font font; /**< The font used for text rendering. */
    sf::Vector2u windowSize; /**< The size of the game window. */
    sf::Text scoreText; /**< The text displaying the player's score. */
    sf::Text roundText; /**< The text displaying the current round. */
    sf::Text enemyKilledText; /**< The text displaying the number of enemies killed. */
    sf::Text enemiesRemainingText; /**< The text displaying the number of enemies remaining. */
    sf::Text highestScoreText; /**<The text displaying the highest score. */
    Settings* options; /**< Pointer to the settings object. */
    int score; /**< The player's current score. */
    int enemySum; /**< The total number of enemies. */
    sf::Texture life3Texture; /**< The texture representing 3 lives for the health bar. */
    sf::Texture life2Texture; /**< The texture representing 2 lives for the health bar. */
    sf::Texture life1Texture; /**< The texture representing 1 life for the health bar. */
    sf::Texture life0Texture; /**< The texture representing 0 lives for the health bar. */
    sf::Sprite healthBar; /**< The sprite representing the health bar. */

};

#endif //FIRE_FIGHTER_METRICS_H
