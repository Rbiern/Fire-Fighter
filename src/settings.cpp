#include "settings.h"

/** constructor */
settings::settings() {
    // Open the file
    std::ifstream file("../../config/settings.txt");
    char idx = 0;
    // Check if the file is open
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file." << std::endl;
        return; // Return error code
    }
    // Read and print each line of the file
    std::string line;
    while (std::getline(file, line)) {
        int number = std::stoi(line, nullptr, 2); // Convert the line to an integer
        array[idx++] = number;
    }
    // Close the file
    file.close();
    fullscreen = array[0];
    resolution = array[1] == 1 ? res.dv : array[1] == 2 ? res.sd : array[1] == 3 ? res.hd : res.uhd;
    frameRate = array[2];
    rotation = array[3];
    music = array[4];
    soundEffects = array[5];
    language = array[6] == 1 ? lang.English : array[6] == 2 ? lang.Korean : lang.Mandarin;
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
    if (!icon.loadFromFile("../../resource/img/icon.png")) {
        std::cerr << "Failed to load icon" << std::endl;
        return;
    }
}

/** Helper method for checking if the parallelogram button is pressed */
bool settings::isButtonPressed(const sf::ConvexShape& button, const sf::Vector2f& mousePosition) {
    sf::FloatRect buttonBounds = button.getGlobalBounds();
    return buttonBounds.contains(mousePosition);
}

/** Helper method for checking if the rectangle button is pressed */
bool settings::isButtonPressed(const sf::RectangleShape& button, const sf::Vector2f& mousePosition) {
    sf::FloatRect buttonBounds = button.getGlobalBounds();
    return buttonBounds.contains(mousePosition);
}

/** Helper method to create a parallelogram shape */
sf::ConvexShape settings::createParallelogram(float width, float height) {
    sf::ConvexShape parallelogram;
    parallelogram.setPointCount(4);
    parallelogram.setPoint(0, sf::Vector2f(0, 0));
    parallelogram.setPoint(1, sf::Vector2f(width, 0));
    parallelogram.setPoint(2, sf::Vector2f(width * 0.8f, height));
    parallelogram.setPoint(3, sf::Vector2f(-width * 0.2f, height));
    parallelogram.setFillColor(sf::Color::Transparent);
    parallelogram.setOutlineThickness(2);
    parallelogram.setOutlineColor(sf::Color::White);
    return parallelogram;
}

/** Helper method to create a rectangle shape */
sf::RectangleShape settings::createRectangle(float width, float height) {
    sf::RectangleShape button(sf::Vector2f(width, height));
    button.setFillColor(sf::Color(54, 207, 213));
    button.setOutlineThickness(2);
    button.setOutlineColor(sf::Color::White);
    return button;
}

/** main settings window loop */
void settings::openSettings(int w, int h) {
    // Create the SFML window
    sf::VideoMode fullScreenMode = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(fullscreen ? fullScreenMode : sf::VideoMode(resolution[0], resolution[1]), "Fire Fighter", fullscreen || resolution[0] >= fullScreenMode.width ? sf::Style::Fullscreen : sf::Style::Default);
    window.setFramerateLimit(60); // Limit the frame rate to 60 FPS
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr()); // Set the window icon

    // languages
    sf::String s9 = language[9];
    sf::Text buttonText(s9, font, 20);
    buttonText.setFillColor(sf::Color::White);
    buttonText.setStyle(sf::Text::Bold);
    // for res
    sf::String s10 = language[10];
    sf::Text buttonText2(s10, font, 20);
    buttonText2.setFillColor(sf::Color::White);
    buttonText2.setStyle(sf::Text::Bold);

    // Create parallelogram buttons
    sf::ConvexShape English;
    sf::ConvexShape korean;
    sf::ConvexShape Mandarin;
    sf::ConvexShape dv;
    sf::ConvexShape sd;
    sf::ConvexShape hd;
    sf::ConvexShape uhd;

    // Get the current window size
    float screenWidth = window.getSize().x;
    float screenHeight = window.getSize().y;
    // setup dimensions and count for resolution buttons
    float buttonWidth = (screenWidth / 3) * 0.8f;
    float buttonHeight = (screenHeight / 4) * 0.5f;
    float totalButtonWidth = buttonWidth * 3;
    // create languages button shape
    English = createParallelogram(buttonWidth, buttonHeight);
    korean = createParallelogram(buttonWidth, buttonHeight);
    Mandarin = createParallelogram(buttonWidth, buttonHeight);
    // set position of languages button on where to draw it
    English.setPosition((screenWidth - totalButtonWidth) / 2, screenHeight / 2 - buttonHeight / 2);
    korean.setPosition(English.getPosition().x + buttonWidth, screenHeight / 2 - buttonHeight / 2);
    Mandarin.setPosition(korean.getPosition().x + buttonWidth, screenHeight / 2 - buttonHeight / 2);
    // place languages text on top of button
    buttonText.setPosition(korean.getPosition().x + (buttonWidth - buttonText.getLocalBounds().width) / 2, korean.getPosition().y - 30);

    // setup dimensions and count for resolution buttons
    buttonWidth = (screenWidth / 4) * 0.8f;
    buttonHeight = (screenHeight / 4) * 0.5f;
    totalButtonWidth = buttonWidth * 4;
    // create resolution button shape
    dv = createParallelogram(buttonWidth, buttonHeight);
    sd = createParallelogram(buttonWidth, buttonHeight);
    hd = createParallelogram(buttonWidth, buttonHeight);
    uhd = createParallelogram(buttonWidth, buttonHeight);
    // set position of resolution button on where to draw it
    dv.setPosition((screenWidth - totalButtonWidth) / 2, screenHeight * 0.75 - buttonHeight / 2);
    sd.setPosition(dv.getPosition().x + buttonWidth, screenHeight * 0.75 - buttonHeight / 2);
    hd.setPosition(sd.getPosition().x + buttonWidth, screenHeight * 0.75 - buttonHeight / 2);
    uhd.setPosition(hd.getPosition().x + buttonWidth, screenHeight * 0.75 - buttonHeight / 2);
    // place resolution text on top of button
    buttonText2.setPosition((screenWidth / 2) - buttonWidth / 2, sd.getPosition().y - 30);

    // create colors for the buttons
    sf::Color normalColor = sf::Color(54, 207, 213);
    sf::Color pressedColor = sf::Color::Yellow;
    // setup language button colors
    English.setFillColor(normalColor);
    korean.setFillColor(normalColor);
    Mandarin.setFillColor(normalColor);
    if (language[0] == "NEW GAME") {
        English.setFillColor(pressedColor);
    } else if (language[0] == L"\uC0C8 \uAC8C\uC784") {
        korean.setFillColor(pressedColor);
    } else {
        Mandarin.setFillColor(pressedColor);
    }
    // setup resolution button colors
    dv.setFillColor(normalColor);
    sd.setFillColor(normalColor);
    hd.setFillColor(normalColor);
    uhd.setFillColor(normalColor);
    if (resolution[0] == 640) {
        dv.setFillColor(pressedColor);
    } else if (resolution[0] == 1280) {
        sd.setFillColor(pressedColor);
    } else if (resolution[0] == 1920) {
        hd.setFillColor(pressedColor);
    } else {
        uhd.setFillColor(pressedColor);
    }

    // Create language buttons text with color RGB(235, 70, 60)
    sf::Text englishText("English", font, 20);
    englishText.setPosition(English.getPosition().x + 20, English.getPosition().y + 10); // Adjusting position of text
    englishText.setFillColor(sf::Color(235, 70, 60)); // Setting text color

    sf::Text koreanText("Korean", font, 20);
    koreanText.setPosition(korean.getPosition().x + 20, korean.getPosition().y + 10); // Adjusting position of text
    koreanText.setFillColor(sf::Color(235, 70, 60)); // Setting text color

    sf::Text mandarinText("Mandarin", font, 20);
    mandarinText.setPosition(Mandarin.getPosition().x + 20, Mandarin.getPosition().y + 10); // Adjusting position of text
    mandarinText.setFillColor(sf::Color(235, 70, 60)); // Setting text color

    sf::Text dvText("640:360", font, 20);
    dvText.setPosition(dv.getPosition().x + 20, dv.getPosition().y + 10); // Adjusting position of text
    dvText.setFillColor(sf::Color(235, 70, 60)); // Setting text color

    sf::Text sdText("1280:720", font, 20);
    sdText.setPosition(sd.getPosition().x + 16, sd.getPosition().y + 10); // Adjusting position of text
    sdText.setFillColor(sf::Color(235, 70, 60)); // Setting text color

    sf::Text hdText("1920:1080", font, 20);
    hdText.setPosition(hd.getPosition().x + 11, hd.getPosition().y + 10); // Adjusting position of text
    hdText.setFillColor(sf::Color(235, 70, 60)); // Setting text color

    sf::Text uhdText("3840:2160", font, 20);
    uhdText.setPosition(uhd.getPosition().x + 5, uhd.getPosition().y + 10); // Adjusting position of text
    uhdText.setFillColor(sf::Color(235, 70, 60)); // Setting text color

    // Create rectangle buttons
    sf::RectangleShape FullscreenButton = createRectangle(100, 50);
    sf::RectangleShape musicButton = createRectangle(100, 50);
    sf::RectangleShape soundEffectsButton = createRectangle(100, 50);
    sf::RectangleShape rotationButton = createRectangle(100, 50);

    // Set initial button position
    float buttonSpacing = 20.0f;
    totalButtonWidth = (FullscreenButton.getSize().x + buttonSpacing) * 4 - buttonSpacing;
    float startX = (window.getSize().x - totalButtonWidth) / 2;
    float startY = screenHeight * 0.21f;

    FullscreenButton.setPosition(startX, startY);
    musicButton.setPosition(startX + FullscreenButton.getSize().x + buttonSpacing, startY);
    soundEffectsButton.setPosition(startX + (musicButton.getSize().x + buttonSpacing) * 2, startY);
    rotationButton.setPosition(startX + (soundEffectsButton.getSize().x + buttonSpacing) * 3, startY);

    sf::String s1 = language[3];
    sf::Text text10(s1, font, 20);
    sf::String s2 = language[4];
    sf::Text text11(s2, font, 20);
    sf::String s3 = language[5];
    sf::Text text12(s3, font, 20);
    sf::String s4 = language[6];
    sf::Text text13(s4, font, 20);
    sf::String s5 = language[7];
    sf::String s6 = language[8];
    sf::Text text14(fullscreen ? s5 : s6, font, 20);
    text14.setFillColor(sf::Color(235, 70, 60));
    sf::Text text15(music ? s5 : s6, font, 20);
    text15.setFillColor(sf::Color(235, 70, 60));
    sf::Text text16(soundEffects ? s5 : s6, font, 20);
    text16.setFillColor(sf::Color(235, 70, 60));
    sf::Text text17(rotation ? s5 : s6, font, 20);
    text17.setFillColor(sf::Color(235, 70, 60));

    // Set position for text
    float textOffsetX = 10.0f; // Offset from the button's left edge
    float textOffsetY = 15.0f; // Offset from the button's top edge

    text14.setPosition(FullscreenButton.getPosition().x + textOffsetX, FullscreenButton.getPosition().y + textOffsetY);
    text15.setPosition(musicButton.getPosition().x + textOffsetX, musicButton.getPosition().y + textOffsetY);
    text16.setPosition(soundEffectsButton.getPosition().x + textOffsetX, soundEffectsButton.getPosition().y + textOffsetY);
    text17.setPosition(rotationButton.getPosition().x + textOffsetX, rotationButton.getPosition().y + textOffsetY);

    text10.setPosition(FullscreenButton.getPosition().x + textOffsetX, FullscreenButton.getPosition().y - textOffsetY * 1.8);
    text11.setPosition(musicButton.getPosition().x + textOffsetX + 13, musicButton.getPosition().y - textOffsetY * 1.8);
    text12.setPosition(soundEffectsButton.getPosition().x + textOffsetX - 15, soundEffectsButton.getPosition().y - textOffsetY * 1.8);
    text13.setPosition(rotationButton.getPosition().x + textOffsetX, rotationButton.getPosition().y - textOffsetY * 1.8);


    // Create square buttons
    sf::RectangleShape applyButton = createRectangle(70, 40);
    sf::RectangleShape cancelButton = createRectangle(70,40);

    // Set initial button position
    buttonSpacing = 20.0f;
    totalButtonWidth = applyButton.getSize().x * 2 + buttonSpacing;
    startX = (window.getSize().x - totalButtonWidth) / 2;
    startY = window.getSize().y - 50.0f;

    applyButton.setPosition(startX, startY);
    cancelButton.setPosition(startX + applyButton.getSize().x + buttonSpacing, startY);

    sf::String s11 = language[11];
    sf::Text applyText(s11, font, 20);
    applyButton.setFillColor(sf::Color::Green);
    sf::String s12 = language[12];
    sf::Text cancelText(s12, font, 20);
    cancelButton.setFillColor(sf::Color(235, 70, 60));

    // Set position for text
    textOffsetX = 13.0f;
    textOffsetY = 6.0f;
    applyText.setPosition(applyButton.getPosition().x + textOffsetX, applyButton.getPosition().y + textOffsetY);
    cancelText.setPosition(cancelButton.getPosition().x + textOffsetX, cancelButton.getPosition().y + textOffsetY);

    // Main loop
    while (window.isOpen()) {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(window));
                if (isButtonPressed(FullscreenButton, mousePosition)) {
                    std::cout << "Button 10 Pressed!" << std::endl;
                    fullscreen = !fullscreen;
                    text14.setString(fullscreen ? s5 : s6);
                } else if (isButtonPressed(musicButton, mousePosition)) {
                    std::cout << "Button 11 Pressed!" << std::endl;
                    music = !music;
                    text15.setString(music ? s5 : s6);
                } else if (isButtonPressed(soundEffectsButton, mousePosition)) {
                    std::cout << "Button 12 Pressed!" << std::endl;
                    soundEffects = !soundEffects;
                    text16.setString(soundEffects ? s5 : s6);
                } else if (isButtonPressed(rotationButton, mousePosition)) {
                    std::cout << "Button 13 Pressed!" << std::endl;
                    rotation = !rotation;
                    text17.setString(rotation ? s5 : s6);
                } else if (isButtonPressed(English, mousePosition)) {
                    std::cout << "Button 1 Pressed!" << std::endl;
                    English.setFillColor(pressedColor);
                    korean.setFillColor(normalColor);
                    Mandarin.setFillColor(normalColor);
                    language = lang.English;
                } else if (isButtonPressed(korean, mousePosition)) {
                    std::cout << "Button 2 Pressed!" << std::endl;
                    English.setFillColor(normalColor);
                    korean.setFillColor(pressedColor);
                    Mandarin.setFillColor(normalColor);
                    language = lang.Korean;
                } else if (isButtonPressed(Mandarin, mousePosition)) {
                    std::cout << "Button 3 Pressed!" << std::endl;
                    English.setFillColor(normalColor);
                    korean.setFillColor(normalColor);
                    Mandarin.setFillColor(pressedColor);
                    language = lang.Mandarin;
                } else if (isButtonPressed(dv, mousePosition)) {
                    std::cout << "Button 4 Pressed!" << std::endl;
                    dv.setFillColor(pressedColor);
                    sd.setFillColor(normalColor);
                    hd.setFillColor(normalColor);
                    uhd.setFillColor(normalColor);
                    resolution = res.dv;
                } else if (isButtonPressed(sd, mousePosition)) {
                    std::cout << "Button 5 Pressed!" << std::endl;
                    dv.setFillColor(normalColor);
                    sd.setFillColor(pressedColor);
                    hd.setFillColor(normalColor);
                    uhd.setFillColor(normalColor);
                    resolution = res.sd;
                } else if (isButtonPressed(hd, mousePosition)) {
                    std::cout << "Button 6 Pressed!" << std::endl;
                    dv.setFillColor(normalColor);
                    sd.setFillColor(normalColor);
                    hd.setFillColor(pressedColor);
                    uhd.setFillColor(normalColor);
                    resolution = res.hd;
                } else if (isButtonPressed(uhd, mousePosition)) {
                    std::cout << "Button 7 Pressed!" << std::endl;
                    dv.setFillColor(normalColor);
                    sd.setFillColor(normalColor);
                    hd.setFillColor(normalColor);
                    uhd.setFillColor(pressedColor);
                    resolution = res.uhd;
                } else if (isButtonPressed(applyButton, mousePosition)) {
                    array[0] = (fullscreen) ? 1 : 0;
                    array[1] = resolution == res.dv ? 1 : resolution == res.sd ? 2 : resolution == res.hd ? 3 : 4;
                    array[2] = frameRate;
                    array[3] = rotation;
                    array[4] = (music) ? 1 : 0;
                    array[5] = (soundEffects) ? 1 : 0;
                    array[6] = language == lang.English ? 1 : language == lang.Korean ? 2 : 3;
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
                        // Convert the integer to a string
                        std::string binaryString = std::bitset<8>(array[i]).to_string();
                        binaryString = binaryString.substr(0);
                        // Write the binary string to the file followed by a new line
                        file << binaryString << '\n';
                    }
                    file.close(); // Close the file

                    window.close(); // Close the window if exit button is pressed
                } else if (isButtonPressed(cancelButton, mousePosition)) {
                    fullscreen = array[0];
                    resolution = array[1] == 1 ? res.dv : array[1] == 2 ? res.sd : array[1] == 3 ? res.hd : res.uhd;
                    frameRate = array[2];
                    rotation = array[3];
                    music = array[4];
                    soundEffects = array[5];
                    language = array[6] == 1 ? lang.English : array[6] == 2 ? lang.Korean : lang.Mandarin;
                    window.close(); // Close the window if exit button is pressed
                }
            }
        }

        // Clear the window
        window.clear(sf::Color(52, 109, 129));

        // Draw buttons
        window.draw(English);
        window.draw(korean);
        window.draw(Mandarin);


        window.draw(dv);
        window.draw(sd);
        window.draw(hd);
        window.draw(uhd);


        // top buttons
        window.draw(FullscreenButton);
        window.draw(musicButton);
        window.draw(soundEffectsButton);
        window.draw(rotationButton);

        // Draw text
        window.draw(buttonText);
        window.draw(buttonText2);
        window.draw(englishText);
        window.draw(koreanText);
        window.draw(mandarinText);

        //top text for button
        window.draw(text10);
        window.draw(text11);
        window.draw(text12);
        window.draw(text13);

        window.draw(text14);
        window.draw(text15);
        window.draw(text16);
        window.draw(text17);

        window.draw(dvText);
        window.draw(sdText);
        window.draw(hdText);
        window.draw(uhdText);

        // Draw buttons
        window.draw(applyButton);
        window.draw(cancelButton);
        // Draw text
        window.draw(applyText);
        window.draw(cancelText);

        // Display content
        window.display();
    }
}

int *settings::getResolution() {
    return resolution;
}

sf::String * settings::getLanguage() {
    return language;
}

bool settings::toggleMusic() const {
    return music;
}

bool settings::isFullScreen() const {
    return fullscreen;
}

sf::Font settings::getFont() {
    return font;
}

sf::Image settings::getIcon() {
    return icon;
}

bool settings::toggleSounds() const {
    return soundEffects;
}
