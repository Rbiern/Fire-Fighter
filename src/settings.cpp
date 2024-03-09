#include "settings.h"
#include <SFML/Graphics.hpp>
#include "ui.h"

settings::settings() {
    fullscreen = false;
    resolution = res.dv;
    frameRate = 60;
    music = false;
    soundEffects = true;
    language = lang.English;
}
bool isButtonPressed(const sf::RectangleShape& button, const sf::Vector2f& mousePosition) {
    sf::FloatRect buttonBounds = button.getGlobalBounds();
    return buttonBounds.contains(mousePosition);
}

void settings::openSettings(int w, int h) {
    // Create the SFML window
    sf::RenderWindow window(sf::VideoMode(w, h), "Settings");
    sf::Image icon;
    if (!icon.loadFromFile(R"(C:\Users\Pc MSI\CLionProjects\Fire Fighter\resource\img\icon.png)")) {
        std::cerr << "Failed to load icon" << std::endl;
        return;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr()); // Set the window icon

    // Create fonts
    sf::Font font;
    if (!font.loadFromFile(R"(C:\Users\Pc MSI\CLionProjects\Fire Fighter\resource\fonts\Rajdhani-SemiBold.ttf)")) {
        std::cerr << "Failed to load font!" << std::endl;
        return;
    }

    // Create buttons
    sf::RectangleShape button1(sf::Vector2f(100, 50));
    sf::RectangleShape button2(sf::Vector2f(100, 50));
    sf::RectangleShape button3(sf::Vector2f(100, 50));
    sf::RectangleShape button4(sf::Vector2f(100, 50));
    sf::RectangleShape button5(sf::Vector2f(100, 50));
    sf::RectangleShape button6(sf::Vector2f(100, 50));
    sf::RectangleShape button7(sf::Vector2f(100, 50));
    sf::RectangleShape button8(sf::Vector2f(100, 50));

    // Position buttons
    button1.setPosition(50, 50);
    button2.setPosition(200, 50);
    button3.setPosition(350, 50);
    button4.setPosition(50, 150);
    button5.setPosition(200, 150);
    button6.setPosition(350, 150);
    button7.setPosition(500, 150);
    button8.setPosition(650, 150);

    // Set button colors
    button1.setFillColor(sf::Color::Red);
    button2.setFillColor(sf::Color::Green);
    button3.setFillColor(sf::Color::Blue);
    button4.setFillColor(sf::Color::Yellow);
    button5.setFillColor(sf::Color::Magenta);
    button6.setFillColor(sf::Color::Cyan);
    button7.setFillColor(sf::Color::White);
    button8.setFillColor(sf::Color::Black);

    // Create exit button
    sf::RectangleShape exitButton(sf::Vector2f(60, 30));
    exitButton.setPosition(w - 100, h - 50);
    exitButton.setFillColor(sf::Color::Red);

    // Set exit button text
    sf::Text exitText("Exit", font, 20);
    exitText.setPosition(w - 90, h - 45); // Adjusting position of text

    // Create language buttons text with color RGB(235, 70, 60)
    sf::Text englishText("English", font, 20);
    englishText.setPosition(70, 55); // Adjusting position of text
    englishText.setFillColor(sf::Color(235, 70, 60)); // Setting text color

    sf::Text koreanText("Korean", font, 20);
    koreanText.setPosition(220, 55); // Adjusting position of text
    koreanText.setFillColor(sf::Color(235, 70, 60)); // Setting text color

    sf::Text mandarinText("Mandarin", font, 20);
    mandarinText.setPosition(370, 55); // Adjusting position of text
    mandarinText.setFillColor(sf::Color(235, 70, 60)); // Setting text color

// Create resolution buttons text with color RGB(235, 70, 60)
    sf::Text resolutionText1("640, 360", font, 20);
    resolutionText1.setPosition(70, 155); // Adjusting position of text
    resolutionText1.setFillColor(sf::Color(235, 70, 60)); // Setting text color

    sf::Text resolutionText2("1280, 720", font, 20);
    resolutionText2.setPosition(220, 155); // Adjusting position of text
    resolutionText2.setFillColor(sf::Color(235, 70, 60)); // Setting text color

    sf::Text resolutionText3("1920, 1080", font, 20);
    resolutionText3.setPosition(370, 155); // Adjusting position of text
    resolutionText3.setFillColor(sf::Color(235, 70, 60)); // Setting text color

    sf::Text resolutionText4("3840, 2160", font, 20);
    resolutionText4.setPosition(520, 155); // Adjusting position of text
    resolutionText4.setFillColor(sf::Color(235, 70, 60)); // Setting text color
    // Main loop
    while (window.isOpen())
    {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                if (isButtonPressed(button1, window.mapPixelToCoords(mousePosition))) {
                    std::cout << "Button 1 Pressed!" << std::endl;
                    language = lang.Korean;
                }
                if (isButtonPressed(button2, window.mapPixelToCoords(mousePosition)))
                    std::cout << "Button 2 Pressed!" << std::endl;
                if (isButtonPressed(button3, window.mapPixelToCoords(mousePosition)))
                    std::cout << "Button 3 Pressed!" << std::endl;
                if (isButtonPressed(button4, window.mapPixelToCoords(mousePosition))) {
                    std::cout << "Button 4 Pressed!" << std::endl;
                    resolution = res.dv;
                }
                if (isButtonPressed(button5, window.mapPixelToCoords(mousePosition))) {
                    std::cout << "Button 5 Pressed!" << std::endl;
                    resolution = res.sd;
                }
                if (isButtonPressed(button6, window.mapPixelToCoords(mousePosition))) {
                    std::cout << "Button 6 Pressed!" << std::endl;
                    resolution = res.hd;
                }
                if (isButtonPressed(button7, window.mapPixelToCoords(mousePosition))) {
                    std::cout << "Button 7 Pressed!" << std::endl;
                    resolution = res.uhd;
                }
                if (isButtonPressed(button8, window.mapPixelToCoords(mousePosition)))
                    std::cout << "Button 8 Pressed!" << std::endl;
                if (isButtonPressed(exitButton, window.mapPixelToCoords(mousePosition))) {
                    window.close(); // Close the window if exit button is pressed
                    sf::VideoMode fullscreenMode = sf::VideoMode::getFullscreenModes()[0]; // Get the first available fullscreen mode
                   // sf::RenderWindow window(sf::VideoMode(resolution[0], resolution[1]), "Fire Fighter"); //make new window
//                    sf::RenderWindow window(sf::VideoMode(fullscreenMode), "Fixed Window", sf::Style::None | sf::Style::Titlebar);
                    sf::RenderWindow window(sf::VideoMode(resolution[0], resolution[1]), "Maximized Window", sf::Style::Fullscreen);
                    mainWindow::ui program(window); // initialize ui window
                    program.displayMenu(); // method from ui to run the main program loop
                }
            }
        }

        // Clear the window
        window.clear();

        // Draw buttons
        window.draw(button1);
        window.draw(button2);
        window.draw(button3);
        window.draw(button4);
        window.draw(button5);
        window.draw(button6);
        window.draw(button7);
        window.draw(button8);

        // Draw exit button
        window.draw(exitButton);
        window.draw(exitText);

        // Draw language buttons text
        window.draw(englishText);
        window.draw(koreanText);
        window.draw(mandarinText);

        // Draw resolution buttons text
        window.draw(resolutionText1);
        window.draw(resolutionText2);
        window.draw(resolutionText3);
        window.draw(resolutionText4);

        // Display content
        window.display();
    }
}



void settings::fullScreenSettings() {

}

void settings::changeResoltion() {

}

void settings::changeFrameRate() {

}

void settings::toggleMusic() {

}

void settings::toggleSoundEffects() {

}

void settings::toggleEnglish() {

}

void settings::toggleKorean() {

}

void settings::toggleMandarin() {

}

int *settings::getResolution() {
    return resolution;
}

std::string *settings::getLanguage() {
    return language;
}
