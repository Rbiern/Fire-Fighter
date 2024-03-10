#include "settings.h"
#include <SFML/Graphics.hpp>
#include "ui.h"

settings *options = new settings();

settings::settings() {
    fullscreen = false;
    resolution = res.dv;
    frameRate = 60;
    rotation = 0;
    music = true;
    soundEffects = true;
    language = lang.English;
}

// Function to check if mouse is inside the parallelogram button
bool isButtonPressed(const sf::ConvexShape& button, const sf::Vector2f& mousePosition) {
    sf::FloatRect buttonBounds = button.getGlobalBounds();
    return buttonBounds.contains(mousePosition);
}

bool isButtonPressed(const sf::RectangleShape& button, const sf::Vector2f& mousePosition) {
    sf::FloatRect buttonBounds = button.getGlobalBounds();
    return buttonBounds.contains(mousePosition);
}

// Function to create a parallelogram shape
sf::ConvexShape createParallelogram(float width, float height) {
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

sf::RectangleShape createButton(float width, float height) {
    sf::RectangleShape button(sf::Vector2f(width, height));
    button.setFillColor(sf::Color(54, 207, 213));
    button.setOutlineThickness(2);
    button.setOutlineColor(sf::Color::White);
    return button;
}

/** main settings window loop */
void settings::openSettings(int w, int h) {
    // Create the SFML window

//        sf::VideoMode f = sf::VideoMode::getFullscreenModes()[0];
//        sf::RenderWindow window(sf::VideoMode(f), "Fixed Window", );

        sf::RenderWindow window(sf::VideoMode(w, h), "Fire Fighter", (h >= 1080) ? sf::Style::Fullscreen : NULL);

    window.setFramerateLimit(60); // Limit the frame rate to 60 FPS
    // Load Icon
    sf::Image icon;
    if (!icon.loadFromFile(R"(C:\Users\Pc MSI\CLionProjects\Fire Fighter\resource\img\icon.png)")) {
        std::cerr << "Failed to load icon" << std::endl;
        return;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr()); // Set the window icon
    // load fonts
    sf::Font font;
    if (!font.loadFromFile(R"(C:\Users\Pc MSI\CLionProjects\Fire Fighter\resource\fonts\Rajdhani-SemiBold.ttf)")) {
        std::cerr << "Failed to load font!" << std::endl;
        return;
    }

    // languages
    sf::Text buttonText("Select Languages", font, 20);
    buttonText.setFillColor(sf::Color::White);
    buttonText.setStyle(sf::Text::Bold);
    // for res
    sf::Text buttonText2("Select Resolution", font, 20);
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
    if (language = lang.English) {
        English.setFillColor(pressedColor);
    } else if (language = lang.Korean) {
        korean.setFillColor(pressedColor);
    } else if (language = lang.Mandarin) {
        Mandarin.setFillColor(pressedColor);
    }
    // setup resolution button colors
    dv.setFillColor(normalColor);
    sd.setFillColor(normalColor);
    hd.setFillColor(normalColor);
    uhd.setFillColor(normalColor);
    if (resolution = res.dv) {
        dv.setFillColor(pressedColor);
    } else if (resolution = res.sd) {
        sd.setFillColor(pressedColor);
    } else if (resolution = res.hd) {
        hd.setFillColor(pressedColor);
    } else if (resolution = res.uhd) {
        uhd.setFillColor(pressedColor);
    }

    //    // Create language buttons text with color RGB(235, 70, 60)
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
    sf::RectangleShape button8 = createButton(100, 50);
    sf::RectangleShape button9 = createButton(100, 50);
    sf::RectangleShape button10 = createButton(100, 50);
    sf::RectangleShape button11 = createButton(100, 50);

    // Set initial button position
    float buttonSpacing = 20.0f;
    totalButtonWidth = (button8.getSize().x + buttonSpacing) * 4 - buttonSpacing;
    float startX = (window.getSize().x - totalButtonWidth) / 2;
    float startY = screenHeight * 0.21f;

    button8.setPosition(startX, startY);
    button9.setPosition(startX + button8.getSize().x + buttonSpacing, startY);
    button10.setPosition(startX + (button9.getSize().x + buttonSpacing) * 2, startY);
    button11.setPosition(startX + (button10.getSize().x + buttonSpacing) * 3, startY);

    sf::Text text10("Fullscreen", font, 20);
//    text10.setFillColor(sf::Color(235, 70, 60));
    sf::Text text11("Music", font, 20);
//    text11.setFillColor(sf::Color(235, 70, 60));
    sf::Text text12("Sound Effects", font, 20);
//    text12.setFillColor(sf::Color(235, 70, 60));
    sf::Text text13("Rotation", font, 20);
//    text13.setFillColor(sf::Color(235, 70, 60));

    sf::Text text14(fullscreen ? "On" : "Off", font, 20);
    text14.setFillColor(sf::Color(235, 70, 60));
    sf::Text text15(music ? "On" : "Off", font, 20);
    text15.setFillColor(sf::Color(235, 70, 60));
    sf::Text text16(soundEffects ? "On" : "Off", font, 20);
    text16.setFillColor(sf::Color(235, 70, 60));
    sf::Text text17(rotation ? "On" : "Off", font, 20);
    text17.setFillColor(sf::Color(235, 70, 60));

    // Set position for text
    float textOffsetX = 10.0f; // Offset from the button's left edge
    float textOffsetY = 15.0f; // Offset from the button's top edge

    text14.setPosition(button8.getPosition().x + textOffsetX, button8.getPosition().y + textOffsetY);
    text15.setPosition(button9.getPosition().x + textOffsetX, button9.getPosition().y + textOffsetY);
    text16.setPosition(button10.getPosition().x + textOffsetX, button10.getPosition().y + textOffsetY);
    text17.setPosition(button11.getPosition().x + textOffsetX, button11.getPosition().y + textOffsetY);

    text10.setPosition(button8.getPosition().x + textOffsetX, button8.getPosition().y - textOffsetY * 1.8);
    text11.setPosition(button9.getPosition().x + textOffsetX + 13, button9.getPosition().y - textOffsetY * 1.8);
    text12.setPosition(button10.getPosition().x + textOffsetX - 15, button10.getPosition().y - textOffsetY * 1.8);
    text13.setPosition(button11.getPosition().x + textOffsetX, button11.getPosition().y - textOffsetY * 1.8);


    // Create square buttons
    sf::RectangleShape applyButton = createButton(70, 40);
    sf::RectangleShape cancelButton = createButton(70,40);

    // Set initial button position
    buttonSpacing = 20.0f;
    totalButtonWidth = applyButton.getSize().x * 2 + buttonSpacing;
    startX = (window.getSize().x - totalButtonWidth) / 2;
    startY = window.getSize().y - 50.0f;

    applyButton.setPosition(startX, startY);
    cancelButton.setPosition(startX + applyButton.getSize().x + buttonSpacing, startY);


    sf::Text applyText("Apply", font, 20);
    applyButton.setFillColor(sf::Color::Green);
    sf::Text cancelText("Cancel", font, 20);
    cancelButton.setFillColor(sf::Color(235, 70, 60));

    // Set position for text
    textOffsetX = 13.0f; // Offset from the button's left edge
    textOffsetY = 6.0f; // Offset from the button's top edge
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
                if (isButtonPressed(button8, mousePosition)) {
                    std::cout << "Button 10 Pressed!" << std::endl;
                    fullscreen = !fullscreen;
                    text14.setString(fullscreen ? "On" : "Off");
                } else if (isButtonPressed(button9, mousePosition)) {
                    std::cout << "Button 11 Pressed!" << std::endl;
                    music = !music;
                    text15.setString(music ? "On" : "Off");
                } else if (isButtonPressed(button10, mousePosition)) {
                    std::cout << "Button 12 Pressed!" << std::endl;
                    soundEffects = !soundEffects;
                    text16.setString(soundEffects ? "On" : "Off");
                } else if (isButtonPressed(button11, mousePosition)) {
                    std::cout << "Button 13 Pressed!" << std::endl;
                    rotation = !rotation;
                    text17.setString(rotation ? "On" : "Off");
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
                    window.close(); // Close the window if exit button is pressed
                    sf::VideoMode fullscreenMode = sf::VideoMode::getFullscreenModes()[0]; // Get the first available fullscreen mode
                   // sf::RenderWindow window(sf::VideoMode(resolution[0], resolution[1]), "Fire Fighter"); //make new window
//                    sf::RenderWindow window(sf::VideoMode(fullscreenMode), "Fixed Window", sf::Style::None | sf::Style::Titlebar);
                    sf::RenderWindow window(fullscreen ? fullscreenMode : sf::VideoMode(resolution[0], resolution[1]), "Fire Fighter", fullscreen ? sf::Style::Fullscreen : NULL);
                    mainWindow::ui program(window); // initialize ui window
                    program.displayMenu(); // method from ui to run the main program loop
                } else if (isButtonPressed(cancelButton, mousePosition)) {
                    window.close(); // Close the window if exit button is pressed
                    sf::VideoMode fullscreenMode = sf::VideoMode::getFullscreenModes()[0]; // Get the first available fullscreen mode
                    sf::RenderWindow window(fullscreen ? fullscreenMode : sf::VideoMode(w, h), "Fire Fighter"); //make new window
//                    sf::RenderWindow window(sf::VideoMode(fullscreenMode), "Fixed Window", sf::Style::None | sf::Style::Titlebar);
                    mainWindow::ui program(window); // initialize ui window
                    program.displayMenu(); // method from ui to run the main program loop
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
        window.draw(button8);
        window.draw(button9);
        window.draw(button10);
        window.draw(button11);

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

std::string *settings::getLanguage() {
    return language;
}

bool settings::toggleMusic() {
    return music;
}

settings *settings::getSettings() {
    return options;
}
