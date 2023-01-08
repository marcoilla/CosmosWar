#ifndef ARCADE_GAME_SOUNDMIXER_H
#define ARCADE_GAME_SOUNDMIXER_H

#include "include.h"

class SoundMixer {
public:
    SoundMixer();
    ~SoundMixer();
    bool load();
    void playSoundSoundtrack();
    void playSoundMenu();
    void playSoundDeath();
    void playSoundShot();
    void playSoundButtonClick();
    void playSoundCollision();
    void playSoundError();
    void playSoundGameOver();
    void playSoundWin();
private:
    Mix_Chunk* soundtrack;
    Mix_Chunk* menu;
    Mix_Chunk* death;
    Mix_Chunk* shot;
    Mix_Chunk* buttonClick;
    Mix_Chunk* collision;
    Mix_Chunk* error;
    Mix_Chunk* gameOver;
    Mix_Chunk* win;
};


#endif //ARCADE_GAME_SoundMixer_H
