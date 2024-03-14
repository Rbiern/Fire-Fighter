#ifndef FIRE_FIGHTER_GAME_H
#define FIRE_FIGHTER_GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "settings.h"
#include "entity.h"
#include "player.h"
#include "powerup.h"
#include "enemy.h"

class game {
private:
    Entity temp;
    settings* options;
public:
    game();
    void gameLoop();
};


#endif //FIRE_FIGHTER_GAME_H
