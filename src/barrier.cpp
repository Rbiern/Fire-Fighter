#include "bullet.h"

Bullet::Bullet(float startX, float startY, const std::string& type, sf::Vector2u res) {
    loadTexture(type);
    bulletSprite.setTexture(bulletTexture);
    bulletSprite.setPosition(startX, startY);
    bulletSprite.setScale(0.5f * ((float)res.x/1280.f), 0.5f * ((float)res.y/720.f));
    speed = 300.f;
}

Bullet::~Bullet() = default;

void Bullet::update(const sf::Time& delta, const std::string& type) {
    if (type == "enemy"){
        bulletSprite.move(speed * delta.asSeconds(), 0);
    }
    else if(type == "player"){
        bulletSprite.move(-speed * delta.asSeconds(), 0);
    }
}

void Bullet::draw(sf::RenderWindow& window, const std::string &type) {
    loadTexture(type);
    window.draw(bulletSprite);
}

sf::FloatRect Bullet::getGlobalBounds() const {
    return bulletSprite.getGlobalBounds();
}

const sf::Sprite& Bullet::getSprite() const {
    return bulletSprite;
}

void Bullet::loadTexture(const std::string &type) {
    if (type =="player" && !bulletTexture.loadFromFile("../../resource/img/water-bullet.png")) {
        std::cerr << "Failed to load player's bullet texture" << std::endl;
    }
    else if(type =="enemy" && !bulletTexture.loadFromFile("../../resource/img/fireball.png")) {
        std::cerr << "Failed to load enemy's bullet texture" << std::endl;
    }
    bulletSprite.setTexture(bulletTexture);
}
