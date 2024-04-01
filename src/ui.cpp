#include "ui.h"

/** constructor */
ui::ui() {
    sf::VideoMode fullScreenMode = sf::VideoMode::getDesktopMode();
    window.create((options.isFullScreen()) ? fullScreenMode : sf::VideoMode(options.getResolution()[0], options.getResolution()[1]), "Fire Fighter", (options.isFullScreen() || options.getResolution()[0] >= fullScreenMode.width) ? sf::Style::Fullscreen : sf::Style::Default);
    _init();
}

/** destructor */
ui::~ui() {
    if (window.isOpen()) {      // Close the SFML window if it's open
        window.close();
    }
    if (startGame != nullptr) {   // delete it if it's not nullptr
        delete startGame;
        startGame = nullptr;      // Set to nullptr after deletion
    }
}

/** main UI menu loop */
void ui::displayMenu() {
    // Calculate button dimensions based on window size
    float windowWidth = (window.getSize().x / 3) * 0.6f;
    float windowHeight = (window.getSize().y / 4) * 0.4f;
    float totalButtonWidth = windowWidth * 3;

    // Create new game button
    sf::ConvexShape newGameButton = createButtonShape(windowWidth, windowHeight);
    newGameButton.setPosition((window.getSize().x - totalButtonWidth) / 2, window.getSize().y * 0.9 - windowHeight / 2);
    //Create settings button
    sf::ConvexShape settingsbutton = createButtonShape(windowWidth, windowHeight);
    settingsbutton.setPosition(newGameButton.getPosition().x + windowWidth, window.getSize().y * 0.9 - windowHeight / 2);
    // Create quit button
    sf::ConvexShape quitButton = createButtonShape(windowWidth, windowHeight);
    quitButton.setPosition(settingsbutton.getPosition().x + windowWidth, window.getSize().y * 0.9 - windowHeight / 2);

    // Create the separationLine2 from the bottom-right of the New Game button to the top-right of the New Game button
    sf::VertexArray separationLine1(sf::Lines, 2);
    separationLine1[0].position = sf::Vector2f(newGameButton.getPosition().x + newGameButton.getPoint(2).x, newGameButton.getPosition().y + newGameButton.getPoint(2).y);
    separationLine1[1].position = sf::Vector2f(newGameButton.getPosition().x + newGameButton.getPoint(1).x, newGameButton.getPosition().y + newGameButton.getPoint(1).y);
    separationLine1[0].color = sf::Color::Red;
    separationLine1[1].color = sf::Color::Red;

    // Create the separationLine2 from the bottom-right of the settings button to the top-right of the settings button
    sf::VertexArray separationLine2(sf::Lines, 2);
    separationLine2[0].position = sf::Vector2f(settingsbutton.getPosition().x + settingsbutton.getPoint(2).x, settingsbutton.getPosition().y + settingsbutton.getPoint(2).y);
    separationLine2[1].position = sf::Vector2f(settingsbutton.getPosition().x + settingsbutton.getPoint(1).x, settingsbutton.getPosition().y + settingsbutton.getPoint(1).y);
    separationLine2[0].color = sf::Color::Red;
    separationLine2[1].color = sf::Color::Red;

    // Create new game button text
    sf::String newGameString = options.getLanguage()[0];
    sf::Text newGameText(newGameString, font, options.widthScaling(26));
    newGameText.setFillColor(sf::Color(235, 70, 60));
    newGameText.setPosition(newGameButton.getPosition().x + (newGameText.getLocalBounds().width / 4), newGameButton.getPosition().y + newGameText.getLocalBounds().height * 1.5);
    // Create settings button text
    sf::String settingsString = options.getLanguage()[1];
    sf::Text settingsText(settingsString, font, options.widthScaling(26));
    settingsText.setFillColor(sf::Color(235, 70, 60));
    settingsText.setPosition(settingsbutton.getPosition().x + (settingsText.getLocalBounds().width / 4), settingsbutton.getPosition().y + settingsText.getLocalBounds().height * 1.5);
    // Create quit button text
    sf::String quitString = options.getLanguage()[2];
    sf::Text quitText(quitString, font, options.widthScaling(26));
    quitText.setFillColor(sf::Color(235, 70, 60));
    quitText.setPosition(quitButton.getPosition().x + (quitText.getLocalBounds().width), settingsbutton.getPosition().y + settingsText.getLocalBounds().height * 1.5);

    // set up background image
    sf::Sprite background(backgroundImage);
    background.setTexture(backgroundImage);
    background.setScale(window.getSize().x / background.getLocalBounds().width, window.getSize().y / background.getLocalBounds().height);

    if (options.toggleMusic()) music.play();

    bool startGameFlag = false;
    bool openSettings = false;
    bool exitFlag = false;

    // The UI window loop starts here
    while (1) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // check if user has closed the window
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                //game window
                if (newGameButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    std::cout << "New Game" << std::endl;
                    startGameFlag = true;
                }
                // settings
                if (settingsbutton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    std::cout << "Settings" << std::endl;
                    openSettings = true;
                }
                //quit button
                if (quitButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    std::cout << "Quit" << std::endl;
                    window.close();
                    return;
                }
            }
        }
        // checks if new game button was pressed or not
        if (startGameFlag) {
            if (options.toggleMusic()) music.pause();
            window.close();

            startGame = new game(&options);
            startGame->gameLoop();
            delete(startGame);
            startGame = nullptr;

            startGameFlag = false;
            if (options.toggleMusic()) music.play();
            exitFlag = true;    // set to true we can exit the loop and create a new window for UI
            break;
        }
        if (openSettings) {
            window.close();
            options.openSettings();
            // when exited settings
            exitFlag = true;    // set to true to exit loop and create a new UI window reloaded with new settings applied weather or not any changes were applied in settings
            break;
        }
        // for button mouse hover effect
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (settingsbutton.getGlobalBounds().contains(mousePos.x, mousePos.y))
            settingsbutton.setFillColor(sf::Color(0, 255, 0, 200)); // Green with transparency
        else
            settingsbutton.setFillColor(sf::Color(54, 207, 213));
        if (quitButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
            quitButton.setFillColor(sf::Color(0, 0, 255, 200));     // Blue with transparency
        else
            quitButton.setFillColor(sf::Color(54, 207, 213));
        if (newGameButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
            newGameButton.setFillColor(sf::Color(255, 0, 255, 200));// Red with transparency
        else
            newGameButton.setFillColor(sf::Color(54, 207, 213));

        window.clear();
        window.draw(background);
        window.draw(settingsbutton);
        window.draw(quitButton);
        window.draw(newGameButton);
        window.draw(separationLine2);
        window.draw(separationLine1);
        window.draw(newGameText);
        window.draw(settingsText);
        window.draw(quitText);
        window.display();
    }// end of while loop

    if (exitFlag) {     // if returning from settings or playing a new game, then reload UI
        sf::VideoMode fullScreenMode = sf::VideoMode::getDesktopMode();
        window.create((options.isFullScreen()) ? fullScreenMode : sf::VideoMode(options.getResolution()[0], options.getResolution()[1]), "Fire Fighter", (options.isFullScreen() || options.getResolution()[0] >= fullScreenMode.width) ? sf::Style::Fullscreen : sf::Style::Default);
        _init();
        displayMenu();
    }
}

/**
 * helper method to help initialize ui variables, it is also need to reload changed values from settings
 * returns false if successful, otherwise returns true
 * */
void ui::_init() {
    sf::Image icon = options.getIcon();                                                             // Load icon image
    window.setFramerateLimit(60);                                                              // set frame rate
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());     // Set the window icon
    options.userScreenInfo(window.getSize().x, window.getSize().y);                                 // send user screen info to settings
    font = options.getFont();                                                                       // Set the font
    if (!backgroundImage.loadFromFile("../../resource/img/menu_background.jpg")) {          // load background image for main menu
        std::cerr << "Failed to load background image!" << std::endl;
    }
    if (!music.openFromFile("../../music/EyjafjallaDream.mp3")) {                           // set music for the main menu
        std::cerr << "Failed to load music" << std::endl;
    }
    music.setLoop(true);                                                                            // enable music to loop
}

/** help create the button shapes on screen */
sf::ConvexShape ui::createButtonShape(float width, float height) {
    sf::ConvexShape parallelogram;
    parallelogram.setPointCount(4);
    parallelogram.setPoint(0, sf::Vector2f(0, 0));
    parallelogram.setPoint(1, sf::Vector2f(width, 0));
    parallelogram.setPoint(2, sf::Vector2f(width * 0.8f, height));
    parallelogram.setPoint(3, sf::Vector2f(-width * 0.2f, height));
    parallelogram.setFillColor(sf::Color(54, 207, 213));
    return parallelogram;
}
