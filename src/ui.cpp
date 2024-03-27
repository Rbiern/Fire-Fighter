#include "ui.h"

/** constructor */
ui::ui() {
    options = new settings();
    sf::VideoMode fullScreenMode = sf::VideoMode::getDesktopMode();
    _window.create((options->isFullScreen()) ? fullScreenMode : sf::VideoMode(options->getResolution()[0],options->getResolution()[1]), "Fire Fighter", (options->isFullScreen() || options->getResolution()[0] >= fullScreenMode.width) ? sf::Style::Fullscreen : sf::Style::Default);
    font = options->getFont();
    errorFlag = _init();
}

/**
 * helper method to help initialize ui variables
 * returns false if successful, otherwise returns true
 * */
bool ui::_init() {
    sf::Image icon = options->getIcon();                                                            // Load icon image
    _window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());    // Set the window icon
    if (!backgroundImage.loadFromFile("../../resource/img/menu_background.jpg")) {          // load background image for main menu
        std::cerr << "Failed to load background image!" << std::endl; // uses <iostream>
        return true;
    }
    if (!music.openFromFile("../../music/EyjafjallaDream.mp3")) {                           // set music for the main menu
        std::cerr << "Failed to load music" << std::endl;
        return true;
    }
    music.setLoop(true);                                                                            // enable music to loop
    return false;
}

/** help create the button shapes on screen */
sf::ConvexShape ui::createButtonShape(float windowWidth) {
    // Calculate button positions
    float startX = (windowWidth - ((windowWidth / 5.f) * 3)) / 2.f;
    sf::ConvexShape parallelogram;
    parallelogram.setPointCount(4);
    parallelogram.setPoint(0, sf::Vector2f(startX, 0.f));
    parallelogram.setPoint(1, sf::Vector2f(startX + (windowWidth / 5.f), 0.f));
    parallelogram.setPoint(2, sf::Vector2f(startX + (windowWidth / 5.f) - 50.f, 55.f));
    parallelogram.setPoint(3, sf::Vector2f(startX - 50.f, 55.f));
    parallelogram.setFillColor(sf::Color(54, 207, 213));
    return parallelogram;
}

/** main UI menu loop */
void ui::displayMenu() {
    if (errorFlag) return;

    // Calculate button dimensions based on window size
    float windowWidth = static_cast<float>(_window.getSize().x);
    float windowHeight = static_cast<float>(_window.getSize().y);
    // Calculate button positions
    float startX = (windowWidth - ((windowWidth / 5.f) * 3)) / 2.f;

    //Create settings button
    sf::ConvexShape settingsbutton = createButtonShape(windowWidth);
    settingsbutton.setPosition(startX, windowHeight - 55.f - 20.f);
    // Create quit button
    sf::ConvexShape quitButton = createButtonShape(windowWidth);
    quitButton.setPosition(startX + (windowWidth / 5.f), windowHeight - 55.f - 20.f);
    // Create new game button
    sf::ConvexShape newGameButton = createButtonShape(windowWidth);
    newGameButton.setPosition(startX - (windowWidth / 5.f), windowHeight - 55.f - 20.f);

    // Create settings button text
    sf::String s1 = options->getLanguage()[0];
    sf::Text text1(s1, font, 20);
    text1.setFillColor(sf::Color(235, 70, 60));
    text1.setPosition(settingsbutton.getPosition().x, settingsbutton.getPosition().y + 20);
    // Create quit button text
    sf::String s2 = options->getLanguage()[1];
    sf::Text text2(s2, font, 20);
    text2.setFillColor(sf::Color(235, 70, 60));
    text2.setPosition(quitButton.getPosition().x + 5, quitButton.getPosition().y + 20);
    // Create new game button text
    sf::String s3 = options->getLanguage()[2];
    sf::Text text3(s3, font, 20);
    text3.setFillColor(sf::Color(235, 70, 60));
    text3.setPosition(quitButton.getPosition().x + (windowWidth / 5.f) + 20, newGameButton.getPosition().y + 20);

    sf::Sprite background(backgroundImage);
    background.setTexture(backgroundImage);
    background.setScale(_window.getSize().x / background.getLocalBounds().width,_window.getSize().y / background.getLocalBounds().height);

    _window.setFramerateLimit(60);
    if (options->toggleMusic()) music.play();

    bool startGameFlag = false;
    bool openSettings = false;
    bool exitFlag = false;

    // The main loop starts here
    while (1) {
        sf::Event event;
        while (_window.pollEvent(event)) {
            // check if user has closed the window
            if (event.type == sf::Event::Closed) {
                _window.close();
                return;
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(_window);
                //game window
                if (newGameButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    std::cout << "New Game" << std::endl;
                    startGameFlag = true;
                }
                // settings
                if (settingsbutton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    std::cout << "Settings" << std::endl;
                    openSettings = true;
                }
                //quit button
                if (quitButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    std::cout << "Quit" << std::endl;
                    _window.close();
                    return;
                }
            }
        }
        if (startGameFlag) {
            if (options->toggleMusic()) {
                music.pause();
            }
            _window.close();
            game *newGame = new game(options);
            newGame->gameLoop();
            startGameFlag = false;
            if (options->toggleMusic()) {
                music.play();
            }
            exitFlag = true;
            break;
        }
        if (openSettings) {
            _window.close();
            options->openSettings(options->getResolution()[0], options->getResolution()[1]);
            // when exited settings
            exitFlag = true;
            break;
        }
        // for button mouse hover effect
        sf::Vector2i mousePos = sf::Mouse::getPosition(_window);
        if (settingsbutton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            settingsbutton.setFillColor(sf::Color(0, 255, 0, 200)); // Green with transparency
        } else {
            settingsbutton.setFillColor(sf::Color(54, 207, 213));
        }
        if (quitButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            quitButton.setFillColor(sf::Color(0, 0, 255, 200)); // Blue with transparency
        } else {
            quitButton.setFillColor(sf::Color(54, 207, 213));
        }
        if (newGameButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            newGameButton.setFillColor(sf::Color(255, 0, 255, 200)); // Red with transparency
        } else {
            newGameButton.setFillColor(sf::Color(54, 207, 213));
        }
        _window.clear();
        _window.draw(background);
        _window.draw(settingsbutton);
        _window.draw(quitButton);
        _window.draw(newGameButton);
        _window.draw(text1);
        _window.draw(text2);
        _window.draw(text3);
        _window.display();
    }
    if (exitFlag) {
        sf::VideoMode fullScreenMode = sf::VideoMode::getDesktopMode();
        _window.create((options->isFullScreen()) ? fullScreenMode : sf::VideoMode(options->getResolution()[0],options->getResolution()[1]), "Fire Fighter", (options->isFullScreen() || options->getResolution()[0] >= fullScreenMode.width) ? sf::Style::Fullscreen : sf::Style::Default);
        _init();
        displayMenu();
    }
}

ui::~ui() {
    delete(options);
}
