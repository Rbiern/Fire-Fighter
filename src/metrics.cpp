#include "metrics.h"

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

    separationLine.setSize(sf::Vector2f(windowSize.x, 2));
    separationLine.setFillColor(sf::Color::White);
    separationLine.setPosition(0, infoBarHeight - 3);

    options = opt;
    font = opt->getFont();

    scoreText.setFont(font);
    scoreText.setCharacterSize(opt->heightScaling(20));
    scoreText.setFillColor(sf::Color::White);
    scoreText.setString(opt->getLanguage()[22] + std::to_string(score));
    scoreText.setPosition(((windowSize.x * 0.3f) - (scoreText.getLocalBounds().width) / 2.f), (infoBarHeight/2) - (scoreText.getLocalBounds().height/2));

    enemyKilledText.setFont(font);
    enemyKilledText.setCharacterSize(opt->heightScaling(20));
    enemyKilledText.setFillColor(sf::Color::White);
    enemyKilledText.setString(opt->getLanguage()[23]+ std::to_string(score));
    enemyKilledText.setPosition((((windowSize.x) * 0.4f) - (enemyKilledText.getLocalBounds().width) / 2.f), (infoBarHeight/2) - (enemyKilledText.getLocalBounds().height/2));

    roundText.setFont(font);
    roundText.setCharacterSize(opt->heightScaling(20));
    roundText.setFillColor(sf::Color::White);
    roundText.setString(opt->getLanguage()[24] + std::to_string(score));
    roundText.setPosition((((windowSize.x) * 0.5f) - (roundText.getLocalBounds().width) / 2.f), (infoBarHeight/2) - (roundText.getLocalBounds().height/2));

    enemiesRemainingText.setFont(font);
    enemiesRemainingText.setCharacterSize(opt->heightScaling(20));
    enemiesRemainingText.setFillColor(sf::Color::White);
    enemiesRemainingText.setString(opt->getLanguage()[25] + std::to_string(score));
    enemiesRemainingText.setPosition((((windowSize.x) * 0.65f) - (enemiesRemainingText.getLocalBounds().width) / 2.f), (infoBarHeight/2) - (enemiesRemainingText.getLocalBounds().height/2));

    highestScoreText.setFont(font);
    highestScoreText.setCharacterSize(opt->heightScaling(20));
    highestScoreText.setFillColor(sf::Color::White);
    highestScoreText.setString("Highest Score" + std::to_string(score));
    highestScoreText.setPosition((((windowSize.x) * 0.8f) - (highestScoreText.getLocalBounds().width) / 2.f), (infoBarHeight/2) - (highestScoreText.getLocalBounds().height/2));
    
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

Metrics::~Metrics() = default;

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

void Metrics::drawFinalScore(sf::RenderTarget& window) {
    scoreText.setPosition(((windowSize.x * 0.5f) - (scoreText.getLocalBounds().width) / 2.f), (options->getResolution()[1]/3) - (scoreText.getLocalBounds().height * 5));
    roundText.setPosition(((windowSize.x * 0.5f) - (roundText.getLocalBounds().width) / 2.f), (options->getResolution()[1]/3) - (roundText.getLocalBounds().height * 3));
    enemyKilledText.setPosition(((windowSize.x * 0.5f) - (enemyKilledText.getLocalBounds().width) / 2.f), (options->getResolution()[1]/3) - (enemyKilledText.getLocalBounds().height * 6));
    highestScoreText.setPosition(((windowSize.x * 0.5f) - (highestScoreText.getLocalBounds().width) / 2.f), (options->getResolution()[1]/3) - (highestScoreText.getLocalBounds().height * 1));
    window.draw(scoreText);
    window.draw(roundText);
    window.draw(enemyKilledText);
    window.draw(highestScoreText);
}

void Metrics::setEnemyCount(int enemyCount) {
    enemySum = enemyCount;
    enemiesRemainingText.setString(options->getLanguage()[25] + std::to_string(enemyCount));
}

void Metrics::increaseScore(int points) {
    score += points;
    updateHighestScore();
    scoreText.setString(options->getLanguage()[22] + std::to_string(score));
    roundText.setString(options->getLanguage()[24]+ std::to_string(((score/points) / enemySum) + 1));
    enemyKilledText.setString(options->getLanguage()[23] + std::to_string(score/points));
    enemiesRemainingText.setString(options->getLanguage()[25] + std::to_string((enemySum - (score/points) % enemySum)));
    highestScoreText.setString("Highest Score:" + std::to_string(highestScore));
}

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

int Metrics::getHighestScore() const {
    // Simply return the highest score
    return highestScore;
}

void Metrics::reset() {
    score = 0;
    float infoBarHeight = windowSize.y * 0.1f;
    healthBar.setTexture(life3Texture);

    scoreText.setString(options->getLanguage()[22] + std::to_string(score));
    scoreText.setPosition(((windowSize.x * 0.3f) - (scoreText.getLocalBounds().width) / 2.f), (infoBarHeight/2) - (scoreText.getLocalBounds().height/2));

    enemyKilledText.setString(options->getLanguage()[23]+ std::to_string(score));
    enemyKilledText.setPosition((((windowSize.x) * 0.4f) - (enemyKilledText.getLocalBounds().width) / 2.f), (infoBarHeight/2) - (enemyKilledText.getLocalBounds().height/2));

    roundText.setString(options->getLanguage()[24] + std::to_string(score));
    roundText.setPosition((((windowSize.x) * 0.5f) - (roundText.getLocalBounds().width) / 2.f), (infoBarHeight/2) - (roundText.getLocalBounds().height/2));

    enemiesRemainingText.setString(options->getLanguage()[25] + std::to_string(score));
    enemiesRemainingText.setPosition((((windowSize.x) * 0.65f) - (enemiesRemainingText.getLocalBounds().width) / 2.f), (infoBarHeight/2) - (enemiesRemainingText.getLocalBounds().height/2));

    highestScoreText.setString("Highest Score:" + std::to_string(score));
    highestScoreText.setPosition((((windowSize.x) * 0.8f) - (highestScoreText.getLocalBounds().width) / 2.f), (infoBarHeight/2) - (highestScoreText.getLocalBounds().height/2));
    
}

int Metrics::getStage() {
    return (score/10) / enemySum + 1;
}
