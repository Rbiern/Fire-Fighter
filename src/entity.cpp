#include "entity.h"

entity::entity() {
    // Create a character
    character.setSize(sf::Vector2f(50.f, 50.f));
    character.setFillColor(sf::Color::Green);
    character.setPosition(400.f, 300.f);
}

sf::RectangleShape entity::getEntity() {
    return character;
}

float entity::getSpeed() {
    return 0.5f;
}
