#ifndef ARCADE_GAME_PERSONAL_ASTEROID_H
#define ARCADE_GAME_PERSONAL_ASTEROID_H

#include "include.h"
#include "Picture.h"
#include "Player.h"

class Asteroid : public Picture {
public:
    Asteroid();
    void setXPos(int x);
    void setYPos(int y);
    void setDial(int dial, Player *players);
    bool load(const char *file, SDL_Renderer *renderer);
private:
    int x_pos;
    int y_pos;
};

#endif //ARCADE_GAME_PERSONAL_ASTEROID_H
