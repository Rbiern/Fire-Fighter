#include "Bullet.h"

Bullet::Bullet(float startX, float startY) {
    loadTexture();
    sprite.setPosition(startX, startY);
    sprite.setScale(0.2f,0.2f);
    speed = 300.f;
}

void Bullet::update(const sf::Time& delta) {
    sprite.move(-speed * delta.asSeconds(), 0);
}

void Bullet::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::FloatRect Bullet::getGlobalBounds() const {
    return sprite.getGlobalBounds();
}

void Bullet::loadTexture() {
    if (!texture.loadFromFile("../../resource/img/water-bullet.png")) {
    }
    sprite.setTexture(texture);
}
const sf::Sprite& Bullet::getSprite() const {
    return sprite;
}

