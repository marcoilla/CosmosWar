#include "Game.h"
#include "Menu.h"
#include "include.h"

// SDL var
static SDL_Window *window;
static SDL_Renderer *renderer;
static SDL_Event event;
// Screen var
static const int WINDOW_WIDTH = 1600;
static const int WINDOW_HEIGHT = 1040;

Game::Game() {
    running = true;
}

int Game::init(const char *title) {
    // attempt to initialize graphics and timer system
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }
    TTF_Init();

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT,SDL_WINDOW_RESIZABLE);
    if (!window) {
        printf("error creating window: %s\n", SDL_GetError());
        return 1;
    }

    // create a renderer, which sets up the graphics hardware
    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    renderer = SDL_CreateRenderer(window, -1, render_flags);
    if (!renderer) {
        printf("error creating renderer: %s\n", SDL_GetError());
        return 1;
    }

    if (!background.load("../resources/img/background.png", renderer)) {
        return 1;
    }

    if (!asteroids[0].load("../resources/img/asteroid.png", renderer)) {
        return 1;
    }
    if (!asteroids[1].load("../resources/img/asteroid.png", renderer)) {
        return 1;
    }
    if (!asteroids[2].load("../resources/img/asteroid.png", renderer)) {
        return 1;
    }

    if (!heart.load("../resources/img/heart_icon.png", renderer)) {
        return 1;
    }

    if (!bullet.load("../resources/img/bullet_icon.png", renderer)) {
        return 1;
    }

    if (!players[0].loadPicture("../resources/img/spaceship-server.png", renderer)) {
        return 1;
    }
    players[0].setClip();
    if (!players[1].loadPicture("../resources/img/spaceship-client.png", renderer)) {
        return 1;
    }
    players[1].setClip();
    // set players position on the screen
    players[0].setPosition(100, WINDOW_HEIGHT / 2);
    players[1].setPosition(WINDOW_WIDTH - 100, WINDOW_HEIGHT / 2);

    mousePointer.load(renderer);

    if (!menu.load(renderer)) {
        return 1;
    }

    soundMixer.load();

    soundMixer.playSoundMenu();

    return 0;
}

void Game::connect() {
    NetworkManager::initServerSock(); // for both client and server

    if (host == 'c') {
        NetworkManager::initClientSock();
        NetworkManager::prepareClient();
        // prepare client players
        players[1].setId(1);
        NetworkManager::sendData(NetworkManager::server_addr, &players[1].getData()[0], 1);
        // waiting server
        pthread_create(&th, NULL, NetworkManager::clientReceiveWaiting, &players[0].getData()[0]);
        } else if (host == 's') {
        NetworkManager::prepareServer();
        // prepare server players
        players[0].setId(0);
        // waiting client
        pthread_create(&th, NULL, NetworkManager::serverReceiveWaiting, &players[1].getData()[0]);
    }
}

void Game::prepare() {
    if (host == 'c') {
        int data[6];
        NetworkManager::receiveData(data, 6);
        asteroids[0].setPosition(data[0], data[1]);
        asteroids[1].setPosition(data[2], data[3]);
        asteroids[2].setPosition(data[4], data[5]);
        // client receiver
        pthread_cancel(th);
        pthread_create(&th, NULL, NetworkManager::receiver, players[0].getData());
    } else if (host == 's') {
        int data[6];
        asteroids[0].setDial(1, players);
        asteroids[1].setDial(2, players);
        asteroids[2].setDial(3, players);
        data[0] = asteroids[0].getX();
        data[1] = asteroids[0].getY();
        data[2] = asteroids[1].getX();
        data[3] = asteroids[1].getY();
        data[4] = asteroids[2].getX();
        data[5] = asteroids[2].getY();
        NetworkManager::sendData(NetworkManager::client_addr, data, 6);
        // server receiver
        pthread_cancel(th);
        pthread_create(&th, NULL, NetworkManager::receiver, players[1].getData());
    }
}

void Game::transfer() {
    SDL_Event event;
    if (host == 'c') {
        if (NetworkManager::transferred) {
            NetworkManager::sendData(NetworkManager::server_addr, players[1].getData(), 4);
            players[1].getData()[1] = 0; // reset
            //NetworkManager::receiveData(players[0].getData(), 4);
            if (players[0].getData()[0] != -1) {
                event = int_to_event(players[0].getData()[1]);
                players[0].handleInput(event, players[0].getData()[2], players[0].getData()[3], renderer, soundMixer);
                players[0].setAngle(players[0].getData()[3], players[0].getData()[2]);
            } else {
                running = false;
                perror("Lost connection with the server");
            }
            NetworkManager::transferred = false;
        }
    } else if (host == 's') {
        NetworkManager::transferred = true;
        if (NetworkManager::transferred) {
            NetworkManager::sendData(NetworkManager::client_addr, players[0].getData(), 4);
            players[0].getData()[1] = 0; //reset
            //NetworkManager::receiveData(players[1].getData(), 4);
            if (players[1].getData()[0] != -1) {
                event = int_to_event(players[1].getData()[1]);
                players[1].handleInput(event, players[1].getData()[2], players[1].getData()[3], renderer, soundMixer);
                players[1].setAngle(players[1].getData()[3], players[1].getData()[2]);
            } else {
                reset();
            }
            NetworkManager::transferred = false;
        }

    }
}

void Game::update() {
    switch (currentGameState) {
        case MENU:
            menu.update(renderer, mousePointer);
            if (NetworkManager::ready) { // wait until client connect
                if (host == 's')
                    NetworkManager::sendData(NetworkManager::client_addr, &players[0].getData()[0], 1);
                players[1].setId(players[1].getData()[0]);
                players[0].setId(players[0].getData()[0]);
                prepare();
                menu.currentMenuState = START;
                currentGameState = PLAY;
                soundMixer.playSoundSoundtrack();
                NetworkManager::ready = false;
            }
            break;
        case PLAY:
            transfer();

            // draw players to the window
            if (host == 'c') {
                players[1].setAngle(mousePointer.getYPos(), mousePointer.getXPos());
            } else if (host == 's') {
                players[0].setAngle(mousePointer.getYPos(), mousePointer.getXPos());
            }
            players[0].move(soundMixer);
            players[1].move(soundMixer);

            collisionManager.checkPlayersBulletsCollisions(players, renderer, soundMixer);
            collisionManager.checkPlayersAsteroidsCollisions(players, asteroids, soundMixer);
            collisionManager.checkPlayerPlayerCollision(players);
            collisionManager.checkBulletsAsteroidsCollisions(players, asteroids);


            if (players[0].getLife() == 0) {
                for (int i = 0; i < players[0].getBulletsSize(); ++i) {
                    if (!players[0].getBullets()[i].isMoving()) {
                        if (host == 'c') {
                            soundMixer.playSoundWin();
                            currentGameState = MENU;
                            menu.currentMenuState = WIN;
                        } else if (host == 's') {
                            soundMixer.playSoundGameOver();
                            currentGameState = MENU;
                            menu.currentMenuState = GAME_OVER;
                        }
                    }
                }
            }
            if (players[1].getLife() == 0) {
                for (int i = 0; i < players[1].getBulletsSize(); ++i) {
                    if (!players[1].getBullets()[i].isMoving()) {
                        if (host == 'c') {
                            soundMixer.playSoundGameOver();
                            currentGameState = MENU;
                            menu.currentMenuState = GAME_OVER;
                        } else if (host == 's') {
                            soundMixer.playSoundWin();
                            currentGameState = MENU;
                            menu.currentMenuState = WIN;
                        }
                    }
                }
            }
            break;
    }
}

void Game::render() {
    int w, h;
    SDL_GetWindowSize(window, &w, &h);
    SDL_RenderSetScale(renderer, (double)w/WINDOW_WIDTH, (double)h/WINDOW_HEIGHT);

    // clear the window
    SDL_RenderClear(renderer);

    background.draw(renderer,NULL, 0);

    switch (currentGameState) {
        case MENU:
            menu.render(renderer);
            break;
        case PLAY:
            // draw players to the window
            players[0].drawFrame(renderer);
            players[0].handleBullets(renderer);
            players[1].drawFrame(renderer);
            players[1].handleBullets(renderer);

            for (int i = 0; i < 3; ++i) {
                asteroids[i].draw(renderer, NULL, 0);
            }

            // handle hearts life
            if (host == 'c') {
                for (int i = 0; i < players[1].getBulletsSize(); ++i) {
                    if (!players[1].getBullets()[i].isMoving()) {
                        bullet.setPosition(WINDOW_WIDTH/2 + 10 + 16*i, 1004);
                        bullet.draw(renderer, NULL, 0);
                    }
                }
                for (int i = 0; i < players[1].getLife(); ++i) {
                    heart.setPosition(WINDOW_WIDTH/2 - 10 - players[1].getLife() * 32 + 32 * i, 1004);
                    heart.draw(renderer, NULL, 0);
                }
            } else if (host == 's') {
                for (int i = 0; i < players[0].getBulletsSize(); ++i) {
                    if (!players[0].getBullets()[i].isMoving()) {
                        bullet.setPosition(WINDOW_WIDTH/2 + 10 + 16*i, 1004);
                        bullet.draw(renderer, NULL, 0);
                    }
                }
                for (int i = 0; i < players[0].getLife(); ++i) {
                    heart.setPosition(WINDOW_WIDTH/2 - 10 - players[0].getLife() * 32 + 32 * i, 1004);
                    heart.draw(renderer, NULL, 0);
                }
            }
            break;
    }

    mousePointer.draw(renderer, NULL, 0);

    SDL_RenderPresent(renderer);
}

void Game::handleEvents() {
    mousePointer.update();

    // process events
    while (SDL_PollEvent(&event)) {
        switch (currentGameState) {
            case MENU:
                switch (event.type) {
                    case SDL_QUIT:
                        running = false;
                        break;
                    case SDL_MOUSEBUTTONDOWN:
                        if (menu.playIsPress()) {
                            soundMixer.playSoundButtonClick();
                            menu.currentMenuState = SERVER_CLIENT;
                        } else if (menu.serverIsPress()) {
                            soundMixer.playSoundButtonClick();
                            host = 's';
                            menu.currentMenuState = IP_ADDRESS;
                        } else if (menu.clientIsPress()) {
                            soundMixer.playSoundButtonClick();
                            host = 'c';
                            menu.currentMenuState = IP_ADDRESS;
                        } else if (menu.enterIsPress()) {
                            soundMixer.playSoundButtonClick();
                            strncpy(NetworkManager::server_ip_addr, menu.ip_address, 15);
                            menu.currentMenuState = WAITING_CONNECTION;
                            connect();
                        } else if (menu.waitingConnectionIsPress() && host == 'c') {
                            soundMixer.playSoundButtonClick();
                            NetworkManager::sendData(NetworkManager::server_addr, &players[1].getData()[0], 1);
                        } else if (menu.gameOverIsPress() || menu.winIsPress()) {
                            soundMixer.playSoundButtonClick();
                            reset();
                            menu.currentMenuState = START;
                        } else if (menu.exitIsPress()) {
                            soundMixer.playSoundButtonClick();
                            running = false;
                        }
                        break;
                    case SDL_KEYDOWN:
                        menu.updateEvent(event);
                        break;
                }
                break;
            case PLAY:
                switch (event.type) {
                    case SDL_QUIT:
                        if (host == 'c') {
                            players[1].setId(-1);
                            NetworkManager::sendData(NetworkManager::server_addr, players[1].getData(), 4);
                        } else if (host == 's') {
                            players[0].setId(-1);
                            NetworkManager::sendData(NetworkManager::client_addr, players[0].getData(), 4);
                        }
                        running = false;
                        break;
                    case SDL_KEYDOWN:
                    case SDL_KEYUP:
                    case SDL_MOUSEBUTTONDOWN:
                        if (host == 'c') {
                            players[1].handleInput(event, mousePointer.getXPos(), mousePointer.getYPos(), renderer, soundMixer);
                        } else if (host == 's') {
                            players[0].handleInput(event, mousePointer.getXPos(), mousePointer.getYPos(), renderer, soundMixer);
                        }
                        break;
                }
                break;

        }
    }
}

void Game::close() {
    running = false;
    pthread_cancel(th);
    NetworkManager::close();
    // clean up resources before exiting
    SDL_DestroyTexture(background.getTexture());
    SDL_DestroyTexture(heart.getTexture());
    SDL_DestroyTexture(bullet.getTexture());
    SDL_DestroyTexture(asteroids[0].getTexture());
    SDL_DestroyTexture(asteroids[1].getTexture());
    SDL_DestroyTexture(asteroids[2].getTexture());
    SDL_DestroyTexture(players[0].getTexture());
    SDL_DestroyTexture(players[1].getTexture());
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
}

void Game::reset() {
    players[0].reset();
    players[1].reset();
    players[0].loadPicture("../resources/img/spaceship-server.png", renderer);
    players[0].setClip();
    players[1].loadPicture("../resources/img/spaceship-client.png", renderer);
    players[1].setClip();
    // set players position on the screen
    players[0].setPosition(100, WINDOW_HEIGHT / 2);
    players[1].setPosition(WINDOW_WIDTH - 100, WINDOW_HEIGHT / 2);
    NetworkManager::close();
    strncpy(menu.ip_address, " ", 15);
    menu.position = 0;
    soundMixer.playSoundMenu();
    currentGameState = MENU;
}

bool Game::isRunning() {
    return running;
}

int Game::getNumPlayers() {
    return num_players;
}