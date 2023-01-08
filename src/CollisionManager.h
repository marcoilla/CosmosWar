#ifndef ARCADE_GAME_COLLISIONMANAGER_H
#define ARCADE_GAME_COLLISIONMANAGER_H

#include "include.h"
#include "Player.h"
#include "Asteroid.h"
#include "MousePointer.h"
#include "SoundMixer.h"

class CollisionManager {
public:
    void checkPlayersBulletsCollisions(Player *players, SDL_Renderer *renderer, SoundMixer &soundMixer);
    void checkPlayersAsteroidsCollisions(Player *players, Asteroid *asteroids, SoundMixer &soundMixer);
    void checkPlayerPlayerCollision(Player *players);
    void checkBulletsAsteroidsCollisions(Player *players, Asteroid *asteroids);
    void checkMouseButtonCollision(MousePointer mousePointer, Picture button);
private:
    void bounceBack(Player *player);
    static bool checkCollision(SDL_Rect* A, SDL_Rect* B);
};


#endif //ARCADE_GAME_COLLISION_H
