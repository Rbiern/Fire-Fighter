//
// Created by Pc MSI on 2024-03-09.
//

#ifndef FIRE_FIGHTER_METRICS_H
#define FIRE_FIGHTER_METRICS_H

#include <SFML/Graphics.hpp>
#include <string>

class metrics {
public:
    metrics(sf::Vector2u windowSize)
            : windowSize(windowSize) {
        // Load the font
        if (!font.loadFromFile("../../resource/fonts/Rajdhani-SemiBold.ttf")) {
            // Handle error
        }

        // Initialize text objects
        scoreText.setFont(font);
        pointsText.setFont(font);
        roundText.setFont(font);
        scoreText.setCharacterSize(24); // Example size
        pointsText.setCharacterSize(24);
        roundText.setCharacterSize(24);
        scoreText.setFillColor(sf::Color::White);
        pointsText.setFillColor(sf::Color::White);
        roundText.setFillColor(sf::Color::White);

        // Load the texture for the health bar
        if (!healthTexture.loadFromFile("../../resource/img/3.png")) {
            // Handle error
        }
        healthBar.setTexture(healthTexture);

        // Scale health bar to fit the info bar height if necessary
//        float scaleY = (float)desiredInfoBarHeight / healthTexture.getSize().y;
        healthBar.setScale(1, 1);

        // Position the health bar
        healthBar.setPosition(10, 10); // Adjust as needed


        separationLine.setSize(sf::Vector2f(windowSize.x, 2)); // Set the height to 2 for a thin line
        separationLine.setFillColor(sf::Color::White);
        separationLine.setPosition(0, 50 + 10); // Adjust the Y position based on the height of your info bar
    }

    void setScore(int score) {
        scoreText.setString("Score: " + std::to_string(score));
    }

    void setPoints(int points) {
        pointsText.setString("Points: " + std::to_string(points));
        // Adjust position based on window size and text width
        pointsText.setPosition(windowSize.x / 2 - pointsText.getLocalBounds().width / 2, 10);
    }

    void setRound(int round) {
        roundText.setString("Round: " + std::to_string(round));
        // Position it to the right
        roundText.setPosition(windowSize.x - roundText.getLocalBounds().width - 20, 10);
    }

    void draw(sf::RenderTarget& target) {
        target.draw(scoreText);
        target.draw(pointsText);
        target.draw(roundText);
        target.draw(healthBar);
        target.draw(separationLine); // Draw the separation line
    }

private:
    sf::Vector2u windowSize;
    sf::Font font;
    sf::Text scoreText, pointsText, roundText;
    sf::Texture healthTexture;
    sf::Sprite healthBar;
    sf::RectangleShape separationLine;
};

#endif //FIRE_FIGHTER_METRICS_H
