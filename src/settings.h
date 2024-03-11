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
    class languages {
    public:
        sf::String English[13] = {"NEW GAME", "SETTINGS", "QUIT", "Fullscreen", "Music", "Sound Effects", "Rotation", "On", "Off", "Select Languages", "Select Resolution", "Apply", "Cancel"};
        sf::String Korean[13] = {L"\uC0C8 \uAC8C\uC784", L"\uC138\uD305", L"\uC885\uB8CC", "Fullscreen", "Music", "Sound Effects", "Rotation", "On", "Off", "Select Languages", "Select Resolution", "Apply", "Cancel"};
        sf::String Mandarin[13] = {L"\u65B0\u6E38\u620F", L"\u8BBE\u7F6E", L"\u8F9E\u804C", L"\u5168\u5C4F", L"\u97F3\u4E50", L"\u58F0\u97F3\u7279\u6548", L"\u56DE\u8F6C", L"\u5728", L"\u79BB\u5F00", L"\u9009\u62E9\u8BED\u8A00", L"\u9009\u62E9\u5206\u8FA8\u7387", L"\u7533\u8BF7", L"\u53D6\u6D88" };
    }lang;
public:
    settings();
    void openSettings(int w, int h);
    int* getResolution();
    bool isFullScreen();
    bool toggleMusic();
    sf::String * getLanguage();
private:
    bool isButtonPressed(const sf::ConvexShape& button, const sf::Vector2f& mousePosition);
    bool isButtonPressed(const sf::RectangleShape& button, const sf::Vector2f& mousePosition);
    sf::ConvexShape createParallelogram(float width, float height); // change name to createButtonShape
    sf::RectangleShape createRectangle(float width, float height); // change name to createButtonShape
};

#endif //FIRE_FIGHTER_SETTINGS_H
