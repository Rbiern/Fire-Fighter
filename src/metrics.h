#ifndef FIRE_FIGHTER_METRICS_H
#define FIRE_FIGHTER_METRICS_H

#include <SFML/Graphics.hpp>
#include <string>

class Metrics {
private:
    sf::Vector2u windowSize;
    sf::Font font;
    sf::Text scoreText, pointsText, roundText, enemyCountText, enemyKilledText;
    sf::RectangleShape separationLine;
    int score;
public:
    Metrics(sf::Vector2u windowSize, sf::Font f);
    void setScore();
    void setPoints(int points);
    void setRound(int round);
    void setEnemyCount(int enemyCount);
    void setEnemyKilled(int enemyKilled);
    void draw(sf::RenderTarget& target);
    void updateHealthbar(int lives);
    sf::Texture life3Texture;
    sf::Texture life2Texture;
    sf::Texture life1Texture;
    sf::Texture life0Texture;
    sf::Sprite healthBar;
    void increaseScore(int points);
    int getScore() const;
};

#endif //FIRE_FIGHTER_METRICS_H
