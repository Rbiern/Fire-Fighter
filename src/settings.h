#ifndef FIRE_FIGHTER_SETTINGS_H
#define FIRE_FIGHTER_SETTINGS_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <bitset>

class settings {
private:
    class resolutionPairs {
    public:
        int dv[2] = {640, 360};
        int sd[2] = {1280, 720};
        int hd[2] = {1920, 1080};
        int uhd[2] = {3840, 2160};
    }res;
    int array[7];
    bool fullscreen;
    int *resolution;
    int frameRate;
    int rotation;
    bool music;
    bool soundEffects;
    sf::String* language;
    sf::Font font;
    sf::Image icon;
    class languages {
    public:
        sf::String English[17] = {"NEW GAME", "SETTINGS", "QUIT", "Fullscreen", "Music", "Sound Effects", "Rotation", "On", "Off", "Select Languages", "Select Resolution", "Apply", "Cancel", "Choose a character", "Go Back", "Fire Girl", "Water Boy"};
        sf::String Korean[17] = {L"\uC0C8 \uAC8C\uC784", L"\uC138\uD305", L"\uC885\uB8CC", L"\uc804\uccb4\u0020\ud654\uba74\u000d", L"\uc74c\uc545", L"\uc74c\ud5a5\u0020\ud6a8\uacfc", L"\ud68c\uc804", L"\ucf1c\uc9d0", L"\uaebc\uc9d0", L"\uc5b8\uc5b4\u0020\uc120\ud0dd", L"\ud574\uc0c1\ub3c4", L"\ud655\uc778", L"\ucde8\uc18c", L"\uce90\ub9ad\ud130\u0020\uc120\ud0dd",L"\ubb3c", L"\ubd88", L"\u97F3\u4E50"};
        sf::String Mandarin[17] = {L"\u65B0\u6E38\u620F", L"\u8BBE\u7F6E", L"\u8F9E\u804C", L"\u5168\u5C4F", L"\u97F3\u4E50", L"\u58F0\u97F3\u7279\u6548", L"\u56DE\u8F6C", L"\u5728", L"\u79BB\u5F00", L"\u9009\u62E9\u8BED\u8A00", L"\u9009\u62E9\u5206\u8FA8\u7387", L"\u7533\u8BF7", L"\u53D6\u6D88", L"\u9009\u62E9\u4E00\u4E2A\u89D2\u8272", L"\u56DE\u53BB", L"\u706B\u5973\u5B69", L"\u706B\u5973\u5B69"};
    }lang;
public:
    settings();
    void openSettings(int w, int h);
    int* getResolution();
    bool isFullScreen() const;
    bool toggleMusic() const;
    sf::String * getLanguage();
    sf::Font getFont();
    sf::Image getIcon();
private:
    bool isButtonPressed(const sf::ConvexShape& button, const sf::Vector2f& mousePosition);
    bool isButtonPressed(const sf::RectangleShape& button, const sf::Vector2f& mousePosition);
    sf::ConvexShape createParallelogram(float width, float height); // change name to createButtonShape
    sf::RectangleShape createRectangle(float width, float height); // change name to createButtonShape
};

#endif //FIRE_FIGHTER_SETTINGS_H
