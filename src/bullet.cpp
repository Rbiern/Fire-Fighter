#include "bullet.h"
#include <iostream>
Bullet::Bullet(float startX, float startY) : Entity() {
    this->setTexture("../../resource/img/water-bullet.png");
    this->setPosition(startX,startY);
    speed = 100.0f;
    this->setScale(0.2f,0.2f);
    std::cout << "Bullet sprite texture: " << sprite.getTexture() << std::endl;
    std::cout << "Bullet sprite position: (" << sprite.getPosition().x << ", " << sprite.getPosition().y << ")" << std::endl;
}


void Bullet::update(const sf::Time& delta) {
    move(-speed * delta.asSeconds(), 0); 
}

//sf::Vector2f Bullet::getPosition() const {
//    return sprite.getPosition();
//}
