#ifndef FIRE_FIGHTER_SETTINGS_H
#define FIRE_FIGHTER_SETTINGS_H

#include <iostream>

class settings {
private:
    class resolutionPairs {
    public:
        int dv[2] = {640, 360};
        int sd[2] = {1280, 720};
        int hd[2] = {1920, 1080};
        int uhd[2] = {3840, 2160};
    }res;
    bool fullscreen;
    int *resolution;
    int frameRate;
    int rotation;
    bool music;
    bool soundEffects;
    std::string* language;
    class languages {
    public:
        std::string English[3] = {"NEW GAME", "SETTINGS", "QUIT"};
        std::string Korean[3] = {"새 게임", "세팅", "종료"};
        std::string Mandarin[3] = {"新游戏", "设置", "辞职"};
    }lang;
public:
    settings();
    void openSettings(int w, int h);
    void fullScreenSettings();
    void changeResoltion();
    void changeFrameRate();
    void toggleMusic();
    void toggleSoundEffects();
    void toggleEnglish();
    void toggleKorean();
    void toggleMandarin();
    int* getResolution();
    std::string* getLanguage();
};

#endif //FIRE_FIGHTER_SETTINGS_H
