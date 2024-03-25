#include "barrier.h"

Barrier::Barrier(float startX, float startY) : Entity() {
    this->setTexture("../../resource/img/iceBlock.png");
    this->setPosition(startX, startY);

//    sf::Vector2f scale(size / texture.getSize().x, size / texture.getSize().y);
//    barrierSprite.setScale(scale);
}


bool Barrier::enemyCollision(const sf::Sprite& enemySprite) const {
    return sprite.getGlobalBounds().intersects(enemySprite.getGlobalBounds());
}

bool Barrier::bulletCollision(const sf::Sprite& bulletSprite) const {
    return sprite.getGlobalBounds().intersects(bulletSprite.getGlobalBounds());
}

void Barrier::shrink() {
    size /= 1.2; // Divide the size by 1.2
    // Ensure size doesn't go below a minimum value
    if (size < 0) {
        size = 0;
    }
    // Resize the barrier sprite
    sf::Vector2f scale(size / texture.getSize().x, size / texture.getSize().y);
    sprite.setScale(scale);
}

void Barrier::reset() {
    size = initialSize;
    sf::Vector2f scale(size / texture.getSize().x, size / texture.getSize().y);
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
