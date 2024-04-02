#include "powerup.h"

Powerup::Powerup() {
    if (!texture.loadFromFile("../../resource/img/life.png")) {
        std::cerr << "Failed to load powerup texture" << std::endl;
    }
    sprite.setTexture(texture);
    if(gameSettings.getVector().x == 3840){
        sprite.setScale(gameSettings.widthScaling(0.2f), gameSettings.heightScaling(0.2f));
    }else{
        sprite.setScale(gameSettings.widthScaling(1.f), gameSettings.heightScaling(1.f));
    }
    reset();
}

Powerup::~Powerup() = default;

void Powerup::reset() {
    // Randomize starting position
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> disY(100.f, 300.f); // Adjust Y range as needed
    sprite.setPosition(-sprite.getGlobalBounds().width, disY(gen));

    // Randomize speed and direction
    speed = 150.f; // Adjust speed as needed
    direction = sf::Vector2f(1.f, 0.f); // Start moving right
    collected = false;

    // Reset the timer for appearance delay
    appearanceDelay = std::uniform_int_distribution<int>(2, 10)(gen);
    time = sf::Time::Zero;
}

void Powerup::update(const sf::Time& delta, Player* player, sf::RenderWindow& window) {
    if (!collected && player->getLives() < 3) { // Only update if lives < 3
        time += delta;

        // Check if it's time to show the powerup
        if (time >= sf::seconds(appearanceDelay)) {
            // Move the powerup
            sprite.move(direction * speed * delta.asSeconds());

            // Check collision with player
            if (sprite.getGlobalBounds().intersects(player->getSprite().getGlobalBounds())) {
                std::cout << "lives before: " << player->getLives() << std::endl;
                player->increaseLife();
                std::cout << "lives after: " << player->getLives() << std::endl;
                collected = true;
            }

            // Bounce off window walls
            if (sprite.getPosition().x < 0) {
                // Change direction to move towards the right
                direction.x = 1.f;
            }
            else if (sprite.getPosition().x + sprite.getGlobalBounds().width > window.getSize().x) {
                // Change direction to move towards the left
                direction.x = -1.f;

                // Bounce randomly to top or bottom
                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_real_distribution<float> disY(window.getSize().y * 0.1f, window.getSize().y - sprite.getGlobalBounds().height); // Adjust Y range as needed

                // Randomly choose to move up or down
                direction.y = (std::rand() % 2 == 0) ? 1.f : -1.f;
            }

            // Bounce off top and bottom walls
            if (sprite.getPosition().y < window.getSize().y * 0.1f || sprite.getPosition().y + sprite.getGlobalBounds().height > window.getSize().y) {
                direction.y *= -1;
            }
        }
    }else{
        reset();
    }
}

void Powerup::draw(sf::RenderWindow& window, Player* player) {
    if (!collected && player->getLives() < 3 && time >= sf::seconds(appearanceDelay)) { // Only draw if lives < 3 and it's time to show the powerup
        window.draw(sprite);
    }
}
