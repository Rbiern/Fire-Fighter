#ifndef FIRE_FIGHTER_GAME_H
#define FIRE_FIGHTER_GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "settings.h"
#include "player.h"
#include "enemy.h"
#include "powerup.h"
#include "barrier.h"
#include "metrics.h"
#include "enemywave.h"


class Game {
private:
    sf::RenderWindow window; ///< Main game window where all graphics are rendered.
    Settings options; ///< Game settings including graphics, sound, and user preferences.
    sf::Font font; ///< Global font used for text elements in the game.
    sf::Image icon; ///< Icon for the game window.
    sf::Music music; ///< Background music player.
    sf::Vector2u resolution; ///< Resolution of the game window, derived from settings.
    sf::Clock clock; ///< Clock for managing updates and timing in the game loop.
    Metrics metrics; ///< Game metrics such as score and health.
    Barrier barrier1, barrier2, barrier3; ///< Barriers that provide cover for the player.
    Powerup powerup; ///< Powerup object for granting player enhancements or bonuses.
    Player* player; ///< Player-controlled character.
    EnemyWave* enemyWave; ///< Management of enemy waves and behavior.


public:
    /**
 * @brief Constructs the Game object with game settings.
 *
 * This constructor initializes the game by setting up the window,
 * loading resources, and preparing the initial state of the game.
 * It sets the window properties based on the settings provided and
 * loads necessary resources such as fonts, icons, and music.
 *
 * @param opt A pointer to the Settings object containing game settings.
 * @author Robert Andrew Biernacki, Chaewon Eom, Prachi Ghevaria, JuYoung Lee, Sungmin Lee
 */
    explicit Game(Settings *opt);

    /**
 * @brief Destroys the Game object.
 *
 * Cleans up resources used by the game. This includes closing the
 * game window and deallocating dynamically allocated memory.
 * It ensures a clean shutdown of the game application.
 *
 * @author Robert Andrew Biernacki
 */
    ~Game();

    /**
 * @brief Contains the main game loop.
 *
 * This method encapsulates the core game loop, including event handling,
 * game updates, and rendering. It manages user input, game state updates,
 * collisions, and drawing the game objects to the screen.
 *
 * @author Robert Andrew Biernacki, Prachi Ghevaria, JuYoung Lee, Sungmin Lee, Chaewon Eom
 */
    void gameLoop();

    /**
 * @brief Displays the character selection screen and processes user input.
 *
 * Allows the player to select a character by displaying a selection screen.
 * Handles user interactions for selecting a character or exiting back to the main UI.
 * It loads and displays character sprites and updates the game state based on the selection.
 *
 * @return char* A string containing the file path of the selected character's texture. Returns NULL if the user exits.
 * @author Robert Andrew Biernacki
 */
    char* characterSelectScreen();

    /**
 * @brief Handles the exit request when the ESC key is pressed.
 *
 * Displays a pause menu with options to exit the game or resume playing.
 * Manages user input to process the selected action.
 *
 * @return bool True if the game should exit, false if the game should resume.
 * @author Robert Andrew Biernacki
 */
    bool handleExitRequest();

    /**
 * @brief Displays the game over screen and offers options to retry or exit.
 *
 * Activated when the player's character runs out of lives or the game reaches
 * a terminal state. It presents the user with options to either restart the game
 * or exit to the main menu.
 *
 * @return bool True if the player chooses to exit the game, false if choosing to retry the game.
 * @author Robert Andrew Biernacki
 */
    bool gameOverScreen();
};

#endif //FIRE_FIGHTER_GAME_H
