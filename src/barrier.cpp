#include "barrier.h"

Barrier::Barrier(float startX, float startY) : Entity() {
    this->setTexture("../../resource/img/iceBlock.png");
    this->setPosition(startX, startY);
    size = 3.5;
    sf::Vector2f scale(size, size);
    sprite.setScale(scale);
}


bool Barrier::enemyCollision(const sf::Sprite& enemySprite) const {
    return sprite.getGlobalBounds().intersects(enemySprite.getGlobalBounds());
}

bool Barrier::bulletCollision(const sf::Sprite& bulletSprite) const {
    return sprite.getGlobalBounds().intersects(bulletSprite.getGlobalBounds());
}

void Barrier::shrink() {
    // Calculate the new size
    size /= 1.02; // Divide the size by 1.02 to shrink it

    // Ensure size doesn't go below a minimum value
    if (size < 0) {
        reset();
    }

    // Resize the barrier sprite
    sf::Vector2f scale(size, size); // Assuming initialSize is the original size of the barrier
    sprite.setScale(scale);
}

void Barrier::reset() {
    size = 3.5;
    sf::Vector2f scale(size, size);
    sprite.setScale(scale);
}

void Barrier::spawn(float newX, float newY) {

}

void Barrier::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::Vector2f Barrier::getSize() const {
    return sprite.getGlobalBounds().getSize();
}

sf::Vector2f Barrier::getPosition() const {
    return sprite.getPosition();
}

Barrier::~Barrier() {

}
