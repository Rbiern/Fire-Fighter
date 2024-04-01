#include "powerup.h"

powerup::powerup() {
    if (!texture.loadFromFile("../../resource/img/life.png")) {
        std::cerr << "Failed to load powerup texture" << std::endl;
    }
    sprite.setTexture(texture);
    resolution = gameSettings.getVector();
    adjustForResolution(resolution)
    reset();
}

powerup::~powerup() = default;

void powerup::reset() {
    // Randomize starting position
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> disY(100.f, 300.f); // Adjust Y range as needed
    sprite.setPosition(-sprite.getGlobalBounds().width, disY(gen));

    // Randomize speed and direction
    speed = 150.f; // Adjust speed as needed
    direction = sf::Vector2f(1.f, 0.f); // Start moving right
    collected = false;
}

void powerup::update(const sf::Time& delta, Player* player, sf::RenderWindow& window) {
    if (!collected && player->getLives() < 3) { // Only update if lives < 3
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
            std::uniform_real_distribution<float> disY(window.getSize().y * 0.1f, window.getSize().y - sprite.getGlobalBounds().height); // Adjust Y range as needed

            // Randomly choose to move up or down
            direction.y = (std::rand() % 2 == 0) ? 1.f : -1.f;
        }

        // Bounce off top and bottom walls
        if (sprite.getPosition().y < window.getSize().y * 0.1f || sprite.getPosition().y + sprite.getGlobalBounds().height > window.getSize().y) {
            direction.y *= -1;
        }
    }
}

void powerup::draw(sf::RenderWindow& window, Player* player) {
    if (!collected && player->getLives() < 3) { // Only draw if lives < 3
        window.draw(sprite);
    }
}

void powerup::adjustForResolution(const sf::Vector2u& resolution) {

    float scale = 0.5f;

    if (resolution == sf::Vector2u(640, 360)) {
        scale = 0.5f;
    } else if (resolution == sf::Vector2u(1280, 720)) {
        scale = 1.0f;
    } else if (resolution == sf::Vector2u(1920, 1080)) {
        scale = 1.2f;
    } else if (resolution == sf::Vector2u(3840, 2160)) {
        scale = 1.5f;
    }

    sprite.setScale(scale,scale);

}
