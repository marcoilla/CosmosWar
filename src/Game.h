#ifndef ARCADE_GAME_GAME_H
#define ARCADE_GAME_GAME_H

#include "include.h"
#include "Picture.h"
#include "Player.h"
#include "Asteroid.h"
#include "CollisionManager.h"
#include "NetworkManager.h"
#include "MousePointer.h"
#include "Menu.h"
#include "SoundMixer.h"

enum game_states {
    MENU = 0,
    PLAY = 1,
};

class Game {
public:
    // Game::FPS of the game
    // If you enable VSYNC in renderer you have to set FPS according to refresh rate of your monitor,
    // if you don't do this, you could have problem with velocity of players and bullets
    static const int FPS = 60.0; // Pay attention to VSYNC settings
    Game();
    int init(const char* title);
    void connect();
    void prepare();
    void transfer();
    void handleEvents();
    void update();
    void render();
    void close();
    void reset();
    bool isRunning();
    int getNumPlayers();

private:
    static const int num_players = 2;
    Picture background, heart, bullet;
    Player players[num_players];
    Asteroid asteroids[3];
    MousePointer mousePointer;
    CollisionManager collisionManager;
    Menu menu;
    SoundMixer soundMixer;
    game_states currentGameState = MENU;
    bool running;
    char host;
    pthread_t th;
};

#endif //ARCADE_GAME_GAME_H