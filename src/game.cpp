//
// Created by Pc MSI on 2024-03-08.
//

#include "game.h"

game::game() {
    options = new settings();
}

void game::gameLoop() {
    sf::RenderWindow window(sf::VideoMode(options->getResolution()[0], options->getResolution()[1]), "Gamer Moment");

//    entity* character = new entity();
    sf::RectangleShape character;

    character.setSize(sf::Vector2f(50.f, 50.f));
    character.setFillColor(sf::Color::Green);
    character.setPosition(400.f, 300.f);

    sf::Clock shootCooldown;
    float movementSpeed = 0.5f;
    bool canShoot = true;

    // Create an exit button
    sf::RectangleShape exitButton(sf::Vector2f(100.f, 30.f)); // Smaller size
    exitButton.setFillColor(sf::Color::Red);
    exitButton.setPosition(window.getSize().x - 130.f, 20.f); // Position in the top right corner

    // Create text for the exit button
    sf::Font font;
    if (!font.loadFromFile(R"(C:\Users\Pc MSI\CLionProjects\Fire Fighter\resource\fonts\Rajdhani-SemiBold.ttf)")) { // Change the font file path as needed
        // Handle font loading failure
    }
    sf::Text exitButtonText("Exit", font, 16); // Smaller text size
    exitButtonText.setFillColor(sf::Color::White);
    // Center the text within the exit button
    exitButtonText.setPosition(exitButton.getPosition().x + (exitButton.getSize().x - exitButtonText.getLocalBounds().width) / 2,
                               exitButton.getPosition().y + (exitButton.getSize().y - exitButtonText.getLocalBounds().height) / 2);




    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Move character
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            if (character.getPosition().y - 0.5 >= 0) {
                character.move(0.f, -movementSpeed);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            if (character.getPosition().y + character.getSize().y + movementSpeed <= window.getSize().y) {
                character.move(0.f, movementSpeed);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            if (character.getPosition().x - movementSpeed >= 0) {
                character.move(-movementSpeed, 0.f);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            if (character.getPosition().x + character.getSize().x + movementSpeed <= window.getSize().x) {
                character.move(movementSpeed, 0.f);
            }
        }

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
                window.close();
            }
        }

        window.clear();
        window.draw(character);
        window.draw(exitButton); // Draw the exit button
        window.draw(exitButtonText); // Draw the exit button text
        window.display();
    }
    return;
}

