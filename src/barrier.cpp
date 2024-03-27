#include "barrier.h"

Barrier::Barrier(float startX, float startY, const sf::Vector2u& resolution) : Entity() {
    this->setTexture("../../resource/img/iceBlock.png");
    this->setPosition(startX, startY);
    adjustForResolution(resolution);
}

bool Barrier::enemyCollision(const Enemy& enemy) const {
    return sprite.getGlobalBounds().intersects(enemy.getGlobalBounds());
}

bool Barrier::bulletCollision(const sf::Sprite& bulletSprite) const {
    return sprite.getGlobalBounds().intersects(bulletSprite.getGlobalBounds());
}

void Barrier::shrink() {
    // Calculate the new size
    size /= 1.02; // Divide the size by 1.02 to shrink it

    // Ensure size doesn't go below a minimum value
    if (size < 0) {
        return;
    }

    // Resize the barrier sprite
    sf::Vector2f scale(size, size); // Assuming initialSize is the original size of the barrier
    sprite.setScale(scale);
}

void Barrier::reset(const sf::Vector2u& resolution) {
    float referenceWidth = 1920.0f; // Reference width for size calculation
    float referenceHeight = 1080.0f; // Reference height for size calculation

    // Calculate the ratio of the current resolution to the reference resolution
    float widthRatio = resolution.x / referenceWidth;
    float heightRatio = resolution.y / referenceHeight;

    size = 3.5f * std::min(widthRatio, heightRatio);
    sf::Vector2f scale(size, size);
    sprite.setScale(scale);
}

//void Barrier::spawn(float newX, float newY) {
//
//}

void Barrier::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

void Barrier::adjustForResolution(const sf::Vector2u& resolution) {

    float referenceWidth = 1920.0f; // Reference width for size calculation
    float referenceHeight = 1080.0f; // Reference height for size calculation

    // Calculate the ratio of the current resolution to the reference resolution
    float widthRatio = resolution.x / referenceWidth;
    float heightRatio = resolution.y / referenceHeight;

    // Calculate the size of the barrier based on the resolution ratio
    size = 3.5f * std::min(widthRatio, heightRatio);

    // Set the scale of the barrier sprite
    sf::Vector2f scale(size, size);
    sprite.setScale(scale);

}

sf::Vector2f Barrier::getSize() const {
    return sprite.getGlobalBounds().getSize();
}

sf::Vector2f Barrier::getPosition() const {
    return sprite.getPosition();
}

Barrier::~Barrier() {

}
