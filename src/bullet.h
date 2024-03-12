//
// Created by Sungmin Lee on 2024/03/11.
//

#ifndef FIRE_FIGHTER_BULLET_H
#define FIRE_FIGHTER_BULLET_H

#include "entity.h"

#include <SFML/Graphics.hpp>

class Bullet:public Entity{
public:
    Bullet(float startX, float startY);
    void update(const sf::Time& delta);
    void setSpeed(float speed);
    //sf::Vector2f getPosition() const;


private:
    sf::Sprite sprite;
    sf::Texture texture;
    float speed;
};

#endif //FIRE_FIGHTER_BULLET_H
