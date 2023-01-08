#include "Picture.h"

// Constructor
Picture::Picture() {
    texture = NULL;
    rect = {0, 0, 0, 0};
}

int Picture::getX() {
    return rect.x;
}

int Picture::getY() {
    return rect.y;
}

void Picture::setX(int x) {
    rect.x = x;
}

void Picture::setY(int y) {
    rect.y = y;
}

void Picture::setPosition(double x, double y) {
    rect.x = x;
    rect.y = y;
}

SDL_Rect *(Picture::getRect)() {
    return &rect;
}

void Picture::setRect(SDL_Rect rect) {
    this->rect = rect;
}

SDL_Texture *Picture::getTexture() {
    return texture;
}

int Picture::getXCenter() {
    return rect.w/2;
}

int Picture::getYCenter() {
    return rect.h/2;
}

bool Picture::load(const char *file, SDL_Renderer *renderer) {
    destroy();

    SDL_Surface *surface = IMG_Load(file);
    if (!surface) {
        printf("Error creating surface: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_Quit();
        return false;
    }
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (!texture) {
        printf("Error creating texture: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_Quit();
        return false;
    }

    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
    /*rect.w = surface->w;
    rect.h = surface->h;*/

    return true;
}

void Picture::draw(SDL_Renderer *renderer, const SDL_Rect *rect, double angle) {
    if (texture != NULL) {
        SDL_Point p = {getXCenter(), getYCenter()};

        if (SDL_RenderCopyEx(renderer, texture, rect, &this->rect, angle, &p, SDL_FLIP_NONE) != 0) {
            printf("Error drawing picture: %s\n", SDL_GetError());
        }
    }

}

void Picture::destroy() {
    if (texture != NULL) {
        SDL_DestroyTexture(texture);
        texture = NULL;
        rect.x = 0;
        rect.y = 0;
        rect.w = 0;
        rect.h = 0;
    }
}