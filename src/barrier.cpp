#include "barrier.h"

/**
 * Constructor of a Barrier object.
 * @param gameSettings The game settings that are set by the user.
 */
Barrier::Barrier(Settings gameSettings) {
    // Set default size
    size = 1.0f;

    // Load barrier texture
    if (!iceBlockTexture.loadFromFile("../../resource/img/iceBlock.png")) {
        std::cerr << "Failed to load background image!" << std::endl;
    }

    // Load shrink sound buffer
    if (!shrinkBuffer.loadFromFile("../../resource/sounds/melt.mp3")) {
        std::cerr << "Shrink sound could not be loaded" << std::endl;
    }

    // Set the sound buffer for the shrink sound
    shrinkSound.setBuffer(shrinkBuffer);

    // Set texture for the barrier sprite
    iceBlockSprite.setTexture(iceBlockTexture);

    // Scale the bullet sprite based on resolution from game settings
    if(gameSettings.getVector().x == 3840){
        iceBlockSprite.setScale(gameSettings.widthScaling(0.75), gameSettings.heightScaling(0.75));
    }else{
        iceBlockSprite.setScale(gameSettings.widthScaling(1.5), gameSettings.heightScaling(1.5));
    }
}

/**
 * Destructor of a Barrier object.
 */
Barrier::~Barrier() = default;

/**
 * Set the position of the Barrier object.
 * @param posX The x-coordinate of the new position.
 * @param posY The y-coordinate of the new position.
 */
void Barrier::setPosition(int posX, int posY) {
    iceBlockSprite.setPosition(posX, posY);
}

/**
 * Check if the bullet collides the Barrier object.
 * @param bulletSprite sprite of the bullet
 * @return True if there is a collision, false otherwise.
 */
bool Barrier::bulletCollision(const sf::Sprite& bulletSprite) const {
    return iceBlockSprite.getGlobalBounds().intersects(bulletSprite.getGlobalBounds());
}

/**
 * Shrink the Barrier object.
 */
void Barrier::shrink() {
    // Check if sound effect is enabled in the game settings
    if (gameSettings.toggleSounds()) {
        // Play the shrink sound effect
        shrinkSound.play();
    }

    // Apply the scaling factor to the size
    size -= 0.25f;

    // Ensure size doesn't go below a certain minimum value
    if (size < 0.29f) {
        size = 0.f;  // barrier disappears
    }

    // Resize the barrier bulletSprite
    if(gameSettings.getVector().x == 3840){
        iceBlockSprite.setScale(gameSettings.widthScaling(0.75)* size, gameSettings.heightScaling(0.75)* size);
    }else{
        iceBlockSprite.setScale(gameSettings.widthScaling(1.5)* size, gameSettings.heightScaling(1.5)* size);
    }
}

/**
 * Reset the Barrier object to its default state.
 */
void Barrier::reset() {
    // Set default size
    size = 1.0f;

    // Scale the bullet sprite based on resolution from game settings
    if(gameSettings.getVector().x == 3840){
        iceBlockSprite.setScale(gameSettings.widthScaling(0.75), gameSettings.heightScaling(0.75));
    }else{
        iceBlockSprite.setScale(gameSettings.widthScaling(1.5), gameSettings.heightScaling(1.5));
    }
}

/**
 * Draw the Barrier object.
 * @param window The SFML render window on which to draw the Barrier.
 */
void Barrier::draw(sf::RenderWindow& window) {
    window.draw(iceBlockSprite);
}
