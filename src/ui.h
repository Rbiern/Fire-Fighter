#ifndef FIRE_FIGHTER_UI_H
#define FIRE_FIGHTER_UI_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "settings.h"
#include "game.h"

namespace mainWindow {
    class ui {
    // variables
    private:
        // required!
        sf::RenderWindow &_window;
        settings* options;
        // optional
        sf::Image icon;
        sf::Texture backgroundImage;
        sf::Font font;
        sf::Music music;
        bool errorFlag;
    // methods
    public:
        // constructor
        explicit ui(sf::RenderWindow &window1);
        void displayMenu();
    // helper methods
    private:
        bool _init();
    };
}//end of namespace mainWindow
#endif //FIRE_FIGHTER_UI_H
