#ifndef FIRE_FIGHTER_GAME_H
#define FIRE_FIGHTER_GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "settings.h"
#include "entity.h"
#include "player.h"
#include "enemy.h"
#include "powerup.h"
#include "barrier.h"
#include "metrics.h"


class game {
private:
    Entity temp;
    sf::Font font;
    settings options; // get icon, get windows size, get music, get font;
    sf::Clock clock;
    sf::Image icon;
    sf::Music music;

public:
    game(settings *opt);
    void gameLoop();
};


#endif //FIRE_FIGHTER_GAME_H
