#include "barrier.h"

Barrier::Barrier(settings gameSettings) {
    size = 1.0f;
    if (!iceBlockTexture.loadFromFile("../../resource/img/iceBlock.png")) {
        std::cerr << "Failed to load background image!" << std::endl;
    }
    iceBlockSprite.setTexture(iceBlockTexture);
    iceBlockSprite.setScale(gameSettings.widthScaling(1.5), gameSettings.heightScaling(1.5));
}

Barrier::~Barrier() = default;

void Barrier::setPosition(int posX, int posY) {
    iceBlockSprite.setPosition(posX, posY);
}

bool Barrier::bulletCollision(const sf::Sprite& bulletSprite) const {
    return iceBlockSprite.getGlobalBounds().intersects(bulletSprite.getGlobalBounds());
}

void Barrier::shrink() {
    // Apply the scaling factor to the size
    size -= 0.35f;
    // Ensure size doesn't go below a certain minimum value
    if (size < 0.29f) {
        size = 0.f;  // barrier disappears
    }
    // Resize the barrier sprite
    iceBlockSprite.setScale(gameSettings.widthScaling(1.5) * size, gameSettings.heightScaling(1.5) * size);
}

void Barrier::reset() {
    size = 1.0f;
    iceBlockSprite.setScale(gameSettings.widthScaling(1.4), gameSettings.heightScaling(1.4));
}

void Barrier::draw(sf::RenderWindow& window) {
    window.draw(iceBlockSprite);
}
