#include "ui.h"

namespace mainWindow {

    /** constructor */
    ui::ui(sf::RenderWindow &window1) : _window(window1) {
        options = new settings(); // create new setting object
        errorFlag = _init();
    }

    /** main program loop */
    void ui::displayMenu() {
        if (errorFlag) {
            return;
        }

        // Calculate button dimensions based on window size
        float windowWidth = static_cast<float>(_window.getSize().x);
        float windowHeight = static_cast<float>(_window.getSize().y);
        float buttonHeight = 55.f;
        float buttonWidth = windowWidth / 5.f; // Adjusted for 3 buttons with spacing
        float buttonOffsetY = 20.f; // Offset from the bottom

        // Calculate button positions
        float totalButtonWidth = buttonWidth * 3; // Total width of all buttons
        float startX = (windowWidth - totalButtonWidth) / 2.f; // Starting x-coordinate for the first button

        //Create buttons
        sf::ConvexShape button1;
        button1.setPointCount(4);
        button1.setPoint(0, sf::Vector2f(startX, 0.f));
        button1.setPoint(1, sf::Vector2f(startX + buttonWidth, 0.f));
        button1.setPoint(2, sf::Vector2f(startX + buttonWidth - 50.f, buttonHeight));
        button1.setPoint(3, sf::Vector2f(startX - 50.f, buttonHeight));
        button1.setFillColor(sf::Color(54, 207, 213));
        button1.setPosition(startX, windowHeight - buttonHeight - buttonOffsetY);

        sf::ConvexShape button2;
        button2.setPointCount(4);
        button2.setPoint(0, sf::Vector2f(startX, 0.f));
        button2.setPoint(1, sf::Vector2f(startX + buttonWidth, 0.f));
        button2.setPoint(2, sf::Vector2f(startX + buttonWidth - 50.f, buttonHeight));
        button2.setPoint(3, sf::Vector2f(startX - 50.f, buttonHeight));
        button2.setFillColor(sf::Color(54, 207, 213));
        button2.setPosition(startX + buttonWidth, windowHeight - buttonHeight - buttonOffsetY);

        sf::ConvexShape button3;
        button3.setPointCount(4);
        button3.setPoint(0, sf::Vector2f(startX, 0.f));
        button3.setPoint(1, sf::Vector2f(startX + buttonWidth, 0.f));
        button3.setPoint(2, sf::Vector2f(startX + buttonWidth - 50.f, buttonHeight));
        button3.setPoint(3, sf::Vector2f(startX - 50.f, buttonHeight));
        button3.setFillColor(sf::Color(54, 207, 213));
        button3.setPosition(startX - buttonWidth, windowHeight - buttonHeight - buttonOffsetY);

        sf::Text text1(options->getLanguage()[0], font, 20);
        text1.setFillColor(sf::Color(235, 70, 60));
        text1.setPosition(button1.getPosition().x, button1.getPosition().y + 20);

        sf::Text text2(options->getLanguage()[1], font, 20);
        text2.setFillColor(sf::Color(235, 70, 60));
        text2.setPosition(button2.getPosition().x + 5, button2.getPosition().y + 20);

        sf::Text text3(options->getLanguage()[2], font, 20);
        text3.setFillColor(sf::Color(235, 70, 60));
        text3.setPosition(button2.getPosition().x + buttonWidth + 20, button3.getPosition().y + 20);


        sf::Sprite background(backgroundImage);
        background.setTexture(backgroundImage);
        background.setScale(_window.getSize().x / background.getLocalBounds().width,
                            _window.getSize().y / background.getLocalBounds().height);
        _window.setFramerateLimit(60);
        music.play();
        bool startGameFlag = false;
        bool openSettings = false;

        // The main loop starts here
        while (_window.isOpen()) {
            sf::Event event;
            while (_window.pollEvent(event)) {
                // check if user has closed the window
                if (event.type == sf::Event::Closed) {
                    _window.close();
                }
                if (event.type == sf::Event::MouseButtonPressed) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(_window);
                    //game window
                    if (button3.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        std::cout << "start game" << std::endl;
                        startGameFlag = true;
                    }
                    // settings
                    if (button1.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        std::cout << "settings" << std::endl;
                        openSettings = true;
                    }
                    //quit button
                    if (button2.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        std::cout << "exit game" << std::endl;
                        return;
                    }
                }
            }
            if (startGameFlag) {
                game *newGame = new game();
                newGame->gameLoop();
                startGameFlag = false;
            }
            if (openSettings) {
                music.stop();
                _window.close();
                options->openSettings(options->getResolution()[0], options->getResolution()[1]);
            }
            // for button mouse hover effect
            sf::Vector2i mousePos = sf::Mouse::getPosition(_window);
            if (button1.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                button1.setFillColor(sf::Color(0, 255, 0, 200)); // Green with transparency
            } else {
                button1.setFillColor(sf::Color(54, 207, 213));
            }
            if (button2.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                button2.setFillColor(sf::Color(0, 0, 255, 200)); // Blue with transparency
            } else {
                button2.setFillColor(sf::Color(54, 207, 213));
            }
            if (button3.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                button3.setFillColor(sf::Color(255, 0, 255, 200)); // Red with transparency
            } else {
                button3.setFillColor(sf::Color(54, 207, 213));
            }
            _window.clear();
            _window.draw(background);
            _window.draw(button1);
            _window.draw(button2);
            _window.draw(button3);
            _window.draw(text1);
            _window.draw(text2);
            _window.draw(text3);
            _window.display();
        }
    }

    /** helper method to help initialize ui variables */
    bool ui::_init() {
        // Load icon image
        if (!icon.loadFromFile(R"(C:\Users\Pc MSI\CLionProjects\Fire Fighter\resource\img\icon.png)")) {
            std::cerr << "Failed to load icon" << std::endl;
            return true;
        }
        _window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr()); // Set the window icon

        // load background image for main menu
        if (!backgroundImage.loadFromFile(
                R"(C:\Users\Pc MSI\CLionProjects\Fire Fighter\resource\img\menu_background.jpg)")) { //"../resource/img/main_menu_image.jpg"
            std::cerr << "Failed to load background image!" << std::endl; // uses <iostream>
            return true; // if it failed, then loop will break and program will close
        }

        // Set fonts
        if (!font.loadFromFile(R"(C:\Users\Pc MSI\CLionProjects\Fire Fighter\resource\fonts\Rajdhani-SemiBold.ttf)")) {
            std::cerr << "Failed to load font!" << std::endl;
            return true;
        }

        // set music for the main menu
        if (!music.openFromFile(R"(C:\Users\Pc MSI\CLionProjects\Fire Fighter\music\CYBERPSYCHO.wav)")) {
            std::cerr << "Failed to load music" << std::endl;
            return true;
        }
        music.setLoop(true); // Loop the music

        return false;
    }

}// end of mainWindow