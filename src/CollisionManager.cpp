#include "CollisionManager.h"
#include "Game.h"


bool CollisionManager::checkCollision(SDL_Rect* A, SDL_Rect* B) {
    int aHBuf = A->h / 10;
    int aWBuf = A->w / 10;
    int bHBuf = B->h / 10;
    int bWBuf = B->w / 10;
    // if the bottom of A is less than the top of B - no collision
    if((A->y + A->h) - aHBuf <= B->y + bHBuf)  { return false; }
    // if the top of A is more than the bottom of B = no collision
    if(A->y + aHBuf >= (B->y + B->h) - bHBuf)  { return false; }
    // if the right of A is less than the left of B - no collision
    if((A->x + A->w) - aWBuf <= B->x +  bWBuf) { return false; }
    // if the left of A is more than the right of B - no collision
    if(A->x + aWBuf >= (B->x + B->w) - bWBuf)  { return false; }
    // otherwise there has been a collision
    return true;
}

void CollisionManager::bounceBack(Player *player) {
    player->updateXPos(-300.0*cos((player->getAngle() - 90)*M_PI/180)*1.0/Game::FPS*player->getUp());
    player->updateYPos(-300.0*sin((player->getAngle() - 90)*M_PI/180)*1.0/Game::FPS*player->getUp());
    player->updateXPos(-300.0*cos((player->getAngle() + 180)*M_PI/180)*1.0/Game::FPS*player->getLeft());
    player->updateYPos(-300.0*sin((player->getAngle() + 180)*M_PI/180)*1.0/Game::FPS*player->getLeft());
    player->updateXPos(-300.0*cos((player->getAngle() + 90)*M_PI/180)*1.0/Game::FPS*player->getDown());
    player->updateYPos(-300.0*sin((player->getAngle() + 90)*M_PI/180)*1.0/Game::FPS*player->getDown());
    player->updateXPos(-300.0*cos(player->getAngle()*M_PI/180)*1.0/Game::FPS*player->getRight());
    player->updateYPos(-300.0*sin(player->getAngle()*M_PI/180)*1.0/Game::FPS*player->getRight());
}

void CollisionManager::checkPlayersBulletsCollisions(Player *players, SDL_Renderer *renderer, SoundMixer &soundMixer) {
    // check collision between players and bullets of other players
    for (int i = 0; i < players[1].getBulletsSize(); ++i) {
        if (players[0].getLife() > 0) {
            if (players[1].getBullets()[i].isMoving()) {
                if (checkCollision(players[0].getRect(), players[1].getBullets()[i].getRect())) {
                    players[0].hit(renderer);
                    players[1].getBullets()[i].destroy();
                    soundMixer.playSoundDeath();
                }
            }
        }
    }
    for (int i = 0; i < players[0].getBulletsSize(); ++i) {
        if (players[1].getLife() > 0) {
            if (players[0].getBullets()[i].isMoving()) {
                if (checkCollision(players[1].getRect(), players[0].getBullets()[i].getRect())) {
                    players[1].hit(renderer);
                    players[0].getBullets()[i].destroy();
                    soundMixer.playSoundDeath();
                }
            }
        }
    }
}

void CollisionManager::checkPlayersAsteroidsCollisions(Player *players, Asteroid *asteroids, SoundMixer &soundMixer) {
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (SDL_HasIntersection(players[i].getRect(), asteroids[j].getRect())) {
                bounceBack(&players[i]);
                soundMixer.playSoundCollision();
            }
        }
    }
}

void CollisionManager::checkPlayerPlayerCollision(Player *players) {
    if (SDL_HasIntersection(players[0].getRect(), players[1].getRect())) {
        bounceBack(&players[0]);
        bounceBack(&players[1]);
    }
}

void CollisionManager::checkBulletsAsteroidsCollisions(Player *players, Asteroid *asteroids) {
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 3; ++j) {
            for(int k = 0; k < players[i].getBulletsSize(); ++k) {
                if (checkCollision(players[i].getBullets()[k].getRect(), asteroids[j].getRect())) {
                    players[i].getBullets()[k].destroy();
                }
            }
        }
    }
}

void CollisionManager::checkMouseButtonCollision(MousePointer mousePointer, Picture button) {
    if (SDL_HasIntersection(mousePointer.getRect(), button.getRect()))
        printf("Collision with button\n");
}