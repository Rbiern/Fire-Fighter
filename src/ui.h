#ifndef FIRE_FIGHTER_UI_H
#define FIRE_FIGHTER_UI_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "settings.h"
#include "game.h"

class ui {
    // variables
private:
    sf::RenderWindow* _window;
    settings* options;
    sf::Texture backgroundImage;
    sf::Font font;
    sf::Music music;
    bool errorFlag;
    // methods
public:
    // constructor
    explicit ui(sf::RenderWindow *window1);
    void displayMenu();
    // helper methods
private:
    sf::ConvexShape createButtonShape(float windowWidth);
    bool _init();
};

#endif //FIRE_FIGHTER_UI_H
