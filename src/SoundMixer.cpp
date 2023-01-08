#include "SoundMixer.h"

SoundMixer::SoundMixer() {
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
}

SoundMixer::~SoundMixer() {
    Mix_FreeChunk(menu);
    Mix_CloseAudio();
}

bool SoundMixer::load() {
    soundtrack = Mix_LoadWAV("../resources/sounds/soundtrack.wav");
    if (soundtrack == 0) {
        printf("error loading soundtrack.wav");
        return false;
    }
    menu = Mix_LoadWAV("../resources/sounds/menu.wav");
    if (menu == 0) {
        printf("error loading menu.wav");
        return false;
    }
    death = Mix_LoadWAV("../resources/sounds/death.wav");
    if (death == 0) {
        printf("error loading death.wav");
        return false;
    }
    shot = Mix_LoadWAV("../resources/sounds/shot.wav");
    if (shot == 0) {
        printf("error loading shot.wav");
        return false;
    }
    buttonClick = Mix_LoadWAV("../resources/sounds/button_click.wav");
    if (buttonClick == 0) {
        printf("error loading soundtrack.wav");
        return false;
    }
    collision = Mix_LoadWAV("../resources/sounds/collision.wav");
    if (collision == 0) {
        printf("error loading soundtrack.wav");
        return false;
    }
    error = Mix_LoadWAV("../resources/sounds/error.wav");
    if (error == 0) {
        printf("error loading soundtrack.wav");
        return false;
    }
    gameOver = Mix_LoadWAV("../resources/sounds/game_over.wav");
    if (gameOver == 0) {
        printf("error loading soundtrack.wav");
        return false;
    }
    win = Mix_LoadWAV("../resources/sounds/win.wav");
    if (win == 0) {
        printf("error loading soundtrack.wav");
        return false;
    }
    Mix_VolumeChunk(soundtrack, MIX_MAX_VOLUME/4);
    Mix_VolumeChunk(menu, MIX_MAX_VOLUME/4);
    Mix_VolumeChunk(death, MIX_MAX_VOLUME/8);
    Mix_VolumeChunk(shot, MIX_MAX_VOLUME/8);
    Mix_VolumeChunk(buttonClick, MIX_MAX_VOLUME/8);
    Mix_VolumeChunk(collision, MIX_MAX_VOLUME/6);
    Mix_VolumeChunk(error, MIX_MAX_VOLUME/8);
    Mix_VolumeChunk(gameOver, MIX_MAX_VOLUME/4);
    Mix_VolumeChunk(win, MIX_MAX_VOLUME/4);
    return true;
}

void SoundMixer::playSoundSoundtrack() {
    Mix_PlayChannel(2, soundtrack, -1);
}

void SoundMixer::playSoundMenu() {
    Mix_PlayChannel(2, menu, -1);
}

void SoundMixer::playSoundDeath() {
    Mix_PlayChannel(-1, death, 0);
}

void SoundMixer::playSoundShot() {
    Mix_PlayChannel(-1, shot, 0);
}

void SoundMixer::playSoundButtonClick() {
    Mix_PlayChannel(-1, buttonClick, 0);
}

void SoundMixer::playSoundCollision() {
    Mix_PlayChannel(-1, collision, 0);
}

void SoundMixer::playSoundError() {
    Mix_PlayChannel(-1, error, 0);
}

void SoundMixer::playSoundGameOver() {
    Mix_PlayChannel(2, gameOver, 0);
}

void SoundMixer::playSoundWin() {
    Mix_PlayChannel(2, win, 0);
}