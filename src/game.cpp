#include "game.h"

/** constructor */
game::game(settings *opt) {
    options = *opt;             // get settings object that was created in UI class
    font = options.getFont();   // load font from settings
    icon = options.getIcon();   // load icon from settings
    if (options.toggleMusic()) {// check if music is enabled
        // setup music for the main menu
        if (!music.openFromFile("../../music/rglk2theme2distort.mp3"))
            std::cerr << "Failed to load music" << std::endl;
        music.setLoop(true);
    }
}

/** run game method */
void game::gameLoop() {
    sf::VideoMode fullScreenMode = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window((options.isFullScreen()) ? fullScreenMode : sf::VideoMode(options.getResolution()[0],options.getResolution()[1]), "Fire Fighter", (options.isFullScreen() || options.getResolution()[0] >= fullScreenMode.width) ? sf::Style::Fullscreen : sf::Style::Default);
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr()); // Set the window icon
    window.setFramerateLimit(60);
    // set up player and scale
    sf::Vector2u resolution(options.getResolution()[0], options.getResolution()[1]);
    Player player(window.getSize().x-100.f, window.getSize().y -100.0f,resolution);
    EnemyWave enemyWave(window);

    //*****************************************************************************************
    // barrier setup
    float barrierX = (window.getSize().x -100) / 2.f; // Center the barrier horizontally
    float barrierY = (window.getSize().y - 100) / 2.f; // Center the barrier vertically
    auto *testMe = new Barrier(barrierX, barrierY); // Create the barrier object
    // end of barrier setup
    //*****************************************************************************************

//*****************************************************************************************
    // pick character window code start
    // character textures
    sf::Texture characterTexture1;
    sf::Texture characterTexture2;
    if (!characterTexture1.loadFromFile("../../resource/img/waterBoy.png")) {
        std::cerr << "Failed to load player!" << std::endl;
        return;
    }
    if (!characterTexture2.loadFromFile("../../resource/img/waterGirl.png")) {
        std::cerr << "Failed to load player!" << std::endl;
        return;
    }
    sf::Sprite character1(characterTexture1);
    sf::Sprite character2(characterTexture2);
    // Get the screen dimensions
    sf::Vector2u screenSize = window.getSize();
    float screenWidth = screenSize.x;
    float screenHeight = screenSize.y;
    // Calculate position to center character
    character1.setPosition((screenWidth - character1.getGlobalBounds().width - 230)/ 2, (screenHeight - character1.getGlobalBounds().height) / 2);
    character2.setPosition((screenWidth - character2.getGlobalBounds().width + 250) / 2, (screenHeight - character2.getGlobalBounds().height) / 2);
    // Create button 1
    sf::RectangleShape button1(sf::Vector2f(200.f, 50.f));
    button1.setFillColor(sf::Color::Blue);
    button1.setPosition((screenWidth - button1.getSize().x * 2 - 50) / 2, screenHeight / 2); // Position first button to the left of center
    // Create button 1 text
    sf::String s1 = options.getLanguage()[16];
    sf::Text text1(s1, font, 20);
    text1.setPosition(button1.getPosition().x + (button1.getSize().x - text1.getLocalBounds().width) / 2, button1.getPosition().y + (button1.getSize().y - text1.getLocalBounds().height) / 2);
    text1.setFillColor(sf::Color::White);
    // Create button 2
    sf::RectangleShape button2(sf::Vector2f(200.f, 50.f));
    button2.setFillColor(sf::Color::Red);
    button2.setPosition(button1.getPosition().x + button1.getSize().x + 50, screenHeight / 2); // Position second button to the right of first button
    // Create button 2 text
    sf::String s2 = options.getLanguage()[15];
    sf::Text text2(s2, font, 20);
    text2.setPosition(button2.getPosition().x + (button2.getSize().x - text2.getLocalBounds().width) / 2, button2.getPosition().y + (button2.getSize().y - text2.getLocalBounds().height) / 2);
    text2.setFillColor(sf::Color::White);
    // create text at top of screen
    sf::String s3 = options.getLanguage()[13];
    sf::Text chooseText(s3, font, 30);
    chooseText.setPosition((screenWidth - chooseText.getLocalBounds().width) / 2, 20); // Position text at the top center
    chooseText.setFillColor(sf::Color::White);
    // Create "Go Back" button
    sf::RectangleShape backButton(sf::Vector2f(150.f, 50.f));
    backButton.setFillColor(sf::Color(54, 207, 213));
    backButton.setPosition(screenWidth - backButton.getSize().x - 20, 20); // Position button at the top right
    // create go back text
    sf::String s4 = options.getLanguage()[14];
    sf::Text backText(s4, font, 20);
    backText.setPosition(backButton.getPosition().x + (backButton.getSize().x - backText.getLocalBounds().width) / 2, backButton.getPosition().y + (backButton.getSize().y - backText.getLocalBounds().height) / 2);
    backText.setFillColor(sf::Color::White);

    for (int flag = true; flag;) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    if (button1.getGlobalBounds().contains(mousePos)) {
                        // Button 1 clicked
                        std::cout << "Player 1 selected\n";
                        player.setPlayerTexture("../../resource/img/waterBoy.png");
                        flag = false;
                    }
                    if (button2.getGlobalBounds().contains(mousePos)) {
                        // Button 2 clicked
                        std::cout << "Player 2 selected\n";
                        player.setPlayerTexture("../../resource/img/waterGirl.png");
                        flag = false;
                    }
                    if (backButton.getGlobalBounds().contains(mousePos)) {
                        // Back button clicked
                        std::cout << "Go Back\n";
                        window.close();
                        return;
                    }
                }
            }
            if (event.type == sf::Event::MouseMoved) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                if (button1.getGlobalBounds().contains(mousePos)) {
                    // Button 1 hovered
                    button1.setFillColor(sf::Color(0, 0, 255, 200));
                } else {
                    button1.setFillColor(sf::Color(0, 0, 255, 255));
                }

                if (button2.getGlobalBounds().contains(mousePos)) {
                    // Button 2 hovered
                    button2.setFillColor(sf::Color(255, 0, 0, 200));
                } else {
                    button2.setFillColor(sf::Color(255, 0, 0, 255));
                }

                if (backButton.getGlobalBounds().contains(mousePos)) {
                    // Back button hovered
                    backButton.setFillColor(sf::Color(54, 207, 213, 200));
                } else {
                    backButton.setFillColor(sf::Color(54, 207, 213, 255));
                }
            }
        }
        // Clear the window
        window.clear(sf::Color(52, 109, 129));

        // Draw elements
        window.draw(character1);
        window.draw(character2);
        window.draw(button1);
        window.draw(text1);
        window.draw(button2);
        window.draw(text2);
        window.draw(chooseText);
        window.draw(backButton);
        window.draw(backText);

        // Display the window
        window.display();
    }
    // end of chose player window
    //*************************************************************************************************

    sf::Clock shootCooldown; // for shooting cool down
    bool canShoot = true;
    float movementSpeed = 0.5f;

    Metrics metrics(resolution);
    metrics.setScore();

    // The message to display
    std::string message = "                      Place your AD here                      ";
    int messageLength = message.length(); int words = 0; int startPos = 0;

    // play music if it is enabled
    if (options.toggleMusic()) music.play();

/** main game window */
    while (window.isOpen()) {
        sf::Event event;
        sf::Time deltaTime = clock.restart();
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
            bool flag = handleRequest(window);
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
        player.updateBullets(deltaTime);
        Powerup.update(deltaTime, player, window);
        player.updateBullets(deltaTime);
        /** end of enemy stuff */
        // Update and draw enemies using EnemyWave
        enemyWave.update(deltaTime);
        enemyWave.draw(window);
        /** end of enemy stuff */

        if (words == 25) {
            // Update the window title with a substring of the message
            std::string title = message.substr(startPos, 100); // Adjust the length based on your needs
            window.setTitle(title);
            // Increment the start position to move the text, wrapping around if necessary
            if (++startPos + 20 > messageLength) startPos = 0;
            words = 0;
        } else {
            words++;
        }

        window.clear();
        player.draw(window);
        Powerup.draw(window,player);
        player.drawBullets(window);
        enemyWave.draw(window);
        metrics.draw(window);
        window.display();
    }
}

/** for pop up exit button */
bool game::handleRequest(sf::RenderWindow& win) {
    // Setup the window
//    sf::RenderWindow win(sf::VideoMode(400, 300), "Popup Window", sf::Style::Close);

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

    sf::RectangleShape resumeButton(sf::Vector2f(buttonWidth, buttonHeight));
    resumeButton.setFillColor(sf::Color(100, 100, 100));
    resumeButton.setPosition(buttonX, resumeButtonY);

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
//                win.close();
                return false;
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (exitButton.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                        std::cout << "Exit Game button clicked!" << std::endl;
//                        win.close(); // Close window on Exit Game button click
                        return true;
                    }

                    if (resumeButton.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                        std::cout << "Resume Game button clicked!" << std::endl;
//                        win.close(); // Close window on Exit Game button click
                        return false;
                        // Add logic for resuming the game
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

