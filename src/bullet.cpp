#include "bullet.h"

/**
 * Constructor of Bullet object.
 * @param startX The starting x-coordinate of the bullet.
 * @param startY The starting y-coordinate of the bullet.
 * @param type The type of bullet ("player" or "enemy").
 * @param res The resolution of the game window.
 */
Bullet::Bullet(float startX, float startY, const std::string& type, sf::Vector2u res) {
    // Load and set texture based on bullet type
    loadTexture(type);
    bulletSprite.setTexture(bulletTexture);

    // Set initial position
    bulletSprite.setPosition(startX, startY);

    // Set scale based on bullet type and game resolution
    if (type == "enemy"){
        bulletSprite.setScale(0.5f * ((float)res.x/1280.f), 0.5f * ((float)res.y/720.f));
    }
    else{
        if(res.x == 3840){
            bulletSprite.setScale(0.5f * ((float)res.x/1280.f), 0.5f * ((float)res.y/720.f));
        }else{
            bulletSprite.setScale(1.2f * ((float)res.x/1280.f), 1.2f * ((float)res.y/720.f));
        }
    }

    // Set default speed
    speed = 300.f;
}

/**
 * Destructor of the Bullet object.
 */
Bullet::~Bullet() = default;

/**
 * Update the position of the bullet.
 * @param delta The elapsed time since the last update.
 * @param type The type of bullet ("player" or "enemy").
 */
void Bullet::update(const sf::Time& delta, const std::string& type) {
    if (type == "enemy"){
        bulletSprite.move(speed * delta.asSeconds(), 0); // Move bullet to the right
    }
    else if(type == "player"){
        bulletSprite.move(-speed * delta.asSeconds(), 0); // Move bullet to the left
    }
}

/**
 * Draw the bullet sprite.
 * @param window The SFML render window to draw the bullet on.
 * @param type The type of bullet ("player" or "enemy").
 */
void Bullet::draw(sf::RenderWindow& window, const std::string &type) {
    // Load texture based on bullet type
    loadTexture(type);

    // Draw bullet sprite on the render window
    window.draw(bulletSprite);
}

/**
 * Return the global bounding rectangle of the bullet sprite.
 * @return The global bounding rectangle of the bullet sprite.
 */
sf::FloatRect Bullet::getGlobalBounds() const {
    return bulletSprite.getGlobalBounds();
}

/**
 * Return the bullet sprite.
 * @return A constant reference to the bullet sprite.
 */
const sf::Sprite& Bullet::getSprite() const {
    return bulletSprite;
}

/**
 * Load the texture of the bullet.
 * @param type The type of bullet ("player" or "enemy").
 */
void Bullet::loadTexture(const std::string &type) {
    // Load file based on the type and print error message if fails
    if (type =="player" && !bulletTexture.loadFromFile("../../resource/img/droplet.png")) {
        std::cerr << "Failed to load player's bullet texture" << std::endl;
    }
    else if(type =="enemy" && !bulletTexture.loadFromFile("../../resource/img/fireball.png")) {
        std::cerr << "Failed to load enemy's bullet texture" << std::endl;
    }

    // Set the loaded texture to the bullet sprite
    bulletSprite.setTexture(bulletTexture);
}
