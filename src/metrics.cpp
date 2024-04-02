#include "metrics.h"

/**
 * @brief Constructor of Metrics.
 *
 * Initializes a Metrics object with the given window size and optional settings.
 * It calculates the height of the infoBar as 10% of the window's height and creates an infoBar accordingly.
 * Various text elements such as score, enemy killed count, round number, and enemies remaining are initialized and positioned on the infoBar.
 * Life counter textures are loaded for displaying health status, and the health bar sprite is set up accordingly.
 *
 * @param windowSize The size of the game window.
 * @param opt Optional settings for customizing the Metrics object.
 * @authors Prachi Ghevaria, Robert Andrew Biernacki
 */
Metrics::Metrics(sf::Vector2u windowSize, Settings* opt) : score(0), windowSize(windowSize) {
    // Calculate the infoBar height as 10% of the window's height
    float infoBarHeight = windowSize.y * 0.1f;

    // Load the highest score from file
    std::ifstream inFile("highestScore.txt");
    if (inFile.is_open()) {
        inFile >> highestScore;
        inFile.close();
    } else {
        std::cerr << "Unable to open file for reading highest score!" << std::endl;
    }

    // Create a infoBar that spans the width of the window and 10% of its height
    infoBar.setSize(sf::Vector2f(windowSize.x, infoBarHeight));
    infoBar.setFillColor(sf::Color(100, 100, 100)); // Set the infoBar to be blue
    infoBar.setPosition(0, 0); // Set the position to the top-left corner

    // Create a separation line below the infoBar
    separationLine.setSize(sf::Vector2f(windowSize.x, 2));
    separationLine.setFillColor(sf::Color::White);
    separationLine.setPosition(0, infoBarHeight - 3);

    options = opt; // Assign optional settings
    font = opt->getFont(); // Get font from settings

    // Initialize and position the score text
    scoreText.setFont(font);
    scoreText.setCharacterSize(opt->heightScaling(20));
    scoreText.setFillColor(sf::Color::White);
    scoreText.setString(opt->getLanguage()[22] + std::to_string(score));
    scoreText.setPosition(((windowSize.x * 0.7f) - (scoreText.getLocalBounds().width) / 2.f), (infoBarHeight/2) - (scoreText.getLocalBounds().height/2));

    // Initialize and position the enemy killed text
    enemyKilledText.setFont(font);
    enemyKilledText.setCharacterSize(opt->heightScaling(20));
    enemyKilledText.setFillColor(sf::Color::White);
    enemyKilledText.setString(opt->getLanguage()[23]+ std::to_string(score));
    enemyKilledText.setPosition((((windowSize.x) * 0.48f) - (enemyKilledText.getLocalBounds().width) / 2.f), (infoBarHeight/2) - (enemyKilledText.getLocalBounds().height/2));

    // Initialize and position the round text
    roundText.setFont(font);
    roundText.setCharacterSize(opt->heightScaling(20));
    roundText.setFillColor(sf::Color::White);
    roundText.setString(opt->getLanguage()[24] + std::to_string(score));
    roundText.setPosition((((windowSize.x) * 0.6f) - (roundText.getLocalBounds().width) / 2.f), (infoBarHeight/2) - (roundText.getLocalBounds().height/2));

    // Initialize and position the enemies remaining text
    enemiesRemainingText.setFont(font);
    enemiesRemainingText.setCharacterSize(opt->heightScaling(20));
    enemiesRemainingText.setFillColor(sf::Color::White);
    enemiesRemainingText.setString(opt->getLanguage()[25] + std::to_string(score));
    enemiesRemainingText.setPosition((((windowSize.x) * 0.3f) - (enemiesRemainingText.getLocalBounds().width) / 2.f), (infoBarHeight/2) - (enemiesRemainingText.getLocalBounds().height/2));

    // Initialize and position the highest score text
    highestScoreText.setFont(font);
    highestScoreText.setCharacterSize(opt->heightScaling(20));
    highestScoreText.setFillColor(sf::Color::White);
    highestScoreText.setString(opt->getLanguage()[26] + std::to_string(highestScore));
    highestScoreText.setPosition((((windowSize.x) * 0.82f) - (highestScoreText.getLocalBounds().width) / 2.f), (infoBarHeight/2) - (highestScoreText.getLocalBounds().height/2));

    // Load life counter textures and set up health bar sprite
    if (!life3Texture.loadFromFile("../../resource/img/3.png") ||
        !life2Texture.loadFromFile("../../resource/img/2.png") ||
        !life1Texture.loadFromFile("../../resource/img/1.png") ||
        !life0Texture.loadFromFile("../../resource/img/0.png")) {
        std::cerr << "Failed to load life counter textures!" << std::endl;
        return;
    }
    healthBar.setTexture(life3Texture);
    healthBar.setScale(opt->widthScaling(1.4), opt->widthScaling(1.4));
    healthBar.setPosition(windowSize.x * 0.03, (infoBarHeight/2) - (life3Texture.getSize().y / 2));
}

/**
 * Destructor of metrics.
 */
Metrics::~Metrics() = default;

/**
 * @brief Destructor of Metrics.
 *
 * Default destructor for the Metrics class.
 * This destructor is defaulted, meaning it does not have custom cleanup operations.
 * It will automatically release resources and memory allocated by the Metrics class.
 * @author Prachi Ghevaria
 */
void Metrics::updateHealthbar(int lives){
    switch (lives) {
        case 3:
            healthBar.setTexture(life3Texture);
            break;
        case 2:
            healthBar.setTexture(life2Texture);
            break;
        case 1:
            healthBar.setTexture(life1Texture);
            break;
        case 0:
            healthBar.setTexture(life0Texture);
            break;
        default:
            break;
    }
}

/**
 * @brief Draw the metrics elements on the specified render target.
 *
 * This function draws various metrics elements, such as the infoBar, separation line, score text, round text, health bar,
 * enemy killed text, and enemies remaining text, on the specified render target (window).
 *
 * @param window The render target (SFML RenderTarget) to draw the metrics elements on.
 * @author Prachi Ghevaria
 */
void Metrics::draw(sf::RenderTarget& window) {
    window.draw(infoBar);
    window.draw(separationLine);
    window.draw(scoreText);
    window.draw(roundText);
    window.draw(healthBar);
    window.draw(enemyKilledText);
    window.draw(enemiesRemainingText);
    window.draw(highestScoreText);
}

/**
 * @brief Draw the final score elements on the specified render target.
 *
 * This function draws the final score elements, including the score text, round text, and enemy killed text,
 * at specific positions on the specified render target (window). These elements are positioned centered horizontally
 * and vertically at one-third of the window's height.
 *
 * @param window The render target (SFML RenderTarget) to draw the final score elements on.
 */
void Metrics::drawFinalScore(sf::RenderTarget& window) {
    // Position the score text, roundtext, enemy killed text, and highest score text
    scoreText.setPosition(((windowSize.x * 0.5f) - (scoreText.getLocalBounds().width) / 2.f), (options->getResolution()[1]/3) - (scoreText.getLocalBounds().height * 8.5));
    roundText.setPosition(((windowSize.x * 0.5f) - (roundText.getLocalBounds().width) / 2.f), (options->getResolution()[1]/3) - (roundText.getLocalBounds().height * 5));
    enemyKilledText.setPosition(((windowSize.x * 0.5f) - (enemyKilledText.getLocalBounds().width) / 2.f), (options->getResolution()[1]/3) - (enemyKilledText.getLocalBounds().height * 1));
    highestScoreText.setPosition(((windowSize.x * 0.5f) - (highestScoreText.getLocalBounds().width) / 2.f), (options->getResolution()[1]/3) - (highestScoreText.getLocalBounds().height * 3));

    window.draw(scoreText);
    window.draw(roundText);
    window.draw(enemyKilledText);
    window.draw(highestScoreText);
}

/**
 * @brief Set the count of remaining enemies and updates the corresponding text.
 * 
 * This function sets the count of remaining enemies to the specified value and updates
 * the enemies remaining text accordingly.
 * 
 * @param enemyCount The count of remaining enemies.
 */
void Metrics::setEnemyCount(int enemyCount) {
    enemySum = enemyCount;
    enemiesRemainingText.setString(options->getLanguage()[25] + std::to_string(enemyCount));
}

/**
 * @brief Increases the score by the specified points and updates the corresponding texts.
 *
 * This function increases the score by the specified points and updates the score text, round text,
 * enemy killed text, and enemies remaining text accordingly.
 *
 * @param points The points to be added to the score.
 */
void Metrics::increaseScore(int points) {
    score += points;
    updateHighestScore();
    scoreText.setString(options->getLanguage()[22] + std::to_string(score));
    roundText.setString(options->getLanguage()[24]+ std::to_string(((score/points) / enemySum) + 1));
    enemyKilledText.setString(options->getLanguage()[23] + std::to_string(score/points));
    enemiesRemainingText.setString(options->getLanguage()[25] + std::to_string((enemySum - (score/points) % enemySum)));
    highestScoreText.setString(options->getLanguage()[26] + std::to_string(highestScore));
}

/**
 * @brief Update the highest score.
 *
 * This function updates the highest score if the current score is greater.
 * It also stores the highest score in a file.
 *
 */
void Metrics::updateHighestScore() {
    // Update highest score if current score is greater
    if (score > highestScore) {
        highestScore = score;

        // Store the highest score in a file
        std::ofstream outFile("highestScore.txt");
        if (outFile.is_open()) {
            outFile << highestScore;
            outFile.close();
        } else {
            std::cerr << "Unable to open file for highest score storage!" << std::endl;
        }
    }
}
/**
 * @brief Return the highest score.
 * @return int The current highest score.
 */
int Metrics::getHighestScore() const {
    // Simply return the highest score
    return highestScore;
}

/**
 * @brief Resets the metrics to their default state.
 *
 * This function resets the metrics, including the score and various text elements,
 * to their default state. It sets the score to zero and updates the score text,
 * enemy killed text, round text, and enemies remaining text accordingly.
 */
void Metrics::reset() {
    score = 0;
    float infoBarHeight = windowSize.y * 0.1f;
    healthBar.setTexture(life3Texture);

    scoreText.setString(options->getLanguage()[22] + std::to_string(score));
    scoreText.setPosition(((windowSize.x * 0.7f) - (scoreText.getLocalBounds().width) / 2.f), (infoBarHeight/2) - (scoreText.getLocalBounds().height/2));

    enemyKilledText.setString(options->getLanguage()[23]+ std::to_string(score));
    enemyKilledText.setPosition((((windowSize.x) * 0.48f) - (enemyKilledText.getLocalBounds().width) / 2.f), (infoBarHeight/2) - (enemyKilledText.getLocalBounds().height/2));

    roundText.setString(options->getLanguage()[24] + std::to_string(score));
    roundText.setPosition((((windowSize.x) * 0.6f) - (roundText.getLocalBounds().width) / 2.f), (infoBarHeight/2) - (roundText.getLocalBounds().height/2));

    enemiesRemainingText.setString(options->getLanguage()[25] + std::to_string(score));
    enemiesRemainingText.setPosition((((windowSize.x) * 0.3f) - (enemiesRemainingText.getLocalBounds().width) / 2.f), (infoBarHeight/2) - (enemiesRemainingText.getLocalBounds().height/2));

    highestScoreText.setString(options->getLanguage()[26] + std::to_string(highestScore));
    highestScoreText.setPosition((((windowSize.x) * 0.82f) - (highestScoreText.getLocalBounds().width) / 2.f), (infoBarHeight/2) - (highestScoreText.getLocalBounds().height/2));

}

/**
 * @brief Calculate the current stage based on the score and number of enemies.
 *
 * This function calculates the current stage based on the score and number of enemies.
 * It divides the score by 10 to determine the stage progression, taking into account
 * the number of enemies defeated. The stage is incremented by 1 to start from 1.
 *
 * @return int The current stage number.
 */
int Metrics::getStage() {
    return (score/10) / enemySum + 1;
}
