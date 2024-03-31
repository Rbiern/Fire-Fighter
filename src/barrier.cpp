#include "barrier.h"

Barrier::Barrier(float barrierX, float barrierY, sf::RenderWindow& window, settings gameSettings) : Entity(),
size(1.0f), scaleFactor(1.0f), referenceWidth(1280.0f), referenceHeight(720.0f), barrierSpacing(150.0f), gameSettings(gameSettings){
    this->setTexture("../../resource/img/iceBlock.png");
    this->setPosition(barrierX, barrierY);

    resolution = gameSettings.getVector();
    adjustForResolution(resolution);
    adjustSpacingForResolution(window, resolution);
}

bool Barrier::bulletCollision(const sf::Sprite& bulletSprite) const {
    return sprite.getGlobalBounds().intersects(bulletSprite.getGlobalBounds());
}

void Barrier::shrink() {

    // Calculate the scaling factor based on the reference resolution
    scaleFactor = gameSettings.widthScaling(referenceWidth) / gameSettings.heightScaling(referenceHeight);

    // Apply the scaling factor to the size
    size /= scaleFactor;

    minimumSize = 0.2f * gameSettings.heightScaling(1.0f);

    // Ensure size doesn't go below a certain minimum value
    if (size < minimumSize) {
        size = 0;  // barrier disappears
    }

    // Resize the barrier sprite
    sf::Vector2f scale(size, size);
    sprite.setScale(scale);
}

void Barrier::reset(const sf::Vector2u& resolution) {
    adjustForResolution(resolution);
}

//void Barrier::respawn(const sf::Vector2f& position, const sf::Vector2u& resolution) {
//
//    setPosition(position); // Set the position of the barrier
//    reset(resolution); // Reset the barrier size based on the resolution
//
//}


void Barrier::adjustForResolution(const sf::Vector2u& resolution) {

    // Reference resolution
    const sf::Vector2u referenceResolution = sf::Vector2u(referenceWidth, referenceHeight);

    // Calculate the size ratio based on the reference resolution
    float widthRatio = static_cast<float>(resolution.x) / referenceResolution.x;
    float heightRatio = static_cast<float>(resolution.y) / referenceResolution.y;
    float resolutionRatio = std::min(widthRatio, heightRatio);

    // Adjust the size based on the resolution ratio
    size = 2.0f * resolutionRatio;

    // Set the scale of the barrier sprite
    sf::Vector2f scale(size, size);
    sprite.setScale(scale);

}

void Barrier::adjustSpacingForResolution(const sf::RenderWindow& window, const sf::Vector2u& resolution) {
    // Calculate the scaling factor based on the reference resolution
    float heightRatio = static_cast<float>(resolution.y) / referenceHeight;
    float availableHeight = window.getSize().y - 90.0f; // Subtract some margin from the bottom

    // Calculate the spacing between barriers
    barrierSpacing = availableHeight / 4;

    // Adjust the spacing based on the resolution ratio
    barrierSpacing *= heightRatio;

    // Ensure the minimum barrier spacing
    float minSpacing = getSize().y * 1.5f; // Minimum spacing between barriers
    barrierSpacing = std::max(barrierSpacing, minSpacing);

    // Ensure the maximum barrier spacing based on window size
    float maxSpacing = window.getSize().y * 0.25f; // Maximum spacing as 15% of window height
    barrierSpacing = std::min(barrierSpacing, maxSpacing);
}

void Barrier::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

float Barrier::getBarrierSpacing() {
    return barrierSpacing;
}

sf::Vector2f Barrier::getSize() const {
    return sprite.getGlobalBounds().getSize();
}

//
//sf::Vector2f Barrier::getPosition() const {
//    return sprite.getPosition();
//}

Barrier::~Barrier() {

}
