#ifndef ARCADE_GAME_PERSONAL_MOUSEPOINTER_H
#define ARCADE_GAME_PERSONAL_MOUSEPOINTER_H

#include "include.h"

class MousePointer : public Picture {
public:
    SDL_Rect point;

    void load(SDL_Renderer *renderer) {
        Picture::load("../resources/img/mousepointer.png", renderer);

        point.h = 1.0;
        point.w = 1.0;
    }

    void update() {
        SDL_ShowCursor(false);
        SDL_GetMouseState(&getRect()->x, &getRect()->y);
        point.x = getRect()->x + getRect()->w/2;
        point.y = getRect()->y + getRect()->h/2;
    }

    int getXPos() { return point.x; }
    int getYPos() { return point.y; }
};

#endif //ARCADE_GAME_PERSONAL_MOUSEPOINTER_H
