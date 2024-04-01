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
        int uniqueRes[2];
    }res;
    int dataFromFile[7]{};
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
        sf::String English[26] = {"NEW GAME", "SETTINGS", "QUIT", "Fullscreen", "Music", "Sound Effects", "Rotation", "On", "Off", "Select Languages", "Select Resolution", "Apply", "Cancel", "Choose a Character", "Go Back", "Water Girl", "Water Boy", "Exit", "Retry", "Game Over!", "Exit Game", "Resume Game", "Score: ", "Enemies Killed: ", "Stage: ", "Enemies Remaining: "};
        sf::String Korean[26] = {L"\uC0C8 \uAC8C\uC784", L"\uC138\uD305", L"\uC885\uB8CC", L"\uc804\uccb4\u0020\ud654\uba74\u000d", L"\uc74c\uc545", L"\uc74c\ud5a5\u0020\ud6a8\uacfc", L"\ud68c\uc804", L"\ucf1c\uc9d0", L"\uaebc\uc9d0", L"\uc5b8\uc5b4\u0020\uc120\ud0dd", L"\ud574\uc0c1\ub3c4", L"\ud655\uc778", L"\ucde8\uc18c", L"\uce90\ub9ad\ud130\u0020\uc120\ud0dd",L"\ub4a4\ub85c", L"\uBB3C \uC18C\uB140", L"\uBB3C\uC18C\uB144", L"\uCD9C\uAD6C", L"\uc7ac\uc2dc\uc791", L"\uac8c\uc784\u0020\uc624\ubc84\u000d", L"\uc885\ub8cc\u000d", L"\uac8c\uc784\u0020\uc7ac\uac8c",L"\uc810\uc218\uFF1A", L"\uc8fd\uc740\u0020\uc801\uFF1A", L"\uc2a4\ud14c\uc774\uc9c0\uFF1A", L"\ub0a8\uc740\u0020\uc801\u0020\u003a\u0020"};
        sf::String Mandarin[26] = {L"\u65B0\u6E38\u620F", L"\u8BBE\u7F6E", L"\u8F9E\u804C", L"\u5168\u5C4F", L"\u97F3\u4E50", L"\u58F0\u97F3\u7279\u6548", L"\u56DE\u8F6C", L"\u5728", L"\u79BB\u5F00", L"\u9009\u62E9\u8BED\u8A00", L"\u9009\u62E9\u5206\u8FA8\u7387", L"\u7533\u8BF7", L"\u53D6\u6D88", L"\u9009\u62E9\u4E00\u4E2A\u89D2\u8272", L"\u56DE\u53BB", L"\u6C34\u5973\u5B69", L"\u706B\u5973\u5B69", L"\u51FA\u53E3", L"\u91CD\u8BD5", L"\u6E38\u620F\u7ED3\u675F\uFF01", L"\u9000\u51FA\u6E38\u620F", L"\u5206\u6570\uFF1A", L"\u6740\u6B7B\u7684\u654C\u4EBA\uFF1A", L"\u9636\u6BB5\uFF1A", L"\u6b8b\u654c\u0020\u003a\u0020"};
    }lang;
public:
    settings();
    ~settings();
    void openSettings();
    int* getResolution();
    bool isFullScreen() const;
    bool toggleMusic() const;
    bool toggleSounds() const;
    sf::String * getLanguage();
    sf::Font getFont();
    sf::Image getIcon();
    float widthScaling(float x);
    float heightScaling(float y);
    sf::Vector2u getVector();
    void userScreenInfo(int x, int y);
private:
    bool isButtonPressed(const sf::ConvexShape& button, const sf::Vector2f& mousePosition);
    bool isButtonPressed(const sf::RectangleShape& button, const sf::Vector2f& mousePosition);
    sf::ConvexShape createParallelogram(float width, float height);
    sf::RectangleShape createRectangle(float width, float height);
};

#endif //FIRE_FIGHTER_SETTINGS_H
