#ifndef FIRE_FIGHTER_PLAYER_H
#define FIRE_FIGHTER_PLAYER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "entity.h"
#include "bullet.h"
#include <SFML/Audio.hpp>
#include "settings.h"
#include "bullet.h"
#include <iostream>

class Player : public Entity {
public:

    Player(float startX, float startY);

    virtual ~Player();

    void shoot();

    void updateBullets(const sf::Time& delta);


    void drawBullets(sf::RenderWindow& window);


    void move(const sf::Vector2f& direction) ;
    void draw(sf::RenderWindow& window) ;


    void setSpeed(float speed);
    float getSpeed() const;


    sf::Vector2f getSize() const ;
    //sf::Vector2f getPosition() const;


    void setLives(int lives);
    int getLives() const;
    void decreaseLife();

    bool isCollidingWithEnemy(const sf::Sprite& enemySprite) const;

private:
    float movementSpeed;
    int lives;
    sf::SoundBuffer shootBuffer;
    sf::Sound shootSound;
    std::vector<Bullet> bullets; // 발사된 총알을 저장하는 컨테이너
    settings *options;
};

#endif //FIRE_FIGHTER_PLAYER_H
