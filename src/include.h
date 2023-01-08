#ifndef ARCADE_GAME_INCLUDE_H
#define ARCADE_GAME_INCLUDE_H

// Include library
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <string>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

// SDL_Event code
#define KEYDOWN_W (1)
#define KEYDOWN_A (2)
#define KEYDOWN_S (3)
#define KEYDOWN_D (4)
#define KEYUP_W (5)
#define KEYUP_A (6)
#define KEYUP_S (7)
#define KEYUP_D (8)
#define MOUSEBUTTONDOWN_LEFT (9)

static SDL_Event int_to_event(int input) {
    SDL_Event event;
    switch (input) {
        case KEYDOWN_W:
            event.type = SDL_KEYDOWN;
            event.key.keysym.scancode = SDL_SCANCODE_W;
            break;
        case KEYDOWN_A:
            event.type = SDL_KEYDOWN;
            event.key.keysym.scancode = SDL_SCANCODE_A;
            break;
        case KEYDOWN_S:
            event.type = SDL_KEYDOWN;
            event.key.keysym.scancode = SDL_SCANCODE_S;
            break;
        case KEYDOWN_D:
            event.type = SDL_KEYDOWN;
            event.key.keysym.scancode = SDL_SCANCODE_D;
            break;
        case KEYUP_W:
            event.type = SDL_KEYUP;
            event.key.keysym.scancode = SDL_SCANCODE_W;
            break;
        case KEYUP_A:
            event.type = SDL_KEYUP;
            event.key.keysym.scancode = SDL_SCANCODE_A;
            break;
        case KEYUP_S:
            event.type = SDL_KEYUP;
            event.key.keysym.scancode = SDL_SCANCODE_S;
            break;
        case KEYUP_D:
            event.type = SDL_KEYUP;
            event.key.keysym.scancode = SDL_SCANCODE_D;
            break;
        case MOUSEBUTTONDOWN_LEFT:
            event.type = SDL_MOUSEBUTTONDOWN;
            event.button.button = SDL_BUTTON_LEFT;
            break;
    }
    return event;
}

// method to convert SDL_Event to int
static int event_to_int(SDL_Event event) {
    int input = 0;
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.scancode) {
            case SDL_SCANCODE_W:
                input = KEYDOWN_W;
                break;
            case SDL_SCANCODE_A:
                input = KEYDOWN_A;
                break;
            case SDL_SCANCODE_S:
                input = KEYDOWN_S;
                break;
            case SDL_SCANCODE_D:
                input = KEYDOWN_D;
                break;
        }
    } else if (event.type == SDL_KEYUP) {
        switch (event.key.keysym.scancode) {
            case SDL_SCANCODE_W:
                input = KEYUP_W;
                break;
            case SDL_SCANCODE_A:
                input = KEYUP_A;
                break;
            case SDL_SCANCODE_S:
                input = KEYUP_S;
                break;
            case SDL_SCANCODE_D:
                input = KEYUP_D;
                break;
        }
    } else if (event.type == SDL_MOUSEBUTTONDOWN) {
        if(event.button.button == SDL_BUTTON_LEFT) {
            input = MOUSEBUTTONDOWN_LEFT;
        }
    }
    return input;
}

#endif //ARCADE_GAME_INCLUDE_H
