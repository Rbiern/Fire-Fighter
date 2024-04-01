#ifndef FIRE_FIGHTER_METRICS_H
#define FIRE_FIGHTER_METRICS_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "settings.h"

class Metrics {
private:
    int highestScore;
    sf::RectangleShape infoBar;
    sf::RectangleShape separationLine;
    sf::Font font;
    sf::Vector2u windowSize;
    sf::Text scoreText;
    sf::Text roundText;
    sf::Text enemyKilledText;
    sf::Text enemiesRemainingText;
    sf::Text highestScoreText;
    Settings* options;
    int score;
    int enemySum;
    sf::Texture life3Texture;
    sf::Texture life2Texture;
    sf::Texture life1Texture;
    sf::Texture life0Texture;
    sf::Sprite healthBar;
public:
    Metrics(sf::Vector2u windowSize, Settings* opt);
    ~Metrics();
    void draw(sf::RenderTarget& target);
    void drawFinalScore(sf::RenderTarget& target);
    void updateHealthbar(int lives);
    void setEnemyCount(int enemyCount);
    void increaseScore(int points);
    void updateHighestScore();
    int getHighestScore() const;
    int getStage();
    void reset();
};

#endif //FIRE_FIGHTER_METRICS_H
