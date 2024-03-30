#include <iostream>
#include "Bullet.h"

Bullet::Bullet(float startX, float startY, const std::string& type) {
    loadTexture(type);
    sprite.setPosition(startX, startY);
    sprite.setScale(0.2f,0.2f);
    speed = 300.f;
}

void Bullet::update(const sf::Time& delta, const std::string& type) {
    if (type == "enemy"){
        sprite.move(speed * delta.asSeconds(), 0);
    }
    else if(type == "player"){
        sprite.move(-speed * delta.asSeconds(), 0);
    }
}

void Bullet::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::FloatRect Bullet::getGlobalBounds() const {
    return sprite.getGlobalBounds();
}

void Bullet::loadTexture(const std::string &type) {
    if (type =="player" && !texture.loadFromFile("../../resource/img/water-bullet.png")) {
        std::cerr << "Failed to load player's bullet texture" << std::endl;
    }
    else if(type =="enemy" && !texture.loadFromFile("../../resource/img/fireball.png")) {
        std::cerr << "Failed to load enemy's bullet texture" << std::endl;
    }
    sprite.setTexture(texture);
}

const sf::Sprite& Bullet::getSprite() const {
    return sprite;
}

