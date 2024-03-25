#include "powerup.h"
#include <iostream>
#include <random>

powerup::powerup() {
    if (!texture.loadFromFile("../../resource/img/life.png")) {
        std::cerr << "Failed to load powerup texture" << std::endl;
    }
    sprite.setTexture(texture);
    sprite.setScale(0.5f, 0.5f); // Adjust scale as needed
    reset();
}

void powerup::reset() {
    // Randomize starting position
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> disY(50.f, 300.f); // Adjust Y range as needed
    sprite.setPosition(-sprite.getGlobalBounds().width, disY(gen));

    // Randomize speed and direction
    speed = 100.f; // Adjust speed as needed
    direction = sf::Vector2f(1.f, 0.f); // Start moving right
    collected = false;
}

void powerup::update(const sf::Time& delta, Player& player, sf::RenderWindow& window) {
    if (!collected && player.getLives() < 3) { // Only update if lives < 3
        // Move the powerup
        sprite.move(direction * speed * delta.asSeconds());

        // Check collision with player
        if (sprite.getGlobalBounds().intersects(player.getSprite().getGlobalBounds())) {
            std::cout << "lives before: " << player.getLives() << std::endl;
            player.increaseLife();
            std::cout << "lives after: " << player.getLives() << std::endl;
            collected = true;
        }

        // Bounce off window walls
        if (sprite.getPosition().x < 0 || sprite.getPosition().x + sprite.getGlobalBounds().width > window.getSize().x) {
            // Change direction horizontally
            direction.x *= -1;

            // If powerup reaches right wall, bounce randomly to top or bottom
            if (sprite.getPosition().x + sprite.getGlobalBounds().width > window.getSize().x) {
                std::uniform_real_distribution<float> disY(0.f, window.getSize().y); // Adjust Y range as needed
                sprite.setPosition(window.getSize().x - sprite.getGlobalBounds().width, disY(gen));
                direction.y = (std::rand() % 2 == 0) ? 1.f : -1.f;
            }
        }

        // Bounce off top and bottom walls
        if (sprite.getPosition().y < 0 || sprite.getPosition().y + sprite.getGlobalBounds().height > window.getSize().y) {
            direction.y *= -1;
        }
    }
}

void powerup::draw(sf::RenderWindow& window, Player& player) {
    if (!collected && player.getLives() < 3) { // Only draw if lives < 3
        window.draw(sprite);
    }
}
