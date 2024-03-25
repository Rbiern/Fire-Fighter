#ifndef FIRE_FIGHTER_METRICS_H
#define FIRE_FIGHTER_METRICS_H

#include <SFML/Graphics.hpp>
#include <string>
#include "player.h"

class Metrics {
public:
    Metrics(sf::Vector2u windowSize);

    void setScore();
    void setPoints(int points);
    void setRound(int round);
    void draw(sf::RenderTarget& target);
    void updateHealthbar(int lives);
    sf::Texture life3Texture;
    sf::Texture life2Texture;
    sf::Texture life1Texture;
    sf::Texture life0Texture;
    sf::Sprite healthBar;
    void increaseScore(int points);
    int getScore() const;

private:
    int score;
    sf::Vector2u windowSize;
    sf::Font font;
    sf::Text scoreText, pointsText, roundText;

    sf::RectangleShape separationLine;
};

#endif //FIRE_FIGHTER_METRICS_H
