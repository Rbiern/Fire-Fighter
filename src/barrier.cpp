#include "barrier.h"

Barrier::Barrier(float startX, float startY, const sf::Vector2u& resolution) : Entity() {
    this->setTexture("../../resource/img/iceBlock.png");
    this->setPosition(startX, startY);
    adjustForResolution(resolution);
    adjustSpacingForResolution(resolution);
}

bool Barrier::enemyCollision(const Enemy& enemy) const {
    return sprite.getGlobalBounds().intersects(enemy.getGlobalBounds());
}

bool Barrier::bulletCollision(const sf::Sprite& bulletSprite) const {
    return sprite.getGlobalBounds().intersects(bulletSprite.getGlobalBounds());
}

void Barrier::shrink(const sf::Vector2u& resolution) {
    // Calculate the new size based on resolution
    float scaleFactor = 1.0f;
    float minimumSize = 1.3f;  // Default minimum size

    if (resolution == sf::Vector2u(640, 360)) {
        scaleFactor = 0.5f;  // Adjust based on low resolution
        minimumSize = 0.2f; // Adjust minimum size for low resolution
    } else if (resolution == sf::Vector2u(1280, 720)) {
        scaleFactor = 0.7f;  // Adjust for medium resolution
        minimumSize = 0.9f; // Adjust minimum size for medium resolution
    } else if (resolution == sf::Vector2u(1920, 1080)) {
        scaleFactor = 0.83f;  // Adjust for higher resolution
        minimumSize = 2.1f; // Adjust minimum size for higher resolution
    } else if (resolution == sf::Vector2u(3840, 2160)) {
        scaleFactor = 0.9f;  // Adjust for 4K resolution
        minimumSize = 3.2f; // Adjust minimum size for 4K resolution
    }

    // Calculate the new size with the scaleFactor
    size *= scaleFactor;

    // Ensure size doesn't go below the minimum value
    if (size < minimumSize) {
        size = 0;  // barrier disappears
    }

    // Resize the barrier sprite
    sf::Vector2f scale(size, size);
    sprite.setScale(scale);
}

void Barrier::reset(const sf::Vector2u& resolution) {
    float referenceWidth = 1920.0f; // Reference width for size calculation
    float referenceHeight = 1080.0f; // Reference height for size calculation

    // Calculate the ratio of the current resolution to the reference resolution
    float widthRatio = resolution.x / referenceWidth;
    float heightRatio = resolution.y / referenceHeight;

    size = 3.5f * std::min(widthRatio, heightRatio);
    sf::Vector2f scale(size, size);
    sprite.setScale(scale);
}

void Barrier::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

void Barrier::adjustForResolution(const sf::Vector2u& resolution) {

    float referenceWidth = 1920.0f; // Reference width for size calculation
    float referenceHeight = 1080.0f; // Reference height for size calculation

    // Calculate the ratio of the current resolution to the reference resolution
    float widthRatio = resolution.x / referenceWidth;
    float heightRatio = resolution.y / referenceHeight;

    // Calculate the size of the barrier based on the resolution ratio
    size = 3.5f * std::min(widthRatio, heightRatio);

    // Set the scale of the barrier sprite
    sf::Vector2f scale(size, size);
    sprite.setScale(scale);

}

float Barrier::adjustSpacingForResolution(const sf::Vector2u& resolution) {
    float referenceHeight = 1080.0f; // Reference height for spacing calculation
    float heightRatio = resolution.y / referenceHeight; // Calculate the ratio of the current resolution to the reference height

    // Adjust the spacing based on the resolution ratio
    barrierSpacing *= heightRatio;
    return barrierSpacing;
}

// In BarrierWave constructor
//BarrierWave::BarrierWave(sf::RenderWindow& window, const sf::Vector2u& resolution)
//        : barrierRows(3), barrierColumns(1), barrierSpacing(100.0f) { // Adjust the default spacing here
//    adjustSpacingForResolution(resolution); // Adjust spacing based on resolution
//    barriers.resize(barrierRows, std::vector<Barrier>(barrierColumns, Barrier(0, 0, resolution))); // Resize the barriers vector
//
//    // Calculate the starting position of the barriers
//    float startX = (window.getSize().x - 100) / 2.f; // Center the barriers horizontally
//    float startY = 50.0f; // Initial vertical position of the first barrier
//
//    // Create barriers and position them vertically
//    for (int i = 0; i < barrierRows; ++i) {
//        for (int j = 0; j < barrierColumns; ++j) {
//            barriers[i][j] = Barrier(startX, startY + i * barrierSpacing, resolution); // Adjust vertical position based on spacing
//            barriers[i][j].setTexture("barrier_texture_path.png"); // Set the barrier texture path
//        }
//    }
//}

//float BarrierWave::adjustSpacingForResolution(const sf::Vector2u& resolution) {
//    float referenceHeight = 1080.0f; // Reference height for spacing calculation
//    float heightRatio = resolution.y / referenceHeight; // Calculate the ratio of the current resolution to the reference height
//
//    // Adjust the spacing based on the resolution ratio
//    barrierSpacing *= heightRatio;
//    return barrierSpacing;
//}

//sf::Vector2f Barrier::getSize() const {
//    return sprite.getGlobalBounds().getSize();
//}
//
//sf::Vector2f Barrier::getPosition() const {
//    return sprite.getPosition();
//}

Barrier::~Barrier() {

}
