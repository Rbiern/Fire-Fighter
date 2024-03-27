#ifndef FIRE_FIGHTER_PLAYER_H
#define FIRE_FIGHTER_PLAYER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "entity.h"
#include "bullet.h"
#include <SFML/Audio.hpp>
#include "settings.h"
#include "barrier.h"
#include "enemy.h"
#include <iostream>
#include <string>

class Player : public Entity {
public:

    Player(float startX, float startY,  const sf::Vector2u& resolution);

    virtual ~Player();

    void shoot();

    void updateBullets(const sf::Time& delta, EnemyWave& enemyWave);

    void updateBarrier(const sf::Time delta, Barrier& barrier);

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
    void increaseLife();

    bool isCollidingWithEnemy(const sf::Sprite& enemySprite) const;

    void setPlayerTexture(char *t);

private:
    float movementSpeed;
    int lives;
    sf::SoundBuffer shootBuffer;
    sf::Sound shootSound;
    std::vector<Bullet> bullets;
    settings *options;
    void setScale(float scaleFactor);
    void adjustForResolution(const sf::Vector2u &resolution);
};

#endif //FIRE_FIGHTER_PLAYER_H
