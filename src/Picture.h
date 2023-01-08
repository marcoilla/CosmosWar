#ifndef ARCADE_GAME_PICTURE_H
#define ARCADE_GAME_PICTURE_H

#include "include.h"

class Picture {
public:
    // constructor
    Picture();
    // getter and setter
    int getX();
    int getY();
    void setX(int x);
    void setY(int y);
    void setPosition(double x, double y);
    SDL_Rect* getRect();
    void setRect(SDL_Rect rect);
    SDL_Texture *getTexture();
    // methods
    // get center position
    int getXCenter();
    int getYCenter();
    // load image in the texture and in the rect
    bool load(const char *file, SDL_Renderer *renderer);
    // render rect containing image on the screen
    void draw(SDL_Renderer *renderer, const SDL_Rect *rect, double angle);
    // destructor
    void destroy();

private:
    // attributes
    // texture of image
    SDL_Texture *texture;
    // struct to manage image
    SDL_Rect rect;
};

#endif //ARCADE_GAME_PICTURE_H
