#ifndef FIRE_FIGHTER_UI_H
#define FIRE_FIGHTER_UI_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "settings.h"
#include "game.h"

class ui {
private:
    game* startGame;
    sf::RenderWindow window;
    settings options;
    sf::Texture backgroundImage;
    sf::Font font;
    sf::Music music;
public:
    ui();
    ~ui();
    void displayMenu();
private:
    void _init();
    sf::ConvexShape createButtonShape(float windowWidth, float startX);
};

#endif //FIRE_FIGHTER_UI_H
