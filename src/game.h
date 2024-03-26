#ifndef FIRE_FIGHTER_GAME_H
#define FIRE_FIGHTER_GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "settings.h"
#include "player.h"
#include "enemy.h"
#include "powerup.h"
#include "barrier.h"
#include "metrics.h"

class game {
private:
    settings options; // get icon, get windows size, get music, get font;
    sf::Font font;
    sf::Image icon;
    sf::Music music;
    sf::Vector2u resolution;
    sf::Clock clock; // for updating the game
    powerup Powerup;
public:
    explicit game(settings *opt);
    void gameLoop();
    char* characterSelectScreen(sf::RenderWindow& window, const Player& player);
    bool handleExitRequest(sf::RenderWindow& window);
    bool gameOverScreen(sf::RenderWindow& window);
};

#endif //FIRE_FIGHTER_GAME_H
