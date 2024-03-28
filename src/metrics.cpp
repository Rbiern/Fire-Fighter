#include "metrics.h"
#include <iostream>

Metrics::Metrics(sf::Vector2u windowSize, sf::Font f) : score(0), windowSize(windowSize) {
    font = f;
    scoreText.setFont(font);
    pointsText.setFont(font);
    roundText.setFont(font);
    enemyCountText.setFont(font);
    enemyKilledText.setFont(font);

    scoreText.setCharacterSize(24);
    pointsText.setCharacterSize(24);
    roundText.setCharacterSize(24);
    enemyCountText.setCharacterSize(24);
    enemyKilledText.setCharacterSize(24);

    scoreText.setFillColor(sf::Color::White);
    pointsText.setFillColor(sf::Color::White);
    roundText.setFillColor(sf::Color::White);
    enemyCountText.setFillColor(sf::Color::White);
    enemyKilledText.setFillColor(sf::Color::White);

    if (!life3Texture.loadFromFile("../../resource/img/3.png") ||
        !life2Texture.loadFromFile("../../resource/img/2.png") ||
        !life1Texture.loadFromFile("../../resource/img/1.png") ||
        !life0Texture.loadFromFile("../../resource/img/0.png")) {
        std::cerr << "Failed to load life counter textures!" << std::endl;
        return;
    }
    healthBar.setTexture(life3Texture);
    healthBar.setScale(1, 1);
    healthBar.setPosition(10, 10);

    separationLine.setSize(sf::Vector2f(windowSize.x, 2));
    separationLine.setFillColor(sf::Color::White);
    separationLine.setPosition(0, 50 + 10);
}
void Metrics::updateHealthbar(int lives){
    switch (lives) {
        case 3:
            healthBar.setTexture(life3Texture);
            break;
        case 2:
            healthBar.setTexture(life2Texture);
            break;
        case 1:
            healthBar.setTexture(life1Texture);
            break;
        case 0:
            healthBar.setTexture(life0Texture);
            break;
        default:
            break;
    }
}

void Metrics::setScore() {
    scoreText.setString("Score: " + std::to_string(score));
    scoreText.setPosition((windowSize.x - scoreText.getLocalBounds().width) / 2.f, 20.f);
}

void Metrics::setPoints(int points) {
    pointsText.setString("Points: " + std::to_string(points));
    pointsText.setPosition(windowSize.x / 2 - pointsText.getLocalBounds().width / 2, 10);
}

void Metrics::setRound(int round) {
    roundText.setString("Round: " + std::to_string(round));
    roundText.setPosition(windowSize.x - roundText.getLocalBounds().width - 20, 10);
}

void Metrics::setEnemyCount(int enemyCount) {
    enemyCountText.setString("Total Enemy: " + std::to_string(enemyCount));
    // Calculate the X position to start just to the right of the score text
    float newXPosition = scoreText.getPosition().x + scoreText.getLocalBounds().width + 20.f; // 20.f for horizontal spacing from the score
    float newYPosition = scoreText.getPosition().y; // Align vertically with the top of the score text
    enemyCountText.setPosition(newXPosition, newYPosition);
}

void Metrics::setEnemyKilled(int enemyKilled) {
    enemyKilledText.setString("Enemy Killed: " + std::to_string(enemyKilled));
    // Place directly under the "Total Enemy" text
    float newXPosition = enemyCountText.getPosition().x; // Align horizontally with the "Total Enemy" text
    float newYPosition = enemyCountText.getPosition().y + enemyCountText.getLocalBounds().height + 5.f; // Slight vertical spacing
    enemyKilledText.setPosition(newXPosition, newYPosition);
}

void Metrics::draw(sf::RenderTarget& target) {
    target.draw(scoreText);
    target.draw(pointsText);
    target.draw(roundText);
    target.draw(healthBar);
    target.draw(separationLine);
    target.draw(enemyCountText);
    target.draw(enemyKilledText);
}

void Metrics::increaseScore(int points) {
    score += points;
    setScore();
}

int Metrics::getScore() const {
    return score;
}
