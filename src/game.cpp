#include "game.h"
game::game() {
    options = new settings();
}

void game::gameLoop() {
    sf::VideoMode fullScreenMode = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window((options->isFullScreen()) ? fullScreenMode : sf::VideoMode(options->getResolution()[0],options->getResolution()[1]), "Fire Fighter", (options->isFullScreen() || options->getResolution()[0] >= fullScreenMode.width) ? sf::Style::Fullscreen : sf::Style::Default);
    sf::Image icon = options->getIcon();
    sf::Clock clock;
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr()); // Set the window icon
    window.setFramerateLimit(60);
    sf::Font font = options->getFont();
    int* res = options->getResolution(); 
    sf::Vector2u resolution(res[0], res[1]);
    Player player(window.getSize().x-100.f, window.getSize().y -100.0f,resolution);
    EnemyWave enemyWave(window);


    //*****************************************************************************************
    // barrier setup
    float barrierX = (window.getSize().x -100) / 2.f; // Center the barrier horizontally
    float barrierY = (window.getSize().y - 100) / 2.f; // Center the barrier vertically
    Barrier barrier(barrierX, barrierY); // Create the barrier object
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
    sf::String s1 = options->getLanguage()[16];
    sf::Text text1(s1, font, 20);
    text1.setPosition(button1.getPosition().x + (button1.getSize().x - text1.getLocalBounds().width) / 2, button1.getPosition().y + (button1.getSize().y - text1.getLocalBounds().height) / 2);
    text1.setFillColor(sf::Color::White);
    // Create button 2
    sf::RectangleShape button2(sf::Vector2f(200.f, 50.f));
    button2.setFillColor(sf::Color::Red);
    button2.setPosition(button1.getPosition().x + button1.getSize().x + 50, screenHeight / 2); // Position second button to the right of first button
    // Create button 2 text
    sf::String s2 = options->getLanguage()[15];
    sf::Text text2(s2, font, 20);
    text2.setPosition(button2.getPosition().x + (button2.getSize().x - text2.getLocalBounds().width) / 2, button2.getPosition().y + (button2.getSize().y - text2.getLocalBounds().height) / 2);
    text2.setFillColor(sf::Color::White);
    // create text at top of screen
    sf::String s3 = options->getLanguage()[13];
    sf::Text chooseText(s3, font, 30);
    chooseText.setPosition((screenWidth - chooseText.getLocalBounds().width) / 2, 20); // Position text at the top center
    chooseText.setFillColor(sf::Color::White);
    // Create "Go Back" button
    sf::RectangleShape backButton(sf::Vector2f(150.f, 50.f));
    backButton.setFillColor(sf::Color(54, 207, 213));
    backButton.setPosition(screenWidth - backButton.getSize().x - 20, 20); // Position button at the top right
    // create go back text
    sf::String s4 = options->getLanguage()[14];
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
    // end of choose player window
    //*************************************************************************************************

    sf::Clock shootCooldown;
    bool canShoot = true;
    float movementSpeed = 0.5f;

    // Create an exit button
    sf::RectangleShape exitButton(sf::Vector2f(100.f, 30.f)); // Smaller size
    exitButton.setFillColor(sf::Color::Red);
    exitButton.setPosition(window.getSize().x - 130.f, 20.f); // Position in the top right corner

    // Create text for the exit button
    sf::Text exitButtonText(options->getLanguage()[17], font, 16); // Smaller text size
    exitButtonText.setFillColor(sf::Color::White);
    // Center the text within the exit button
    exitButtonText.setPosition(exitButton.getPosition().x + (exitButton.getSize().x - exitButtonText.getLocalBounds().width) / 2,
                               exitButton.getPosition().y + (exitButton.getSize().y - exitButtonText.getLocalBounds().height) / 2);


    powerup Powerup;
    // Load life counter textures
    sf::Texture life3Texture;
    sf::Texture life2Texture;
    sf::Texture life1Texture;
    sf::Texture life0Texture;

    if (!life3Texture.loadFromFile("../../resource/img/3.png") ||
        !life2Texture.loadFromFile("../../resource/img/2.png") ||
        !life1Texture.loadFromFile("../../resource/img/1.png") ||
        !life0Texture.loadFromFile("../../resource/img/0.png")) {
        std::cerr << "Failed to load life counter textures!" << std::endl;
        return;
    }

    // Create life counter sprites
    sf::Sprite lifeCounterSprite;
    lifeCounterSprite.setTexture(life3Texture);
    lifeCounterSprite.setScale(1.5f, 1.5f); // Adjust scale as needed
    lifeCounterSprite.setPosition(15.f, 15.f); // Top left corner of the window

    // The message to display
    std::string message = "                      Place your AD here                      ";
    int messageLength = message.length(); int words = 0;
    // The position at which to start cutting the message
    int startPos = 0;

    sf::Music music;
    if (options->toggleMusic()) {
        // set music for the main menu
        if (!music.openFromFile("../../music/rglk2theme2distort.mp3")) {
            std::cerr << "Failed to load music" << std::endl;
        }
        music.setLoop(true); // Loop the music
        music.play();
    }

/** main game window */
    while (window.isOpen()) {
        sf::Event event;
        sf::Time deltaTime = clock.restart();
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }


        // Update and draw enemies using EnemyWave
        enemyWave.update(deltaTime);
        enemyWave.draw(window);

        /** end of enemy stuff */

        /** barrier stuff */
        barrier.draw(window);
        /** end of barrier stuff */

        // Move character
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            if (player.getPosition().y - movementSpeed >= 0) {
                player.move(sf::Vector2f(0.f, -movementSpeed));
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            if (player.getPosition().y + player.getSize().y + movementSpeed <= window.getSize().y) { // 아래로 이동 가능한 경우에만 이동
                player.move(sf::Vector2f(0.f, movementSpeed));
            }
        }

        // Check if the exit button is clicked
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (exitButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                if (options->toggleMusic()) {
                    music.stop();
                }
                window.close();
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && canShoot) {
            player.shoot();
            shootCooldown.restart();
            canShoot = false;
        }

        if (shootCooldown.getElapsedTime().asSeconds() > 0.5f) {
            canShoot = true;
        }
        int lives = player.getLives();
        switch (lives) {
            case 3:
                lifeCounterSprite.setTexture(life3Texture);
                break;
            case 2:
                lifeCounterSprite.setTexture(life2Texture);
                break;
            case 1:
                lifeCounterSprite.setTexture(life1Texture);
                break;
            case 0:
                lifeCounterSprite.setTexture(life0Texture);
                break;
            default:
                break;
        }

        player.updateBullets(deltaTime);

        window.clear();
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


        window.draw(lifeCounterSprite);
        Powerup.update(deltaTime, player,window);

        player.updateBullets(deltaTime);
        window.clear();
        player.draw(window);
        window.draw(lifeCounterSprite);
        Powerup.draw(window,player);
        player.drawBullets(window);
        enemyWave.draw(window);
        window.draw(exitButton);
        window.draw(exitButtonText);
        window.display();
    }
    return;
}
