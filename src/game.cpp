#include "game.h"

/** constructor */
game::game(settings *opt) {
    options = *opt;             // get settings object that was created in UI class
    font = options.getFont();   // load font from settings
    icon = options.getIcon();   // load icon from settings
    if (options.toggleMusic()) {// check if music is enabled, if so, load it into memory
        if (!music.openFromFile("../../music/rglk2theme2distort.mp3"))
            std::cerr << "Failed to load music" << std::endl;
        music.setLoop(true);
    }
    resolution.x = options.getResolution()[0]; // screen resolution width
    resolution.y = options.getResolution()[1]; // screen resolution height
}

/** run game method */
void game::gameLoop() {
    // setup window, fame rate, and icon
    sf::VideoMode fullScreenMode = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window((options.isFullScreen()) ? fullScreenMode : sf::VideoMode(options.getResolution()[0],options.getResolution()[1]), "Fire Fighter", (options.isFullScreen() || options.getResolution()[0] >= fullScreenMode.width) ? sf::Style::Fullscreen : sf::Style::Default);
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr()); // Set the window icon
    window.setFramerateLimit(60);

    // set up player and scale
    Player player(window.getSize().x-100.f, window.getSize().y -100.0f,resolution);
    EnemyWave enemyWave(window, resolution);

    // barrier setup
    float barrierX = (window.getSize().x -100) / 2.f;   // Center the barrier horizontally
    float barrierY = (window.getSize().y - 100) / 2.f;  // Center the barrier vertically
    Barrier barrier(barrierX, barrierY, resolution);   // Create the barrier object

    // character selection screen method call
    char* str = characterSelectScreen(window, player);
    if (str == NULL) return;                            // an error has occurred or user exited back to UI
    else player.setPlayerTexture(str);               // test player texture to selected file path of str

    sf::Clock shootCooldown; // for shooting cool down
    bool canShoot = true;
    float movementSpeed = 0.5f;

    // setup metrics bar on top of the window
    Metrics metrics(resolution, options.getFont());
    metrics.setScore();
    metrics.setEnemyCount(enemyWave.getTotalSpawned());
    metrics.setEnemyKilled(Enemy::getTotalDead());


    // The message to display on window bar
    std::string message = "                      Place your AD here                      ";
    int messageLength = message.length(); int words = 0; int startPos = 0;

    // start the music if it is enabled
    if (options.toggleMusic()) music.play();

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
            if (player.getPosition().y - movementSpeed >= 0) {
                player.move(sf::Vector2f(0.f, -movementSpeed));
            }
        }
        // Move character South
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            if (player.getPosition().y + player.getSize().y + movementSpeed <= window.getSize().y) { // 아래로 이동 가능한 경우에만 이동
                player.move(sf::Vector2f(0.f, movementSpeed));
            }
        }
        // when user presses exit, pop up window
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            if (options.toggleMusic()) music.stop();
            bool flag = handleExitRequest(window);
            if (flag) window.close();
        }
        // when the game has ended
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
            if (options.toggleMusic()) music.stop();
            bool flag = gameOverScreen(window);
            if (flag) window.close();
        }
        // have player shoot when space bar is pressed
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && canShoot) {
            player.shoot();
            shootCooldown.restart();
            canShoot = false;
        }
        if (shootCooldown.getElapsedTime().asSeconds() > 0.5f) {
            canShoot = true;
        }

        int lives = player.getLives();
        metrics.updateHealthbar(lives);
        Powerup.update(deltaTime, player, window);
        player.updateBullets(deltaTime, enemyWave);
        /** end of enemy stuff */
        // Update and draw enemies using EnemyWave
        enemyWave.update(deltaTime);

        /** when enemy collides barrier, the barrier shrinks */
        for (int i = 0; i < enemyWave.getRows(); ++i) {
            for (int j = 0; j < enemyWave.getColumns(); ++j) {
                Enemy &enemy = enemyWave.getEnemy(i, j);
                if (enemy.getIsAlive() && barrier.enemyCollision(enemy)) {
                    barrier.shrink();
                    // also kill the enemy
                    enemy.kill();
                }
            }
        }

        /** when bullet hits barrier, the barrier shrinks */
        player.updateBarrier(deltaTime,barrier);

        enemyWave.draw(window);
        /** end of enemy stuff */

        // Update the window title message
        if (words == 25) {
            std::string title = message.substr(startPos, 100); // Adjust the length based on your needs
            window.setTitle(title);
            if (++startPos + 20 > messageLength) startPos = 0; // Increment the start position to move the text, wrapping around if necessary
            words = 0;
        } else words++;

        window.clear();
        player.draw(window);
        Powerup.draw(window,player);
        player.drawBullets(window);
        enemyWave.draw(window);
        barrier.draw(window);
        metrics.draw(window);
        window.display();
    }
}


/**
 * character selection window
 * handles character selection
 * */
char* game::characterSelectScreen(sf::RenderWindow &window, const Player& player) {
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

    // Get the screen dimensions
    float screenWidth = resolution.x;
    float screenHeight = resolution.y;
    // Calculate position to center character
    boyDroplet.setPosition((screenWidth - boyDroplet.getGlobalBounds().width - 250) / 2, (screenHeight - boyDroplet.getGlobalBounds().height - 70) / 2);
    girlDroplet.setPosition((screenWidth - girlDroplet.getGlobalBounds().width + 250) / 2, (screenHeight - girlDroplet.getGlobalBounds().height - 70) / 2);

    // Create boy select button
    sf::RectangleShape selectBoyButton(sf::Vector2f(200.f, 50.f));
    selectBoyButton.setFillColor(sf::Color::Blue);
    selectBoyButton.setPosition((screenWidth - selectBoyButton.getSize().x * 2 - 50) / 2, screenHeight / 2); // Position first button to the left of center
    selectBoyButton.setOutlineThickness(2);
    selectBoyButton.setOutlineColor(sf::Color::White);
    // Create boy select button text
    sf::String s1 = options.getLanguage()[16];
    sf::Text text1(s1, font, 20);
    text1.setPosition(selectBoyButton.getPosition().x + (selectBoyButton.getSize().x - text1.getLocalBounds().width) / 2, selectBoyButton.getPosition().y + (selectBoyButton.getSize().y - text1.getLocalBounds().height) / 2);
    text1.setFillColor(sf::Color(235, 70, 60));
    // Create girl select button
    sf::RectangleShape selectGirlButton(sf::Vector2f(200.f, 50.f));
    selectGirlButton.setFillColor(sf::Color::Blue);
    selectGirlButton.setPosition(selectBoyButton.getPosition().x + selectBoyButton.getSize().x + 50, screenHeight / 2); // Position second button to the right of first button
    selectGirlButton.setOutlineThickness(2);
    selectGirlButton.setOutlineColor(sf::Color::White);
    // Create girl select button text
    sf::String s2 = options.getLanguage()[15];
    sf::Text text2(s2, font, 20);
    text2.setPosition(selectGirlButton.getPosition().x + (selectGirlButton.getSize().x - text2.getLocalBounds().width) / 2, selectGirlButton.getPosition().y + (selectGirlButton.getSize().y - text2.getLocalBounds().height) / 2);
    text2.setFillColor(sf::Color(235, 70, 60));
    // create text at top of screen
    sf::String s3 = options.getLanguage()[13];
    sf::Text chooseText(s3, font, 50);
    chooseText.setPosition((screenWidth - chooseText.getLocalBounds().width) / 2, 50); // Position text at the top center
    chooseText.setFillColor(sf::Color(235, 70, 60));
    // Create "Go Back" button
    sf::RectangleShape backButton(sf::Vector2f(150.f, 50.f));
    backButton.setFillColor(sf::Color(54, 207, 213));
    backButton.setPosition(screenWidth - backButton.getSize().x - 20, 20); // Position button at the top right
    backButton.setOutlineThickness(2);
    backButton.setOutlineColor(sf::Color::White);
    // create go back text on go back button
    sf::String s4 = options.getLanguage()[14];
    sf::Text backText(s4, font, 20);
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
            characterBackDrop.setPosition((screenWidth - characterBackDrop.getGlobalBounds().width - 250) / 2, (screenHeight - characterBackDrop.getGlobalBounds().height - 70) / 2);
            window.draw(characterBackDrop);
        } else if (hoverFlagGirl) {
            characterBackDrop.setPosition((screenWidth - characterBackDrop.getGlobalBounds().width + 250) / 2, (screenHeight - characterBackDrop.getGlobalBounds().height - 70) / 2);
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
bool game::handleExitRequest(sf::RenderWindow& win) {
    // Calculate button sizes and positions dynamically based on window size
    sf::Vector2u windowSize = win.getSize();
    float buttonWidth = windowSize.x * 0.5f; // Buttons are 50% of window width
    float buttonHeight = 50.f; // Fixed height for buttons
    float buttonX = (windowSize.x - buttonWidth) / 2; // Center the button on the x-axis
    float exitButtonY = windowSize.y * 0.3f; // Exit button at 30% of window height
    float resumeButtonY = windowSize.y * 0.5f; // Resume button at 50% of window height

    // Setup the rectangle shape for buttons
    sf::RectangleShape exitButton(sf::Vector2f(buttonWidth, buttonHeight));
    exitButton.setFillColor(sf::Color(100, 100, 100));
    exitButton.setPosition(buttonX, exitButtonY);
    exitButton.setOutlineThickness(2);
    exitButton.setOutlineColor(sf::Color::White);

    sf::RectangleShape resumeButton(sf::Vector2f(buttonWidth, buttonHeight));
    resumeButton.setFillColor(sf::Color(100, 100, 100));
    resumeButton.setPosition(buttonX, resumeButtonY);
    resumeButton.setOutlineThickness(2);
    resumeButton.setOutlineColor(sf::Color::White);

    // Setup the text for buttons
    sf::Text exitText;
    exitText.setFont(font);
    exitText.setString("Exit Game");
    exitText.setCharacterSize(24);
    exitText.setFillColor(sf::Color::White);
    // Center text on its button
    exitText.setPosition(buttonX + (buttonWidth - exitText.getLocalBounds().width) / 2, exitButtonY + (buttonHeight - exitText.getLocalBounds().height) / 2);

    sf::Text resumeText;
    resumeText.setFont(font);
    resumeText.setString("Resume Game");
    resumeText.setCharacterSize(24);
    resumeText.setFillColor(sf::Color::White);
    // Center text on its button
    resumeText.setPosition(buttonX + (buttonWidth - resumeText.getLocalBounds().width) / 2, resumeButtonY + (buttonHeight - resumeText.getLocalBounds().height) / 2);

    // Colors for normal and hover states
    sf::Color normalColor(100, 100, 100); // Normal state color
    sf::Color hoverColor(150, 150, 150);  // Hover state color

    while (win.isOpen()) {
        sf::Event event;
        while (win.pollEvent(event)) {
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
        sf::Vector2i mousePos = sf::Mouse::getPosition(win);
        if (exitButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            exitButton.setFillColor(hoverColor);
        } else {
            exitButton.setFillColor(normalColor);
        }

        // Check for hover state for resumeButton
        if (resumeButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            resumeButton.setFillColor(hoverColor);
        } else {
            resumeButton.setFillColor(normalColor);
        }

        win.clear();
        win.draw(exitButton);
        win.draw(exitButton); // Draw the exit button shape
        win.draw(exitText); // Draw the exit button text
        win.draw(resumeButton); // Draw the resume button shape
        win.draw(resumeText); // Draw the resume button text
        win.display();
    }
}

/**
 * handle window when game is over
 * creates a message on window upon game over
 * */
bool game::gameOverScreen(sf::RenderWindow &win) {
// Load a texture from a file
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("../../resource/img/set-on-fire_1920.jpg")) {
        return EXIT_FAILURE; // Error handling
    }

    // Create a sprite that will have the texture of the background
    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTexture);
    // Optionally, scale the sprite to fit the window size
    backgroundSprite.setScale(
            float(win.getSize().x) / backgroundTexture.getSize().x,
            float(win.getSize().y) / backgroundTexture.getSize().y);

    // Calculate button sizes and positions dynamically based on window size
    sf::Vector2u windowSize = win.getSize();
    float buttonWidth = windowSize.x * 0.5f; // Buttons are 50% of window width
    float buttonHeight = 50.f; // Fixed height for buttons
    float buttonX = (windowSize.x - buttonWidth) / 2; // Center the button on the x-axis
    float exitButtonY = windowSize.y * 0.3f; // Exit button at 30% of window height
    float resumeButtonY = windowSize.y * 0.5f; // Resume button at 50% of window height

    // Setup the rectangle shape for buttons
    sf::RectangleShape exitButton(sf::Vector2f(buttonWidth, buttonHeight));
    exitButton.setFillColor(sf::Color(100, 100, 100));
    exitButton.setPosition(buttonX, exitButtonY);
    exitButton.setOutlineThickness(2);
    exitButton.setOutlineColor(sf::Color::White);

    sf::RectangleShape resumeButton(sf::Vector2f(buttonWidth, buttonHeight));
    resumeButton.setFillColor(sf::Color(100, 100, 100));
    resumeButton.setPosition(buttonX, resumeButtonY);
    resumeButton.setOutlineThickness(2);
    resumeButton.setOutlineColor(sf::Color::White);

    // Setup the text for buttons
    sf::Text exitText;
    exitText.setFont(font);
    exitText.setString("Exit");
    exitText.setCharacterSize(24);
    exitText.setFillColor(sf::Color::White);
    // Center text on its button
    exitText.setPosition(buttonX + (buttonWidth - exitText.getLocalBounds().width) / 2, exitButtonY + (buttonHeight - exitText.getLocalBounds().height) / 2);

    sf::Text resumeText;
    resumeText.setFont(font);
    resumeText.setString("Retry");
    resumeText.setCharacterSize(24);
    resumeText.setFillColor(sf::Color::White);
    // Center text on its button
    resumeText.setPosition(buttonX + (buttonWidth - resumeText.getLocalBounds().width) / 2, resumeButtonY + (buttonHeight - resumeText.getLocalBounds().height) / 2);

    // Colors for normal and hover states
    sf::Color normalColor(100, 100, 100); // Normal state color
    sf::Color hoverColor(150, 150, 150);  // Hover state color

    // Create a text object
    sf::Text text;
    text.setFont(font); // Set the font to our loaded font
    text.setString("You Lost"); // Set the text string
    text.setCharacterSize(48); // Set the text size
    text.setFillColor(sf::Color::Red); // Set the text color

    // Position the text at the top center of the window
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top);
    text.setPosition(sf::Vector2f(win.getSize().x/2.0f, 20.f));

    while (win.isOpen()) {
        sf::Event event;
        while (win.pollEvent(event)) {
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
        sf::Vector2i mousePos = sf::Mouse::getPosition(win);
        if (exitButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            exitButton.setFillColor(hoverColor);
        } else {
            exitButton.setFillColor(normalColor);
        }

        // Check for hover state for resumeButton
        if (resumeButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            resumeButton.setFillColor(hoverColor);
        } else {
            resumeButton.setFillColor(normalColor);
        }

        win.clear();
        win.draw(backgroundSprite);
        win.draw(exitButton);
        win.draw(exitButton); // Draw the exit button shape
        win.draw(exitText); // Draw the exit button text
        win.draw(resumeButton); // Draw the resume button shape
        win.draw(resumeText); // Draw the resume button text
        win.draw(text);
        win.display();
    }
}
