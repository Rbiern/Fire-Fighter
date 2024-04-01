#include <iostream>
#include "bullet.h"

Bullet::Bullet(float startX, float startY, const std::string& type) {
    loadTexture(type);
    sprite.setPosition(startX, startY);
    resolution = gameSettings.getVector();
    adjustForResolution(resolution);
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

void Bullet::draw(sf::RenderWindow& window, const std::string &type) {
    loadTexture(type);
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

void Bullet::adjustForResolution(const sf::Vector2u& resolution) {

    float scale = 0.2f;

    if (resolution == sf::Vector2u(640, 360)) {
        scale = 0.2f;
    } else if (resolution == sf::Vector2u(1280, 720)) {
        scale = 0.5f;
    } else if (resolution == sf::Vector2u(1920, 1080)) {
        scale = 0.8f;
    } else if (resolution == sf::Vector2u(3840, 2160)) {
        scale = 1.0f;
    }

    sprite.setScale(scale,scale);

}
