#include "ui.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(640, 360), "Fire Fighter"); //make new window
    ui program(&window); // initialize ui window
    program.displayMenu(); // method from ui to run the main program loop
    return 0;
}
