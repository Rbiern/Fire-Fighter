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
    sf::RenderWindow window;
    settings options; // get icon, get windows size, get music, get font;
    sf::Font font;
    sf::Image icon;
    sf::Music music;
    sf::Vector2u resolution;
    sf::Clock clock; // for updating the game
    Metrics metrics;
    Barrier barrier1;
    Barrier barrier2;
    Barrier barrier3;
    powerup Powerup;
    Player* player;
    EnemyWave* enemyWave;
public:
    explicit game(settings *opt);
    ~game();
    void gameLoop();
    char* characterSelectScreen();
    bool handleExitRequest();
    bool gameOverScreen();
};

#endif //FIRE_FIGHTER_GAME_H
