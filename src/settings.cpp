#include "settings.h"

/**
 * Constructor of a Settings object.
 */
Settings::Settings() {
    std::ifstream file("../../config/settings.txt");             // Open the file
    char idx = 0;
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file." << std::endl;    // Check if the file is open
        return;
    }
    // Read and print each line of the file
    std::string line;
    while (std::getline(file, line)) {
        int number = std::stoi(line, nullptr, 2);     // Convert the line to an integer
        dataFromFile[idx++] = number;   // Assign the value to the data array
    }
    file.close();

    // Assign settings variables based on the values read from the file
    fullscreen = dataFromFile[0];
    resolution = dataFromFile[1] == 1 ? res.dv : dataFromFile[1] == 2 ? res.sd : dataFromFile[1] == 3 ? res.hd : res.uhd;
    frameRate = dataFromFile[2];
    rotation = dataFromFile[3];
    music = dataFromFile[4];
    soundEffects = dataFromFile[5];
    language = dataFromFile[6] == 1 ? lang.English : dataFromFile[6] == 2 ? lang.Korean : lang.Mandarin;

    // Load the appropriate font based on the selected language
    if (language[0] == L"\uC0C8 \uAC8C\uC784") {
        if (!font.loadFromFile("../../resource/fonts/NanumMyeongjoBold.ttf")) {
            std::cerr << "Failed to load Korean font!" << std::endl;   // Print error message if Korean font loading fails
        }
    } else if (language[0] == L"\u65B0\u6E38\u620F") {
        if (!font.loadFromFile("../../resource/fonts/simplified_Chinese.ttf")) {
            std::cerr << "Failed to load Chinese font!" << std::endl;    // Print error message if Chinese font loading fails
        }
    } else {
        if (!font.loadFromFile("../../resource/fonts/Rajdhani-SemiBold.ttf")) {
            std::cerr << "Failed to load English font!" << std::endl;   // Print error message if English font loading fails
        }
    }

    // Load the application icon
    if (!icon.loadFromFile("../../resource/img/icon.png")) {
        std::cerr << "Failed to load icon" << std::endl;  // Print error message
    }
}

/**
 * Destructor of a Settings class.
 */
Settings::~Settings() = default;

/**
 * Open a Settings window loop where the player can adjust various game settings.
 */
void Settings::openSettings() {
    // Create the window
    sf::VideoMode fullScreenMode = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(fullscreen ? fullScreenMode : sf::VideoMode(resolution[0], resolution[1]), "Fire Fighter", fullscreen || resolution[0] >= fullScreenMode.width ? sf::Style::Fullscreen : sf::Style::Default);
    window.setFramerateLimit(60); // Limit the frame rate to 60 FPS
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr()); // Set the window icon

    // create text for languages to display on top of the buttons
    sf::String selectLanguagesString = language[9];
    sf::Text selectLanguagesText(selectLanguagesString, font, 20);
    selectLanguagesText.setFillColor(sf::Color::White);
    selectLanguagesText.setStyle(sf::Text::Bold);

    // create text for resolution to display on top of the buttons
    sf::String selectResolutionString = language[10];
    sf::Text selectResolutionText(selectResolutionString, font, 20);
    selectResolutionText.setFillColor(sf::Color::White);
    selectResolutionText.setStyle(sf::Text::Bold);

    // Get the current window size
    float screenWidth = window.getSize().x;
    float screenHeight = window.getSize().y;

    // setup dimensions and count for languages buttons
    float buttonWidth = (screenWidth / 3) * 0.8f;
    float buttonHeight = (screenHeight / 4) * 0.5f;
    float totalButtonWidth = buttonWidth * 3;

    // create parallelogram languages buttons
    sf::ConvexShape EnglishButton = createParallelogram(buttonWidth, buttonHeight);
    sf::ConvexShape koreanButton = createParallelogram(buttonWidth, buttonHeight);
    sf::ConvexShape MandarinButton = createParallelogram(buttonWidth, buttonHeight);

    // set position of languages button on where to draw it
    EnglishButton.setPosition((screenWidth - totalButtonWidth) / 2, screenHeight / 2 - buttonHeight / 2);
    koreanButton.setPosition(EnglishButton.getPosition().x + buttonWidth, screenHeight / 2 - buttonHeight / 2);
    MandarinButton.setPosition(koreanButton.getPosition().x + buttonWidth, screenHeight / 2 - buttonHeight / 2);
    // place select languages text top center of all languages buttons
    selectLanguagesText.setPosition(koreanButton.getPosition().x + (buttonWidth - selectLanguagesText.getLocalBounds().width) / 2, koreanButton.getPosition().y - 30);

    // setup dimensions and count for resolution buttons
    buttonWidth = (screenWidth / 4) * 0.8f;
    buttonHeight = (screenHeight / 4) * 0.5f;
    totalButtonWidth = buttonWidth * 4;

    // create parallelogram resolutions buttons
    sf::ConvexShape dvButton = createParallelogram(buttonWidth, buttonHeight);
    sf::ConvexShape sdButton = createParallelogram(buttonWidth, buttonHeight);
    sf::ConvexShape hdButton = createParallelogram(buttonWidth, buttonHeight);
    sf::ConvexShape uhdButton = createParallelogram(buttonWidth, buttonHeight);

    // set position of resolution button on where to draw it
    dvButton.setPosition((screenWidth - totalButtonWidth) / 2, screenHeight * 0.75 - buttonHeight / 2);
    sdButton.setPosition(dvButton.getPosition().x + buttonWidth, screenHeight * 0.75 - buttonHeight / 2);
    hdButton.setPosition(sdButton.getPosition().x + buttonWidth, screenHeight * 0.75 - buttonHeight / 2);
    uhdButton.setPosition(hdButton.getPosition().x + buttonWidth, screenHeight * 0.75 - buttonHeight / 2);

    // place select resolution text top center of all resolution buttons
    selectResolutionText.setPosition((screenWidth / 2) - buttonWidth / 2, sdButton.getPosition().y - 30);

    // create two different colors for the buttons based of weather or not they are selected or not
    sf::Color normalColor = sf::Color(54, 207, 213);
    sf::Color pressedColor = sf::Color::Yellow;

    // setup language button colors
    EnglishButton.setFillColor(normalColor);
    koreanButton.setFillColor(normalColor);
    MandarinButton.setFillColor(normalColor);
    if (language[0] == "NEW GAME") {
        EnglishButton.setFillColor(pressedColor);
    } else if (language[0] == L"\uC0C8 \uAC8C\uC784") {
        koreanButton.setFillColor(pressedColor);
    } else {
        MandarinButton.setFillColor(pressedColor);
    }

    // setup resolution button colors
    dvButton.setFillColor(normalColor);
    sdButton.setFillColor(normalColor);
    hdButton.setFillColor(normalColor);
    uhdButton.setFillColor(normalColor);
    if (resolution[0] == 640) {
        dvButton.setFillColor(pressedColor);
    } else if (resolution[0] == 1280) {
        sdButton.setFillColor(pressedColor);
    } else if (resolution[0] == 1920) {
        hdButton.setFillColor(pressedColor);
    } else {
        uhdButton.setFillColor(pressedColor);
    }

    // Adjusting the position and creating text for language buttons. Colors set to RGB(235, 70, 60)
    sf::Text englishText("English", font, 20);
    englishText.setPosition(EnglishButton.getPosition().x + 20, EnglishButton.getPosition().y + 10);
    englishText.setFillColor(sf::Color(235, 70, 60));

    sf::Text koreanText("Korean", font, 20);
    koreanText.setPosition(koreanButton.getPosition().x + 20, koreanButton.getPosition().y + 10);
    koreanText.setFillColor(sf::Color(235, 70, 60));

    sf::Text mandarinText("Mandarin", font, 20);
    mandarinText.setPosition(MandarinButton.getPosition().x + 20, MandarinButton.getPosition().y + 10);
    mandarinText.setFillColor(sf::Color(235, 70, 60));

    // Adjusting the position and creating text for resolution buttons. Colors set to RGB(235, 70, 60)
    sf::Text dvText("640:360", font, 20);
    dvText.setPosition(dvButton.getPosition().x + 20, dvButton.getPosition().y + 10);
    dvText.setFillColor(sf::Color(235, 70, 60));

    sf::Text sdText("1280:720", font, 20);
    sdText.setPosition(sdButton.getPosition().x + 16, sdButton.getPosition().y + 10);
    sdText.setFillColor(sf::Color(235, 70, 60));

    sf::Text hdText("1920:1080", font, 20);
    hdText.setPosition(hdButton.getPosition().x + 11, hdButton.getPosition().y + 10);
    hdText.setFillColor(sf::Color(235, 70, 60));

    sf::Text uhdText("3840:2160", font, 20);
    uhdText.setPosition(uhdButton.getPosition().x + 5, uhdButton.getPosition().y + 10);
    uhdText.setFillColor(sf::Color(235, 70, 60));

    // Create rectangle buttons
    sf::RectangleShape fullscreenButton = createRectangle(100, 50);
    sf::RectangleShape musicButton = createRectangle(100, 50);
    sf::RectangleShape soundEffectsButton = createRectangle(100, 50);
    sf::RectangleShape rotationButton = createRectangle(100, 50);

    // Set initial button position
    float buttonSpacing = 20.0f;
    totalButtonWidth = (fullscreenButton.getSize().x + buttonSpacing) * 4 - buttonSpacing;
    float startX = (window.getSize().x - totalButtonWidth) / 2;
    float startY = screenHeight * 0.21f;

    // set button positions
    fullscreenButton.setPosition(startX, startY);
    musicButton.setPosition(startX + fullscreenButton.getSize().x + buttonSpacing, startY);
    soundEffectsButton.setPosition(startX + (musicButton.getSize().x + buttonSpacing) * 2, startY);
    rotationButton.setPosition(startX + (soundEffectsButton.getSize().x + buttonSpacing) * 3, startY);

    sf::String fullscreenString = language[3];
    sf::Text fullscreenText(fullscreenString, font, 20);
    sf::String musicString = language[4];
    sf::Text musicText(musicString, font, 20);
    sf::String soundEffectsString = language[5];
    sf::Text soundEffectsText(soundEffectsString, font, 20);
    sf::String rotationString = language[6];
    sf::Text rotationText(rotationString, font, 20);
    sf::String onString = language[7];
    sf::String offString = language[8];
    sf::Text screenOnOffText(fullscreen ? onString : offString, font, 20);
    screenOnOffText.setFillColor(sf::Color(235, 70, 60));
    sf::Text musicOnOffText(music ? onString : offString, font, 20);
    musicOnOffText.setFillColor(sf::Color(235, 70, 60));
    sf::Text soundOnOffText(soundEffects ? onString : offString, font, 20);
    soundOnOffText.setFillColor(sf::Color(235, 70, 60));
    sf::Text rotationOnOffText(rotation ? onString : offString, font, 20);
    rotationOnOffText.setFillColor(sf::Color(235, 70, 60));

    // Set position for text
    float textOffsetX = 10.0f; // Offset from the button's left edge
    float textOffsetY = 15.0f; // Offset from the button's top edge

    screenOnOffText.setPosition(fullscreenButton.getPosition().x + textOffsetX, fullscreenButton.getPosition().y + textOffsetY);
    musicOnOffText.setPosition(musicButton.getPosition().x + textOffsetX, musicButton.getPosition().y + textOffsetY);
    soundOnOffText.setPosition(soundEffectsButton.getPosition().x + textOffsetX, soundEffectsButton.getPosition().y + textOffsetY);
    rotationOnOffText.setPosition(rotationButton.getPosition().x + textOffsetX, rotationButton.getPosition().y + textOffsetY);

    fullscreenText.setPosition(fullscreenButton.getPosition().x + textOffsetX, fullscreenButton.getPosition().y - textOffsetY * 1.8);
    musicText.setPosition(musicButton.getPosition().x + textOffsetX + 13, musicButton.getPosition().y - textOffsetY * 1.8);
    soundEffectsText.setPosition(soundEffectsButton.getPosition().x + textOffsetX - 15, soundEffectsButton.getPosition().y - textOffsetY * 1.8);
    rotationText.setPosition(rotationButton.getPosition().x + textOffsetX, rotationButton.getPosition().y - textOffsetY * 1.8);

    // Create square buttons
    sf::RectangleShape applyButton = createRectangle(70, 40);
    sf::RectangleShape cancelButton = createRectangle(70,40);

    // Set initial button position for cancel and apply
    buttonSpacing = 20.0f;
    totalButtonWidth = applyButton.getSize().x * 2 + buttonSpacing;
    startX = (window.getSize().x - totalButtonWidth) / 2;
    startY = window.getSize().y - 50.0f;

    applyButton.setPosition(startX, startY);
    cancelButton.setPosition(startX + applyButton.getSize().x + buttonSpacing, startY);

    sf::String applyString = language[11];
    sf::Text applyText(applyString, font, 20);
    applyButton.setFillColor(sf::Color::Green);
    sf::String cancelString = language[12];
    sf::Text cancelText(cancelString, font, 20);
    cancelButton.setFillColor(sf::Color(235, 70, 60));

    // Set position apply and cancel text
    textOffsetX = 13.0f;
    textOffsetY = 6.0f;
    applyText.setPosition(applyButton.getPosition().x + textOffsetX, applyButton.getPosition().y + textOffsetY);
    cancelText.setPosition(cancelButton.getPosition().x + textOffsetX, cancelButton.getPosition().y + textOffsetY);

    // settings window loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(window));
                if (isButtonPressed(fullscreenButton, mousePosition)) {
                    std::cout << "Fullscreen Button Pressed!" << std::endl;
                    fullscreen = !fullscreen;
                    screenOnOffText.setString(fullscreen ? onString : offString);
                } else if (isButtonPressed(musicButton, mousePosition)) {
                    std::cout << "Music Button Pressed!" << std::endl;
                    music = !music;
                    musicOnOffText.setString(music ? onString : offString);
                } else if (isButtonPressed(soundEffectsButton, mousePosition)) {
                    std::cout << "Sound Effects Button Pressed!" << std::endl;
                    soundEffects = !soundEffects;
                    soundOnOffText.setString(soundEffects ? onString : offString);
//                } else if (isButtonPressed(rotationButton, mousePosition)) {
//                    std::cout << "Rotation Button Pressed!" << std::endl;
//                    rotation = !rotation;
//                    rotationOnOffText.setString(rotation ? onString : offString);
                } else if (isButtonPressed(EnglishButton, mousePosition)) {
                    std::cout << "English Button Pressed!" << std::endl;
                    EnglishButton.setFillColor(pressedColor);
                    koreanButton.setFillColor(normalColor);
                    MandarinButton.setFillColor(normalColor);
                    language = lang.English;
                } else if (isButtonPressed(koreanButton, mousePosition)) {
                    std::cout << "Korean 2 Pressed!" << std::endl;
                    EnglishButton.setFillColor(normalColor);
                    koreanButton.setFillColor(pressedColor);
                    MandarinButton.setFillColor(normalColor);
                    language = lang.Korean;
                } else if (isButtonPressed(MandarinButton, mousePosition)) {
                    std::cout << "Mandarin Button Pressed!" << std::endl;
                    EnglishButton.setFillColor(normalColor);
                    koreanButton.setFillColor(normalColor);
                    MandarinButton.setFillColor(pressedColor);
                    language = lang.Mandarin;
                } else if (isButtonPressed(dvButton, mousePosition)) {
                    std::cout << "dv Button Pressed!" << std::endl;
                    dvButton.setFillColor(pressedColor);
                    sdButton.setFillColor(normalColor);
                    hdButton.setFillColor(normalColor);
                    uhdButton.setFillColor(normalColor);
                    resolution = res.dv;
                } else if (isButtonPressed(sdButton, mousePosition)) {
                    std::cout << "sd Button Pressed!" << std::endl;
                    dvButton.setFillColor(normalColor);
                    sdButton.setFillColor(pressedColor);
                    hdButton.setFillColor(normalColor);
                    uhdButton.setFillColor(normalColor);
                    resolution = res.sd;
                } else if (isButtonPressed(hdButton, mousePosition)) {
                    std::cout << "hd Button Pressed!" << std::endl;
                    dvButton.setFillColor(normalColor);
                    sdButton.setFillColor(normalColor);
                    hdButton.setFillColor(pressedColor);
                    uhdButton.setFillColor(normalColor);
                    resolution = res.hd;
                } else if (isButtonPressed(uhdButton, mousePosition)) {
                    std::cout << "uhd Button Pressed!" << std::endl;
                    dvButton.setFillColor(normalColor);
                    sdButton.setFillColor(normalColor);
                    hdButton.setFillColor(normalColor);
                    uhdButton.setFillColor(pressedColor);
                    resolution = res.uhd;
                } else if (isButtonPressed(applyButton, mousePosition)) {
                    dataFromFile[0] = (fullscreen) ? 1 : 0;
                    dataFromFile[1] = resolution == res.dv ? 1 : resolution == res.sd ? 2 : resolution == res.hd ? 3 : 4;
                    dataFromFile[2] = frameRate;
                    dataFromFile[3] = rotation;
                    dataFromFile[4] = (music) ? 1 : 0;
                    dataFromFile[5] = (soundEffects) ? 1 : 0;
                    dataFromFile[6] = language == lang.English ? 1 : language == lang.Korean ? 2 : 3;
                    if (language[0] == L"\uC0C8 \uAC8C\uC784") {
                        if (!font.loadFromFile("../../resource/fonts/NanumMyeongjoBold.ttf")) {
                            std::cerr << "Failed to load font!" << std::endl;
                            return;
                        }
                    } else if (language[0] == L"\u65B0\u6E38\u620F") {
                        if (!font.loadFromFile("../../resource/fonts/simplified_Chinese.ttf")) {
                            std::cerr << "Failed to load font!" << std::endl;
                            return;
                        }
                    } else {
                        if (!font.loadFromFile("../../resource/fonts/Rajdhani-SemiBold.ttf")) {
                            std::cerr << "Failed to load font!" << std::endl;
                            return;
                        }
                    }
                    // Open file in write mode, automatically overrides the file
                    std::ofstream file("../../config/settings.txt", std::ios::out);
                    if (!file) {
                        std::cerr << "Failed to open file for writing.\n";
                        return;
                    }
                    for (size_t i = 0; i < 7; ++i) {
                        // Convert the integer to a musicString
                        std::string binaryString = std::bitset<8>(dataFromFile[i]).to_string();
                        binaryString = binaryString.substr(0);
                        // Write the binary musicString to the file followed by a new line
                        file << binaryString << '\n';
                    }
                    file.close(); // Close the file

                    window.close(); // Close the window if exit button is pressed
                } else if (isButtonPressed(cancelButton, mousePosition)) {
                    fullscreen = dataFromFile[0];
                    resolution = dataFromFile[1] == 1 ? res.dv : dataFromFile[1] == 2 ? res.sd : dataFromFile[1] == 3 ? res.hd : res.uhd;
                    frameRate = dataFromFile[2];
                    rotation = dataFromFile[3];
                    music = dataFromFile[4];
                    soundEffects = dataFromFile[5];
                    language = dataFromFile[6] == 1 ? lang.English : dataFromFile[6] == 2 ? lang.Korean : lang.Mandarin;
                    window.close(); // Close the window if exit button is pressed
                }
            }
        }
        // Clear the window with blue backround
        window.clear(sf::Color(52, 109, 129));
        window.draw(EnglishButton);
        window.draw(koreanButton);
        window.draw(MandarinButton);
        window.draw(dvButton);
        window.draw(sdButton);
        window.draw(hdButton);
        window.draw(uhdButton);
        window.draw(fullscreenButton);
        window.draw(musicButton);
        window.draw(soundEffectsButton);
//        window.draw(rotationButton);
        window.draw(selectLanguagesText);
        window.draw(selectResolutionText);
        window.draw(englishText);
        window.draw(koreanText);
        window.draw(mandarinText);
        window.draw(fullscreenText);
        window.draw(musicText);
        window.draw(soundEffectsText);
//        window.draw(rotationText);
        window.draw(screenOnOffText);
        window.draw(musicOnOffText);
        window.draw(soundOnOffText);
//        window.draw(rotationOnOffText);
        window.draw(dvText);
        window.draw(sdText);
        window.draw(hdText);
        window.draw(uhdText);
        window.draw(applyButton);
        window.draw(cancelButton);
        window.draw(applyText);
        window.draw(cancelText);
        window.display();
    }
}

/**
 * Get the resolution settings.
 * @return resolution An array containing the resolution settings.
 */
int *Settings::getResolution() {
    return resolution;
}

/**
 * Get the language settings.
 * @return language An array containing the language settings.
 */
sf::String * Settings::getLanguage() {
    return language;
}

/**
 * Toggle the music setting.
 * @return bool True if music is enabled, false otherwise.
 */
bool Settings::toggleMusic() const {
    return music;
}

/**
 * Check if the application is running in fullscreen mode.
 * @return bool True if the application is in fullscreen mode, false otherwise.
 */
bool Settings::isFullScreen() const {
    return fullscreen;
}

/**
 * Get the font used for rendering text in the application.
 * @return sf::Font The font used for rendering text.
 */
sf::Font Settings::getFont() {
    return font;
}

/**
 * Get the icon used for the application window.
 * @return sf::Image The icon used for the application window.
 */
sf::Image Settings::getIcon() {
    return icon;
}

/**
 * Toggle the sound effects on or off.
 * @return bool True if sound effects are enabled, false otherwise.
 */
bool Settings::toggleSounds() const {
    return soundEffects;
}

/**
 * Scale a given value according to the width of the resolution.
 * @param x The value to be scaled.
 * @return float The scaled value.
 */
float Settings::widthScaling(float x) {
    return x * ((float)resolution[0]/1280.f);
}

/**
 * Scale a given value according to the height of the resolution.
 * @param y The value to be scaled.
 * @return float The scaled value.
 */
float Settings::heightScaling(float y) {
    return y * ((float)resolution[1]/720.f);
}

/**
 * Get the resolution as a sf::Vector2u object.
 * @return sf::Vector2u The resolution as a sf::Vector2u object.
 */
sf::Vector2u Settings::getVector() {
    sf::Vector2u vector(resolution[0], resolution[1]);
    return vector;
}

/**
 * Set a custom screen resolution.
 * @param x The width of the custom resolution.
 * @param y The height of the custom resolution.
 */
void Settings::userScreenInfo(int x, int y) {
    if (resolution[0] != x && resolution[1] != y) {
        res.uniqueRes[0] = x;
        res.uniqueRes[1] = y;
        resolution = res.uniqueRes;
    }
}

/**
 * Helper method to check if a point (mouse position) is inside a convex shape (button).
 * @param button The convex shape representing the button.
 * @param mousePosition The position of the mouse pointer.
 * @return true if the mouse position is inside the button, false otherwise.
 */
bool Settings::isButtonPressed(const sf::ConvexShape& button, const sf::Vector2f& mousePosition) {
    sf::FloatRect buttonBounds = button.getGlobalBounds();
    return buttonBounds.contains(mousePosition);
}


/**
 * Helper method to check if a point (mouse position) is inside a rectangle shape (button).
 * @param button The rectangle shape representing the button.
 * @param mousePosition The position of the mouse pointer.
 * @return true if the mouse position is inside the button, false otherwise.
 */
bool Settings::isButtonPressed(const sf::RectangleShape& button, const sf::Vector2f& mousePosition) {
    sf::FloatRect buttonBounds = button.getGlobalBounds();
    return buttonBounds.contains(mousePosition);
}

/**
 * Helper method to create a parallelogram shape with the specified dimensions.
 * @param width The width of the parallelogram.
 * @param height The height of the parallelogram.
 * @return An sf::ConvexShape object representing the parallelogram.
 */
sf::ConvexShape Settings::createParallelogram(float width, float height) {
    // Create a convex shape to represent the parallelogram
    sf::ConvexShape parallelogram;
    parallelogram.setPointCount(4); // Set the number of points to define the shape (4 for a parallelogram)
    parallelogram.setPoint(0, sf::Vector2f(0, 0)); // Define the first point at the top-left corner
    parallelogram.setPoint(1, sf::Vector2f(width, 0)); // Define the second point at the top-right corner
    parallelogram.setPoint(2, sf::Vector2f(width * 0.8f, height)); // Define the third point at the bottom-right corner
    parallelogram.setPoint(3, sf::Vector2f(-width * 0.2f, height)); // Define the fourth point at the bottom-left corner
    parallelogram.setFillColor(sf::Color::Transparent); // Set the fill color to transparent
    parallelogram.setOutlineThickness(2); // Set the thickness of the outline
    parallelogram.setOutlineColor(sf::Color::White); // Set the color of the outline
    return parallelogram; // Return the created parallelogram shape
}


/**
 * Helper method to create a rectangle shape with the specified dimensions.
 * @param width The width of the rectangle.
 * @param height The height of the rectangle.
 * @return An sf::RectangleShape object representing the rectangle.
 */
sf::RectangleShape Settings::createRectangle(float width, float height) {
    // Create a rectangle shape with the specified dimensions
    sf::RectangleShape button(sf::Vector2f(width, height));
    button.setFillColor(sf::Color(54, 207, 213)); // Set the fill color to a predefined color
    button.setOutlineThickness(2); // Set the thickness of the outline
    button.setOutlineColor(sf::Color::White); // Set the color of the outline
    return button; // Return the created rectangle shape
}
