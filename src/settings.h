#ifndef FIRE_FIGHTER_SETTINGS_H
#define FIRE_FIGHTER_SETTINGS_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <bitset>

/**
 * @file settings.h
 * @author Robert Andrew Biernacki
 * @brief Declaration of the Settings class.
 */
class Settings {

public:
    /**
     * @brief Constructs a Settings object by reading settings from a configuration file.
     *
     * This constructor initializes a Settings object by reading settings from a configuration file.
     * It opens the settings file, reads each line, converts binary strings to integers, and assigns
     * the values to corresponding settings variables. It also loads the appropriate font based on
     * the selected language. If the file cannot be opened or if there are any errors, appropriate
     * error messages are printed to the standard error stream.
     */
    Settings();

    /**
     * @brief Default destructor for the Settings class.
     *
     * This destructor is defaulted, meaning it has no additional functionality
     * beyond the default behavior provided by the compiler. It is provided here
     * for completeness and readability.
     */
    ~Settings();

    /**
     * @brief Implements a Settings window loop for the game.
     *
     * This function creates a window with options based on the current settings.
     * It creates buttons and text for adjusting language and resolution settings;
     * handles mouse clicks on the buttons to change settings such as language, resolution, fullscreen mode, music, and sound effects;
     * saves the settings to a file when "Apply" button is pressed;
     * and cancels any changes made when the "Cancel" button is pressed.
     */
    void openSettings();

    /**
     * @brief Get the resolution settings.
     *
     * This function returns an array containing the resolution settings. The array
     * contains two integers representing the width and height of the resolution,
     * respectively. Index 0 holds the width, and index 1 holds the height.
     *
     * @return int* An array containing the resolution settings.
     */
    int* getResolution();

    /**
     * @brief Get the language settings.
     *
     * This function returns an array containing the language settings. The array
     * contains a sequence of sf::String objects representing different language options.
     *
     * @return sf::String* An array containing the language settings.
     */
    sf::String * getLanguage();

    /**
     * @brief Check if the application is running in fullscreen mode.
     *
     * This function returns a boolean indicating whether the application is currently running
     * in fullscreen mode.
     *
     * @return bool True if the application is in fullscreen mode, false otherwise.
     */
    bool isFullScreen() const;

    /**
     * @brief Toggle the music setting.
     *
     * This function returns the current state of the music setting. If music is enabled,
     * it returns true; otherwise, it returns false.
     *
     * @return bool True if music is enabled, false otherwise.
     */
    bool toggleMusic() const;

    /**
     * @brief Toggle the sound effects on or off.
     *
     * This function returns a boolean indicating whether the sound effects are currently enabled or not.
     *
     * @return bool True if sound effects are enabled, false otherwise.
     */
    bool toggleSounds() const;

    /**
     * @brief Get the font used for rendering text in the application.
     *
     * This function returns the font used for rendering text in the application.
     *
     * @return sf::Font The font used for rendering text.
     */
    sf::Font getFont();

    /**
     * @brief Get the icon used for the application window.
     *
     * This function returns the icon used for the application window.
     *
     * @return sf::Image The icon used for the application window.
     */
    sf::Image getIcon();

    /**
     * @brief Scale a given value according to the width of the resolution.
     *
     * This function scales a given value according to the width of the resolution, maintaining aspect ratio.
     *
     * @param x The value to be scaled.
     * @return float The scaled value.
     */
    float widthScaling(float x);

    /**
     * @brief Scale a given value according to the height of the resolution.
     *
     * This function scales a given value according to the height of the resolution, maintaining aspect ratio.
     *
     * @param y The value to be scaled.
     * @return float The scaled value.
     */
    float heightScaling(float y);

    /**
     * @brief Get the resolution as a sf::Vector2u object.
     *
     * This function returns the resolution as a sf::Vector2u object.
     *
     * @return sf::Vector2u The resolution as a sf::Vector2u object.
     */
    sf::Vector2u getVector();

    /**
     * @brief Set a custom screen resolution.
     *
     * This function sets a custom screen resolution provided by the user.
     *
     * @param x The width of the custom resolution.
     * @param y The height of the custom resolution.
     */
    void userScreenInfo(int x, int y);

private:
    /**
     * @brief A nested class representing different pairs of resolutions.
     */
    class resolutionPairs {
    public:
        int dv[2] = {640, 360}; /**< Resolution for DV (640x360). */
        int sd[2] = {1280, 720}; /**< Resolution for SD (1280x720). */
        int hd[2] = {1920, 1080}; /**< Resolution for HD (1920x1080). */
        int uhd[2] = {3840, 2160}; /**< Resolution for UHD (3840x2160). */
        int uniqueRes[2]; /**< Array to store a unique resolution. */
    } res; /**< Instance of the resolutionPairs class. */
    int dataFromFile[7]{}; /**< Array to store data read from a file. */
    bool fullscreen; /**< Flag indicating whether the game is in fullscreen mode. */
    int *resolution; /**< Pointer to an array representing the resolution. */
    int frameRate; /**< Frame rate of the game. */
    int rotation; /**< Rotation setting of the game. */
    bool music; /**< Flag indicating whether music is enabled. */
    bool soundEffects; /**< Flag indicating whether sound effects are enabled. */
    sf::String *language; /**< Pointer to an array representing the selected language. */
    sf::Font font; /**< Font used for text rendering. */
    sf::Image icon; /**< Image used for the application icon. */

    /**
     * @brief A nested class representing different languages and their respective strings.
     */
    class languages {
    public:
        sf::String English[27] = {"NEW GAME", "SETTINGS", "QUIT", "Fullscreen", "Music", "Sound Effects", "Rotation", "On", "Off", "Select Languages", "Select Resolution", "Apply", "Cancel", "Choose a Character", "Go Back", "Water Girl", "Water Boy", "Exit", "Retry", "Game Over!", "Exit Game", "Resume Game", "Score: ", "Enemies Killed: ", "Stage: ", "Enemies Remaining: ", "Highest Score: "}; /**< Array of English strings. */
        sf::String Korean[27] = {L"\uC0C8 \uAC8C\uC784", L"\uC138\uD305", L"\uC885\uB8CC", L"\uc804\uccb4\u0020\ud654\uba74\u000d", L"\uc74c\uc545", L"\uc74c\ud5a5\u0020\ud6a8\uacfc", L"\ud68c\uc804", L"\ucf1c\uc9d0", L"\uaebc\uc9d0", L"\uc5b8\uc5b4\u0020\uc120\ud0dd", L"\ud574\uc0c1\ub3c4", L"\ud655\uc778", L"\ucde8\uc18c", L"\uce90\ub9ad\ud130\u0020\uc120\ud0dd",L"\ub4a4\ub85c", L"\uBB3C \uC18C\uB140", L"\uBB3C\uC18C\uB144", L"\uCD9C\uAD6C", L"\uc7ac\uc2dc\uc791", L"\uac8c\uc784\u0020\uc624\ubc84\u000d", L"\uc885\ub8cc\u000d", L"\uac8c\uc784\u0020\uc7ac\uac8c",L"\uc810\uc218\uFF1A", L"\uc8fd\uc740\u0020\uc801\uFF1A", L"\uc2a4\ud14c\uc774\uc9c0\uFF1A", L"\ub0a8\uc740\u0020\uc801\u0020\u003a\u0020", L"\ucd5c\uace0\u0020\uc810\uc218\u003a\u0020"}; /**< Array of Korean strings. */
        sf::String Mandarin[27] = {L"\u65B0\u6E38\u620F", L"\u8BBE\u7F6E", L"\u8F9E\u804C", L"\u5168\u5C4F", L"\u97F3\u4E50", L"\u58F0\u97F3\u7279\u6548", L"\u56DE\u8F6C", L"\u5728", L"\u79BB\u5F00", L"\u9009\u62E9\u8BED\u8A00", L"\u9009\u62E9\u5206\u8FA8\u7387", L"\u7533\u8BF7", L"\u53D6\u6D88", L"\u9009\u62E9\u4E00\u4E2A\u89D2\u8272", L"\u56DE\u53BB", L"\u6C34\u5973\u5B69", L"\u706B\u5973\u5B69", L"\u51FA\u53E3", L"\u91CD\u8BD5", L"\u6E38\u620F\u7ED3\u675F\uFF01", L"\u9000\u51FA\u6E38\u620F", L"\u5206\u6570", L"\u6740\u6B7B\u7684\u654C\u4EBA\uFF1A", L"\u9636\u6BB5\uFF1A", L"\u6b8b\u654c\u0020\u003a\u0020",L"\u5269\u4F59\u654C\u4EBA\uFF1A", L"\u6700\u9ad8\u5206\u003a\u0020"}; /**< Array of Mandarin strings. */
    }lang; /**< Instance of the languages class. */

    /**
     * @brief Check if a point (mouse position) is inside a convex shape (button).
     *
     * This helper function checks if a given point (mouse position) is inside the boundaries of a convex shape (button).
     *
     * @param button The convex shape representing the button.
     * @param mousePosition The position of the mouse pointer.
     * @return true if the mouse position is inside the button, false otherwise.
     */
    bool isButtonPressed(const sf::ConvexShape& button, const sf::Vector2f& mousePosition);

    /**
     * @brief Check if a point (mouse position) is inside a rectangle shape (button).
     *
     * This helper function checks if a given point (mouse position) is inside the boundaries of a rectangle shape (button).
     *
     * @param button The rectangle shape representing the button.
     * @param mousePosition The position of the mouse pointer.
     * @return true if the mouse position is inside the button, false otherwise.
     */
    bool isButtonPressed(const sf::RectangleShape& button, const sf::Vector2f& mousePosition);

    /**
     * @brief Create a parallelogram shape with the specified dimensions.
     *
     * This helper function creates a parallelogram shape with the specified width and height.
     *
     * @param width The width of the parallelogram.
     * @param height The height of the parallelogram.
     * @return An sf::ConvexShape object representing the parallelogram.
     */
    sf::ConvexShape createParallelogram(float width, float height);

    /**
     * @brief Create a rectangle shape with the specified dimensions.
     *
     * This helper function creates a rectangle shape with the specified width and height,
     * and sets its fill color to a predefined color.
     *
     * @param width The width of the rectangle.
     * @param height The height of the rectangle.
     * @return An sf::RectangleShape object representing the rectangle.
     */
    sf::RectangleShape createRectangle(float width, float height);
};

#endif //FIRE_FIGHTER_SETTINGS_H
