#include "Asteroid.h"

Asteroid::Asteroid() {
    x_pos = 0;
    y_pos = 0;
}

void Asteroid::setDial(int dial, Player *players) {
    // first dial (0-500)
    // second dial (550-1100)
    // third dial (1150-1600)

    srand((unsigned) time(NULL));

    do {
        switch (dial) {
            case 1:
                x_pos = rand()%(500 - getRect()->w);
                y_pos = rand()%(700 - getRect()->h);
                break;
            case 2:
                x_pos = rand()%(550 - getRect()->w*3) + 550;
                y_pos = rand()%(1000 - getRect()->h);
                break;
            case 3:
                x_pos = rand()%(450 - getRect()->w) + 1100;
                y_pos = rand()%(700 - getRect()->h) + 300;
                break;

        }
        setPosition(x_pos, y_pos);
    } while (SDL_HasIntersection(getRect(), players[0].getRect()) || SDL_HasIntersection(getRect(), players[1].getRect()));
}

bool Asteroid::load(const char *file, SDL_Renderer *renderer) {
    if (!Picture::load(file, renderer)) {
        return false;
    }

    getRect()->h = 150;
    getRect()->w = 150;

    return true;
}