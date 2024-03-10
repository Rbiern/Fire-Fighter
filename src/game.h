#ifndef FIRE_FIGHTER_GAME_H
#define FIRE_FIGHTER_GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "settings.h"
#include "entity.h"

class game {
private:
    entity temp;
    settings* options;
public:
    game();
    void gameLoop();
};


#endif //FIRE_FIGHTER_GAME_H