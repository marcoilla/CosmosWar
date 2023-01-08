#ifndef ARCADE_GAME_MENU_H
#define ARCADE_GAME_MENU_H

#include "Picture.h"
#include "MousePointer.h"

enum menu_states {
    START = 0,
    SERVER_CLIENT = 1,
    IP_ADDRESS = 2,
    WAITING_CONNECTION = 3,
    GAME_OVER = 4,
    WIN = 5
};

class Menu {
public:
    Picture title;
    Picture playButton, exitButton;
    Picture serverButton, clientButton;
    Picture ipAddress, enterButton, waitingConnectionButton;
    Picture gameOver, win;
    menu_states currentMenuState = START;
    char ip_address[15] = " ";
    int position = 0;
    bool load(SDL_Renderer *renderer);
    void update(SDL_Renderer *renderer, MousePointer mousePointer);
    void updateEvent(SDL_Event event);
    void render(SDL_Renderer *renderer);
    bool playIsPress();
    bool exitIsPress();
    bool serverIsPress();
    bool clientIsPress();
    bool enterIsPress();
    bool waitingConnectionIsPress();
    bool gameOverIsPress();
    bool winIsPress();
private:
    bool playPress, exitPress;
    bool serverPress, clientPress;
    bool enterPress;
    bool waitingConnectionPress;
    bool gameOverPress, winPress;
    void display_text(SDL_Renderer *renderer, std::string text, int x, int y);
};

#endif //ARCADE_GAME_MENU_H
