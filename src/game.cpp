//
// Created by Pc MSI on 2024-03-08.
//

#include "game.h"

game::game() {
    options = new settings();
}

void game::gameLoop() {
    sf::RenderWindow window(sf::VideoMode(options->getResolution()[0], options->getResolution()[1]), "Gamer Moment");
    Player player(window.getSize().x-100.f, window.getSize().y -100.0f);

    sf::Clock shootCooldown;
    float movementSpeed = 0.5f;
    bool canShoot = true;

    // Create an exit button
    sf::RectangleShape exitButton(sf::Vector2f(100.f, 30.f)); // Smaller size
    exitButton.setFillColor(sf::Color::Red);
    exitButton.setPosition(window.getSize().x - 130.f, 20.f); // Position in the top right corner

    // Create text for the exit button
    sf::Font font;
    if (!font.loadFromFile(R"(../../resource/fontsRajdhani-SemiBold.ttf)")) { // Change the font file path as needed
        // Handle font loading failure
    }
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

