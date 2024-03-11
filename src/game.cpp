//
// Created by Pc MSI on 2024-03-08.
//

#include "game.h"

game::game() {
    options = new settings();
}

void game::gameLoop() {
    sf::VideoMode fullScreenMode = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window((options->isFullScreen()) ? fullScreenMode : sf::VideoMode(options->getResolution()[0],options->getResolution()[1]), "Gamer Moment", (options->isFullScreen() || options->getResolution()[0] >= fullScreenMode.width) ? sf::Style::Fullscreen : sf::Style::Default);
    sf::Image icon;
    if (!icon.loadFromFile("../../resource/img/icon.png")) {
        std::cerr << "Failed to load icon" << std::endl;
        return;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr()); // Set the window icon
    window.setFramerateLimit(60);

    Player player(window.getSize().x-100.f, window.getSize().y -100.0f);

    sf::Font font;
    if (!font.loadFromFile("../../resource/fonts/Rajdhani-SemiBold.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
        return;
    }

    //*****************************************************************************************
    // pick character window code start
    // character textures
    sf::Texture characterTexture;
    if (!characterTexture.loadFromFile("../../resource/img/water.png")) {
        std::cerr << "Failed to load player!" << std::endl;
        return;
    }
    sf::Sprite character1(characterTexture);
    sf::Sprite character2(characterTexture);
    // Get the screen dimensions
    sf::Vector2u screenSize = window.getSize();
    float screenWidth = screenSize.x;
    float screenHeight = screenSize.y;
    // Calculate position to center character
    character1.setPosition((screenWidth - character1.getGlobalBounds().width - 230)/ 2, (screenHeight - character2.getGlobalBounds().height) / 2);
    character2.setPosition((screenWidth - character2.getGlobalBounds().width + 250) / 2, (screenHeight - character2.getGlobalBounds().height) / 2);
    // Create button 1
    sf::RectangleShape button1(sf::Vector2f(200.f, 50.f));
    button1.setFillColor(sf::Color::Blue);
    button1.setPosition((screenWidth - button1.getSize().x * 2 - 50) / 2, screenHeight / 2); // Position first button to the left of center
    // Create button 1 text
    sf::Text text1("Water Boy", font, 20);
    text1.setPosition(button1.getPosition().x + (button1.getSize().x - text1.getLocalBounds().width) / 2, button1.getPosition().y + (button1.getSize().y - text1.getLocalBounds().height) / 2);
    text1.setFillColor(sf::Color::White);
    // Create button 2
    sf::RectangleShape button2(sf::Vector2f(200.f, 50.f));
    button2.setFillColor(sf::Color::Red);
    button2.setPosition(button1.getPosition().x + button1.getSize().x + 50, screenHeight / 2); // Position second button to the right of first button
    // Create button 2 text
    sf::Text text2("Fire Girl", font, 20);
    text2.setPosition(button2.getPosition().x + (button2.getSize().x - text2.getLocalBounds().width) / 2, button2.getPosition().y + (button2.getSize().y - text2.getLocalBounds().height) / 2);
    text2.setFillColor(sf::Color::White);
    // create text at top of screen
    sf::Text chooseText("Choose a character", font, 30);
    chooseText.setPosition((screenWidth - chooseText.getLocalBounds().width) / 2, 20); // Position text at the top center
    chooseText.setFillColor(sf::Color::White);
    // Create "Go Back" button
    sf::RectangleShape backButton(sf::Vector2f(150.f, 50.f));
    backButton.setFillColor(sf::Color(54, 207, 213));
    backButton.setPosition(screenWidth - backButton.getSize().x - 20, 20); // Position button at the top right
    sf::Text backText("Go Back", font, 20);
    backText.setPosition(backButton.getPosition().x + (backButton.getSize().x - backText.getLocalBounds().width) / 2, backButton.getPosition().y + (backButton.getSize().y - backText.getLocalBounds().height) / 2);
    backText.setFillColor(sf::Color::White);

    for (int flag = true; flag;) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    if (button1.getGlobalBounds().contains(mousePos)) {
                        // Button 1 clicked
                        std::cout << "Player 1 selected\n";
                        flag = false;
                    }
                    if (button2.getGlobalBounds().contains(mousePos)) {
                        // Button 2 clicked
                        std::cout << "Player 2 selected\n";
                        flag = false;
                    }
                    if (backButton.getGlobalBounds().contains(mousePos)) {
                        // Back button clicked
                        std::cout << "Go Back\n";
                        window.close();
                        return;
                    }
                }
            }
            if (event.type == sf::Event::MouseMoved) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                if (button1.getGlobalBounds().contains(mousePos)) {
                    // Button 1 hovered
                    button1.setFillColor(sf::Color(0, 0, 255, 200));
                } else {
                    button1.setFillColor(sf::Color(0, 0, 255, 255));
                }

                if (button2.getGlobalBounds().contains(mousePos)) {
                    // Button 2 hovered
                    button2.setFillColor(sf::Color(255, 0, 0, 200));
                } else {
                    button2.setFillColor(sf::Color(255, 0, 0, 255));
                }

                if (backButton.getGlobalBounds().contains(mousePos)) {
                    // Back button hovered
                    backButton.setFillColor(sf::Color(54, 207, 213, 200));
                } else {
                    backButton.setFillColor(sf::Color(54, 207, 213, 255));
                }
            }
        }
        // Clear the window
        window.clear(sf::Color(52, 109, 129));

        // Draw elements
        window.draw(character1);
        window.draw(character2);
        window.draw(button1);
        window.draw(text1);
        window.draw(button2);
        window.draw(text2);
        window.draw(chooseText);
        window.draw(backButton);
        window.draw(backText);

        // Display the window
        window.display();
    }
    // end of chose player window
    //*************************************************************************************************


    sf::Clock shootCooldown;
    float movementSpeed = 0.5f;
    bool canShoot = true;

    // Create an exit button
    sf::RectangleShape exitButton(sf::Vector2f(100.f, 30.f)); // Smaller size
    exitButton.setFillColor(sf::Color::Red);
    exitButton.setPosition(window.getSize().x - 130.f, 20.f); // Position in the top right corner

    // Create text for the exit button
    sf::Text exitButtonText("Exit", font, 16); // Smaller text size
    exitButtonText.setFillColor(sf::Color::White);
    // Center the text within the exit button
    exitButtonText.setPosition(exitButton.getPosition().x + (exitButton.getSize().x - exitButtonText.getLocalBounds().width) / 2,
                               exitButton.getPosition().y + (exitButton.getSize().y - exitButtonText.getLocalBounds().height) / 2);


    sf::Music music;
    // set music for the main menu
    if (!music.openFromFile("../../music/rglk2theme2distort.mp3")) {
        std::cerr << "Failed to load music" << std::endl;
    }
    music.setLoop(true); // Loop the music
    music.play();

/** main game window */
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Move character
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            if (player.getPosition().y - movementSpeed >= 0) {
                player.move(sf::Vector2f(0.f, -movementSpeed));
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            if (player.getPosition().y + player.getSize().y + movementSpeed <= window.getSize().y) { // 아래로 이동 가능한 경우에만 이동
                player.move(sf::Vector2f(0.f, movementSpeed));
            }
        }
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
//            if (character.getPosition().x - movementSpeed >= 0) {
//                character.move(-movementSpeed, 0.f);
//            }
//        }
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
//            if (character.getPosition().x + character.getSize().x + movementSpeed <= window.getSize().x) {
//                character.move(movementSpeed, 0.f);
//            }
//        }

        // Shooting
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
//            if (canShoot && shootCooldown.getElapsedTime().asSeconds() > 0.5f) {
//                // Shoot projectile here
//                shootCooldown.restart();
//            }
//        }

        // Update shooting cooldown state
//        if (shootCooldown.getElapsedTime().asSeconds() > 0.5f) {
//            canShoot = true;
//        } else {
//            canShoot = false;
//        }

        // Check if the exit button is clicked
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (exitButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                music.stop();
                window.close();
            }
        }

        window.clear();
        player.draw(window);
        window.draw(exitButton); // Draw the exit button
        window.draw(exitButtonText); // Draw the exit button text
        window.display();
    }
    return;
}

