#include "include.h"
#include "Game.h"

using namespace std;

Game game;

int main() {

    const int frameDelay = 1000/Game::FPS;

    Uint32 frameStart;
    int frameTime;

    if (game.init("Arcade game") > 0) {
        game.close();
    }

    while (game.isRunning()) {
        frameStart = SDL_GetTicks();

        game.handleEvents();
        game.update();
        game.render();

        frameTime = SDL_GetTicks() - frameStart;

        if(frameDelay>frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    game.close();

    return 0;
}
