#include "game.h"

/** constructor */
Game::Game(Settings *opt) : metrics(opt->getVector(), opt), barrier1(*opt), barrier2(*opt), barrier3(*opt) {
    options = *opt;             // settings
    font = options.getFont();   // load font from settings
    icon = options.getIcon();   // load icon from settings
    if (options.toggleMusic()) {// check if music is enabled, if so, load it into memory
        if (!music.openFromFile("../../music/rglk2theme2distort.mp3"))
            std::cerr << "Failed to load music" << std::endl;
        music.setLoop(true);
    }
    resolution = opt->getVector();
    // setup window, fame rate, and icon
    sf::VideoMode fullScreenMode = sf::VideoMode::getDesktopMode();
    window.create((options.isFullScreen()) ? fullScreenMode : sf::VideoMode(options.getResolution()[0],options.getResolution()[1]), "Fire Fighter", (options.isFullScreen() || options.getResolution()[0] >= fullScreenMode.width) ? sf::Style::Fullscreen : sf::Style::Default);
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr()); // Set the window icon
    window.setFramerateLimit(60);

    player = new Player(window);
    enemyWave = new EnemyWave(window, options.getVector(), options.getVector().y *0.1f);
}

/** destructor */
Game::~Game() {
    if (window.isOpen()) {
        window.close();
    }
    if (player != nullptr) {
        delete player;
        player = nullptr;
    }
    if (enemyWave != nullptr) {
        delete enemyWave;
        enemyWave = nullptr;
    }
}

/** run game method */
void Game::gameLoop() {
    char* str = characterSelectScreen();                           // character selection screen method call
    if (str == NULL) return;                                       // an error has occurred or user exited back to UI
    else player->setPlayerTexture(str);                         // test player texture to selected file path of str

    spetsnaz:

    // setup barrier
    int useableHeight = options.getResolution()[1] - (options.getResolution()[1] * 0.1f);
    barrier1.setPosition(options.getResolution()[0] * 0.83f, useableHeight * 0.25f);
    barrier2.setPosition(options.getResolution()[0] * 0.83f, useableHeight * 0.55f);
    barrier3.setPosition(options.getResolution()[0] * 0.83f, useableHeight * 0.85f);

    //set up enemy
    float metricsBarHeight = options.getVector().y *0.1;                                // Example height, adjust as needed
    metrics.setEnemyCount(enemyWave->getTotalSpawned());             // setup metrics bar on top of the window

    sf::Clock shootCooldown;                                        // for shooting cool down
    bool canShoot = true;
    float movementSpeed = 0.5f;
    if (options.toggleMusic()) music.play();                        // start the music if it is enabled
    bool restFlag = false;

    /********************************************/
    // Create the rounded rectangle shape (using a simple rectangle for demonstration)
    sf::RectangleShape roundedRect(sf::Vector2f(options.widthScaling(300), options.heightScaling(100))); // Set the size of your button
    roundedRect.setFillColor(sf::Color(231, 76, 60)); // Button color
    roundedRect.setOutlineColor(sf::Color(150, 40, 27)); // Outline color

    // Center the button on the screen
    roundedRect.setOrigin(roundedRect.getSize() / 2.f);
    roundedRect.setPosition(window.getSize().x / 2.f, window.getSize().y / 2.f);

    // Create the stageText
    sf::Text stageText("Stage: 1", font, options.widthScaling(50)); // Adjust the size accordingly
    stageText.setFillColor(sf::Color::White); // Text color

    // Center the stageText on the button
    sf::FloatRect textRect = stageText.getLocalBounds();
    stageText.setOrigin(textRect.left + textRect.width / 2.0f,
                        textRect.top  + textRect.height / 2.0f);
    stageText.setPosition(roundedRect.getPosition());

    sf::Clock clock2;
    float time = 0;
    int stage = 1;
    const float fadeInDuration = 1.0f; // Duration of the fade in seconds
    const float fadeOutDuration = 1.0f; // Duration of the fade out in seconds

/****************************/
/** main game loop */
    while (window.isOpen()) {
        sf::Event event{};
        sf::Time deltaTime = clock.restart();
        // when user closes the window through press of X or red dot on mac, close game loop
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // Move character North
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            if (player->getPosition().y - movementSpeed >= window.getSize().y * 0.1f) {
                player->move(sf::Vector2f(0.f, -movementSpeed));
            }
        }
        // Move character South
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            if (player->getPosition().y + player->getSize().y + movementSpeed <= window.getSize().y) {
                player->move(sf::Vector2f(0.f, movementSpeed));
            }
        }
        // when user presses exit, pop up window
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            if (options.toggleMusic()) music.stop();
            bool flag = handleExitRequest();
            if (flag) window.close();
        }
        // when the game has ended
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
            if (options.toggleMusic()) music.stop();
            bool flag = gameOverScreen();
            if (!flag) restFlag = true;
            window.close();
        }
        // have player shoot when space bar is pressed
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && canShoot) {
            player->shoot();
            shootCooldown.restart();
            canShoot = false;
        }
        if (shootCooldown.getElapsedTime().asSeconds() > 0.5f) {
            canShoot = true;
        }

        // Update enemy movement and shooting
        for (int i = 0; i < enemyWave->getRows(); ++i) {
            for (int j = 0; j < enemyWave->getColumns(); ++j) {
                enemyWave->getEnemy(i, j).update(deltaTime);

                // Check if the enemy has no other enemy on its right
                bool hasEnemyOnRight = (j < enemyWave->getColumns() - 1) && enemyWave->getEnemy(i, j+1).getIsAlive();

                // Get a random shoot interval between 1 and 3 seconds
                static std::vector<sf::Clock> enemyShootClocks(enemyWave->getRows()); // Static to persist between frames
                static std::random_device rd;
                static std::mt19937 gen(rd());
                static std::uniform_int_distribution<> dis(2, 13);

                // Check if enough time has passed since the last shot for this enemy
                if (!hasEnemyOnRight && enemyShootClocks[i].getElapsedTime().asSeconds() >= dis(gen) &&  enemyWave->getEnemy(i, j).getIsAlive() ) {
                    enemyWave->getEnemy(i, j).shoot();
                    enemyShootClocks[i].restart(); // Reset the shoot timer
                }
            }
        }

        int lives = player->getLives();
        metrics.updateHealthbar(lives);

        powerup.update(deltaTime, player, window);
        player->updateBullets(deltaTime, *enemyWave, metrics);
        if (enemyWave->allEnemiesDead()) {
            enemyWave->respawnEnemies(0); // Respawn with increased speed
        }
        /** end of enemy stuff */
        // Update and draw enemies using EnemyWave
        enemyWave->update(metricsBarHeight);

        //check enemy's bullet collide with player
        for (int i = 0; i < enemyWave->getRows(); ++i) {
            for (int j = 0; j < enemyWave->getColumns(); ++j) {
                Enemy &enemy = enemyWave->getEnemy(i, j);
                auto& bullets = enemy.getBullets();
                auto bulletIt = bullets.begin();
                while (bulletIt != bullets.end()) {
                    bool bulletRemoved = false;
                    if (bulletIt->getGlobalBounds().intersects(player->getSprite().getGlobalBounds())) {
                        player->decreaseLife();
                        bulletIt = bullets.erase(bulletIt);
                        bulletRemoved = true;
                        if (player->getLives() <= 0) {
                            bool flag = gameOverScreen();
                            if (!flag) restFlag = true;
                            window.close();
                            std::cout << "Game Over" << std::endl;
                        }
                    }
                    //If enemy's bullet collide with barrier, it shrinks
                    if (!bulletRemoved) {
                        if (barrier1.bulletCollision(bulletIt->getSprite())) {
                            barrier1.shrink();
                            bulletIt = bullets.erase(bulletIt);
                            bulletRemoved = true;
                            break;
                        }
                        if (barrier2.bulletCollision(bulletIt->getSprite())) {
                            barrier2.shrink();
                            bulletIt = bullets.erase(bulletIt);
                            bulletRemoved = true;
                            break;
                        }
                        if (barrier3.bulletCollision(bulletIt->getSprite())) {
                            barrier3.shrink();
                            bulletIt = bullets.erase(bulletIt);
                            bulletRemoved = true;
                            break;
                        }
                    }
                    if (!bulletRemoved) {
                        ++bulletIt;
                    }
                }
                //Check enemy collides with player
                if (enemy.getIsAlive() && player->isCollidingWithEnemy(enemy.getSprite())) {
                    enemy.kill();
                    player->decreaseLife();
                    metrics.updateHealthbar(player->getLives());
                    //if life is 0, display gameover screen
                    if (player->getLives() <= 0) {
                        bool flag = gameOverScreen();
                        if (!flag) restFlag = true;
                        window.close();
                        std::cout << "Game Over" << std::endl;
                    }
                }
            }
        }


        // display next stage
        time += clock2.restart().asSeconds();
        float alpha = 0;
        if (stage <= metrics.getStage()) {
            alpha = 255 * (time / fadeInDuration);
            if (alpha >= 255) {
                alpha = 255;
                stage++; // Start fading out
                time = 0; // Reset timer for fade out
                stageText.setString("Stage: " + std::to_string(metrics.getStage()));
                if (metrics.getStage() >= 1) {
                    barrier1.reset();
                    barrier2.reset();
                    barrier3.reset();
                }
            }
        } else {
            alpha = 255 - (255 * (time / fadeOutDuration));
            if (alpha <= 0) {
                alpha = 0;
            }
        }
        // Apply the alpha to the fill, outline, and stageText colors
        roundedRect.setFillColor(sf::Color(roundedRect.getFillColor().r, roundedRect.getFillColor().g, roundedRect.getFillColor().b, static_cast<sf::Uint8>(alpha)));
        roundedRect.setOutlineColor(sf::Color(roundedRect.getOutlineColor().r, roundedRect.getOutlineColor().g, roundedRect.getOutlineColor().b, static_cast<sf::Uint8>(alpha)));
        stageText.setFillColor(sf::Color(stageText.getFillColor().r, stageText.getFillColor().g, stageText.getFillColor().b, static_cast<sf::Uint8>(alpha)));


        /** when bullet hits barrier, the barrier shrinks */
        player->updateBarrier(deltaTime, barrier1);
        player->updateBarrier(deltaTime, barrier2);
        player->updateBarrier(deltaTime, barrier3);
        enemyWave->draw(window);
        /** end of enemy stuff */

        window.clear();
        player->draw(window);
        powerup.draw(window,player);
        player->drawBullets(window);
        enemyWave->draw(window);
        barrier1.draw(window);
        barrier2.draw(window);
        barrier3.draw(window);
        metrics.draw(window);
        window.draw(roundedRect);
        window.draw(stageText);
        window.display();
    }
    // check of user wants to replay the game
    if (restFlag) {
        sf::VideoMode fullScreenMode = sf::VideoMode::getDesktopMode();
        window.create((options.isFullScreen()) ? fullScreenMode : sf::VideoMode(options.getResolution()[0],options.getResolution()[1]), "Fire Fighter", (options.isFullScreen() || options.getResolution()[0] >= fullScreenMode.width) ? sf::Style::Fullscreen : sf::Style::Default);
        window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr()); // Set the window icon
        window.setFramerateLimit(60);
        metrics.reset();
        barrier1.reset();
        barrier2.reset();
        barrier3.reset();
        powerup.reset();
        player->reset(window);
        enemyWave->respawnEnemies(1);
        goto spetsnaz;
    }
}


/**
 * character selection window
 * handles character selection
 * */
char* Game::characterSelectScreen() {
    char* str;                                          // String of player texture path to return
    sf::Texture boyTexture;                             // load image of the boy droplet image
    sf::Texture girlTexture;                            // load image of the girl droplet image
    sf::Texture characterBackDropTexture;               // load image of the backdrop of the characters
    if (!boyTexture.loadFromFile("../../resource/img/waterBoy.png")) {
        std::cerr << "Failed to load player!" << std::endl;
    }
    if (!girlTexture.loadFromFile("../../resource/img/waterGirl.png")) {
        std::cerr << "Failed to load player!" << std::endl;
    }
    if (!characterBackDropTexture.loadFromFile("../../resource/img/character_back_drop.png")) {
        std::cerr << "Failed to load backdrop!" << std::endl;
    }
    sf::Sprite boyDroplet(boyTexture);          // sprite of the boy player
    sf::Sprite girlDroplet(girlTexture);        // sprite of the girl player
    sf::Sprite characterBackDrop(characterBackDropTexture); // sprites of the backdrop
    boyDroplet.setScale(options.widthScaling(3), options.heightScaling(3));
    girlDroplet.setScale(options.widthScaling(3), options.heightScaling(3));
    characterBackDrop.setScale(options.widthScaling(3), options.heightScaling(3));

    // Get the screen dimensions
    float screenWidth = static_cast<float>(window.getSize().x);
    float screenHeight = static_cast<float>(window.getSize().y);

    // Create boy select button
    sf::RectangleShape selectBoyButton(sf::Vector2f(options.widthScaling(200.f), options.heightScaling(50.f)));
    selectBoyButton.setFillColor(sf::Color::Blue);
    selectBoyButton.setPosition((screenWidth - selectBoyButton.getSize().x * 2 - 50) / 2, screenHeight * 0.6); // Position first button to the left of center
    selectBoyButton.setOutlineThickness(2);
    selectBoyButton.setOutlineColor(sf::Color::White);
    // Create boy select button text
    sf::Text text1(options.getLanguage()[16], font, options.widthScaling(28));
    text1.setPosition(selectBoyButton.getPosition().x + (selectBoyButton.getSize().x - text1.getLocalBounds().width) / 2, selectBoyButton.getPosition().y + (selectBoyButton.getSize().y - text1.getLocalBounds().height) / 2);
    text1.setFillColor(sf::Color(235, 70, 60));
    // Create girl select button
    sf::RectangleShape selectGirlButton(sf::Vector2f(options.widthScaling(200.f), options.heightScaling(50.f)));
    selectGirlButton.setFillColor(sf::Color::Blue);
    selectGirlButton.setPosition(selectBoyButton.getPosition().x + selectBoyButton.getSize().x + 50, screenHeight * 0.6); // Position second button to the right of first button
    selectGirlButton.setOutlineThickness(2);
    selectGirlButton.setOutlineColor(sf::Color::White);
    // Create girl select button text
    sf::Text text2(options.getLanguage()[15], font, options.widthScaling(28));
    text2.setPosition(selectGirlButton.getPosition().x + (selectGirlButton.getSize().x - text2.getLocalBounds().width) / 2, selectGirlButton.getPosition().y + (selectGirlButton.getSize().y - text2.getLocalBounds().height) / 2);
    text2.setFillColor(sf::Color(235, 70, 60));

    // Calculate position to center character
    boyDroplet.setPosition(selectBoyButton.getPosition().x + ((selectBoyButton.getGlobalBounds().width/2) - (boyDroplet.getGlobalBounds().width/2)), selectBoyButton.getPosition().y - (boyDroplet.getGlobalBounds().height * 1.5));
    girlDroplet.setPosition((selectGirlButton.getPosition().x + (selectGirlButton.getGlobalBounds().width/2) - (girlDroplet.getGlobalBounds().width/2)), selectGirlButton.getPosition().y - (girlDroplet.getGlobalBounds().height * 1.5));

    // create text at top of screen
    sf::Text chooseText(options.getLanguage()[13], font, options.widthScaling(70));
    chooseText.setPosition((screenWidth - chooseText.getLocalBounds().width) / 2, 50); // Position text at the top center
    chooseText.setFillColor(sf::Color(235, 70, 60));
    // Create "Go Back" button
    sf::RectangleShape backButton(sf::Vector2f(options.widthScaling(150.f), options.heightScaling(50.f)));
    backButton.setFillColor(sf::Color(54, 207, 213));
    backButton.setPosition(screenWidth - backButton.getSize().x - 20, 20); // Position button at the top right
    backButton.setOutlineThickness(2);
    backButton.setOutlineColor(sf::Color::White);
    // create go back text on go back button
    sf::Text backText(options.getLanguage()[14], font, options.widthScaling(28));
    backText.setPosition(backButton.getPosition().x + (backButton.getSize().x - backText.getLocalBounds().width) / 2, backButton.getPosition().y + (backButton.getSize().y - backText.getLocalBounds().height) / 2);
    backText.setFillColor(sf::Color(235, 70, 60));

    bool hoverFlagBoy = false;          // flag to know when to display backdrop for boy
    bool hoverFlagGirl = false;         // flag to know when to display backdrop for girl
    for (int flag = true; flag;) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return NULL;
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    if (selectBoyButton.getGlobalBounds().contains(mousePos)) {
                        // boy select Button clicked
                        std::cout << "Player 1 selected\n";
                        str = "../../resource/img/waterBoy.png";
                        flag = false;

                    }
                    if (selectGirlButton.getGlobalBounds().contains(mousePos)) {
                        // girl select Button  clicked
                        std::cout << "Player 2 selected\n";
                        str = "../../resource/img/waterGirl.png";
                        flag = false;
                    }
                    if (backButton.getGlobalBounds().contains(mousePos)) {
                        // Back button clicked
                        std::cout << "Go Back\n";
                        window.close();
                        return NULL;
                    }
                }
            }
            if (event.type == sf::Event::MouseMoved) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                if (selectBoyButton.getGlobalBounds().contains(mousePos)) {
                    // Button 1 hovered
                    selectBoyButton.setFillColor(sf::Color(0, 0, 255, 200));
                    hoverFlagBoy = true;
                } else {
                    selectBoyButton.setFillColor(sf::Color(0, 0, 255, 255));
                    hoverFlagBoy = false;
                }

                if (selectGirlButton.getGlobalBounds().contains(mousePos)) {
                    // Button 2 hovered
                    selectGirlButton.setFillColor(sf::Color(255, 105, 180, 200));
                    hoverFlagGirl = true;
                } else {
                    selectGirlButton.setFillColor(sf::Color(255, 105, 180, 255));
                    hoverFlagGirl = false;
                }

                if (backButton.getGlobalBounds().contains(mousePos)) {
                    // Back button hovered
                    backButton.setFillColor(sf::Color(54, 207, 213, 200));
                } else {
                    backButton.setFillColor(sf::Color(54, 207, 213, 255));
                }
            }
        }
        window.clear(sf::Color(52, 109, 129));

        // Draw elements
        if (hoverFlagBoy) {
            characterBackDrop.setPosition(boyDroplet.getPosition().x - (characterBackDrop.getGlobalBounds().width * 0.35), boyDroplet.getPosition().y - characterBackDrop.getGlobalBounds().height * 0.25);
            window.draw(characterBackDrop);
        } else if (hoverFlagGirl) {
            characterBackDrop.setPosition(girlDroplet.getPosition().x - (characterBackDrop.getGlobalBounds().width * 0.35), girlDroplet.getPosition().y - characterBackDrop.getGlobalBounds().height * 0.25);
            window.draw(characterBackDrop);
        }
        window.draw(boyDroplet);
        window.draw(girlDroplet);
        window.draw(selectBoyButton);
        window.draw(text1);
        window.draw(selectGirlButton);
        window.draw(text2);
        window.draw(chooseText);
        window.draw(backButton);
        window.draw(backText);

        // Display the window
        window.display();
    }
    return str;
}

/** handle window when user presses ESC key */
bool Game::handleExitRequest() {
    // Calculate button sizes and positions dynamically based on window size
    float buttonWidth = options.widthScaling(resolution.x * 0.25f);
    float buttonHeight = options.heightScaling(50.f);
    float buttonX = (resolution.x - buttonWidth) / 2;
    float exitButtonY = resolution.y * 0.3f;
    float resumeButtonY = resolution.y * 0.5f;

    // Setup exit button
    sf::RectangleShape exitButton(sf::Vector2f(buttonWidth,  buttonHeight));
    exitButton.setPosition(buttonX, exitButtonY);
    exitButton.setOutlineThickness(2);
    exitButton.setOutlineColor(sf::Color::White);
    // Setup exit resume button
    sf::RectangleShape resumeButton(sf::Vector2f(buttonWidth, buttonHeight));
    resumeButton.setPosition(buttonX, resumeButtonY);
    resumeButton.setOutlineThickness(2);
    resumeButton.setOutlineColor(sf::Color::White);

    // Setup the text for buttons
    sf::Text exitText;
    exitText.setFont(font);
    exitText.setString(options.getLanguage()[20]);
    exitText.setCharacterSize(options.widthScaling(24));
    exitText.setFillColor(sf::Color::White);
    // Center text on its button
    exitText.setPosition(buttonX + (buttonWidth - exitText.getLocalBounds().width) / 2, exitButtonY + (buttonHeight - exitText.getLocalBounds().height) / 2);

    sf::Text resumeText;
    resumeText.setFont(font);
    resumeText.setString(options.getLanguage()[21]);
    resumeText.setCharacterSize(options.widthScaling(24));
    resumeText.setFillColor(sf::Color::White);
    // Center text on its button
    resumeText.setPosition(buttonX + (buttonWidth - resumeText.getLocalBounds().width) / 2, resumeButtonY + (buttonHeight - resumeText.getLocalBounds().height) / 2);

    // Colors for normal and hover states
    sf::Color normalColor(100, 100, 100); // Normal state color
    sf::Color hoverColor(150, 150, 150);  // Hover state color

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                return false;
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (exitButton.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                        std::cout << "Exit Game button clicked!" << std::endl;
                        return true;
                    }
                    if (resumeButton.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                        std::cout << "Resume Game button clicked!" << std::endl;
                        return false;
                    }
                }
            }
        }
        // Check for hover state for exitButton
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (exitButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
            exitButton.setFillColor(hoverColor);
        else
            exitButton.setFillColor(normalColor);

        // Check for hover state for resumeButton
        if (resumeButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
            resumeButton.setFillColor(hoverColor);
        else
            resumeButton.setFillColor(normalColor);

        window.clear();
        metrics.draw(window);
        player->draw(window);
        powerup.draw(window,player);
        player->drawBullets(window);
        enemyWave->draw(window);
        barrier1.draw(window);
        barrier2.draw(window);
        barrier3.draw(window);
        window.draw(exitButton);
        window.draw(exitButton);
        window.draw(exitText);
        window.draw(resumeButton);
        window.draw(resumeText);
        window.display();
    }
}

/**
 * handle window when game is over
 * creates a message on window upon game over
 * */
bool Game::gameOverScreen() {
    // Get the screen dimensions
    float screenWidth = static_cast<float>(window.getSize().x);
    float screenHeight = static_cast<float>(window.getSize().y);

    // Create exit game button
    sf::RectangleShape exitButton(sf::Vector2f(options.widthScaling(200.f), options.heightScaling(50.f)));
    exitButton.setPosition((screenWidth - exitButton.getSize().x * 2 - 50) / 2, screenHeight * 0.7); // Position first button to the left of center
    exitButton.setOutlineThickness(2);
    exitButton.setOutlineColor(sf::Color::White);

    // Create resume button
    sf::RectangleShape resumeButton(sf::Vector2f(options.widthScaling(200.f), options.heightScaling(50.f)));
    resumeButton.setPosition(exitButton.getPosition().x + exitButton.getSize().x + 50, screenHeight * 0.7); // Position second button to the right of first button
    resumeButton.setOutlineThickness(2);
    resumeButton.setOutlineColor(sf::Color::White);

    // Create exit game button text
    sf::Text exitText(options.getLanguage()[17], font, options.widthScaling(28));
    exitText.setPosition(exitButton.getPosition().x + (exitButton.getSize().x - exitText.getLocalBounds().width) / 2, exitButton.getPosition().y + (exitButton.getSize().y - exitText.getLocalBounds().height) / 2);
    exitText.setFillColor(sf::Color(235, 70, 60));

    // Create resume button text
    sf::Text resumeText(options.getLanguage()[18], font, options.widthScaling(28));
    resumeText.setPosition(resumeButton.getPosition().x + (resumeButton.getSize().x - resumeText.getLocalBounds().width) / 2, resumeButton.getPosition().y + (resumeButton.getSize().y - resumeText.getLocalBounds().height) / 2);
    resumeText.setFillColor(sf::Color(235, 70, 60));

    // Create a Game Over Text
    sf::Text gameOverText;
    gameOverText.setFont(font); // Set the font to our loaded font
    gameOverText.setString(options.getLanguage()[19]); // Set the gameOverText string
    gameOverText.setCharacterSize(options.widthScaling(48)); // Set the gameOverText size
    gameOverText.setFillColor(sf::Color::Red); // Set the gameOverText color
    // Position the gameOverText at the top center of the window
    gameOverText.setOrigin(gameOverText.getLocalBounds().left + gameOverText.getLocalBounds().width / 2.0f, gameOverText.getLocalBounds().top);
    gameOverText.setPosition(sf::Vector2f(window.getSize().x / 2.0f, 20.f));

    // Colors for normal and hover states
    sf::Color normalColor(100, 100, 100); // Normal state color
    sf::Color hoverColor(150, 150, 150);  // Hover state color

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                return false;
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (exitButton.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                        std::cout << "Exit Game button clicked!" << std::endl;
                        return true;
                    }
                    if (resumeButton.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                        std::cout << "Retry Game button clicked!" << std::endl;
                        return false;
                    }
                }
            }
        }
        // Check for hover state for exitButton
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (exitButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
            exitButton.setFillColor(hoverColor);
        else
            exitButton.setFillColor(normalColor);

        // Check for hover state for resumeButton
        if (resumeButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
            resumeButton.setFillColor(hoverColor);
        else
            resumeButton.setFillColor(normalColor);

        window.clear();
        window.draw(exitButton);
        window.draw(exitButton); // Draw the exit button shape
        window.draw(exitText); // Draw the exit button gameOverText
        window.draw(resumeButton); // Draw the resume button shape
        window.draw(resumeText); // Draw the resume button gameOverText
        window.draw(gameOverText);
        metrics.drawFinalScore(window);
        window.display();
    }
}
