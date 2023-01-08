#include "include.h"
#include "Menu.h"

bool Menu::load(SDL_Renderer *renderer) {
    if (!title.load("../resources/img/cosmos-war.png", renderer)) {
        return false;
    }
    title.getRect()->w *= 8;
    title.getRect()->h *= 8;
    return true;
}

void Menu::update(SDL_Renderer *renderer, MousePointer mousePointer) {
    playPress = false;
    exitPress = false;
    serverPress = false;
    clientPress = false;
    enterPress = false;
    waitingConnectionPress = false;
    gameOverPress = false;
    winPress = false;

    switch (currentMenuState) {
        case START:
            if (SDL_HasIntersection(mousePointer.getRect(), playButton.getRect())) {
                playButton.load("../resources/img/play-button2.png", renderer);
                playPress = true;
            } else {
                playButton.load("../resources/img/play-button1.png", renderer);
            }
            playButton.getRect()->w *= 4;
            playButton.getRect()->h *= 4;
            if (SDL_HasIntersection(mousePointer.getRect(), exitButton.getRect())) {
                exitButton.load("../resources/img/exit-button2.png", renderer);
                exitPress = true;
            } else {
                exitButton.load("../resources/img/exit-button1.png", renderer);
            }
            exitButton.getRect()->w *= 3;
            exitButton.getRect()->h *= 3;

            playButton.setPosition(672, 500);
            exitButton.setPosition(713, 670);
            break;
        case SERVER_CLIENT:
            if (SDL_HasIntersection(mousePointer.getRect(), serverButton.getRect())) {
                serverButton.load("../resources/img/server-button2.png", renderer);
                serverPress = true;
            } else {
                serverButton.load("../resources/img/server-button1.png", renderer);
            }
            serverButton.getRect()->w *= 4;
            serverButton.getRect()->h *= 4;
            if (SDL_HasIntersection(mousePointer.getRect(), clientButton.getRect())) {
                clientButton.load("../resources/img/client-button2.png", renderer);
                clientPress = true;
            } else {
                clientButton.load("../resources/img/client-button1.png", renderer);
            }
            clientButton.getRect()->w *= 4;
            clientButton.getRect()->h *= 4;
            if (SDL_HasIntersection(mousePointer.getRect(), exitButton.getRect())) {
                exitButton.load("../resources/img/exit-button2.png", renderer);
                exitPress = true;
            } else {
                exitButton.load("../resources/img/exit-button1.png", renderer);
            }
            exitButton.getRect()->w *= 3;
            exitButton.getRect()->h *= 3;

            serverButton.setPosition(412, 500);
            clientButton.setPosition(844, 500);
            exitButton.setPosition(713, 670);
            break;
        case IP_ADDRESS:
            ipAddress.load("../resources/img/ip-address.png", renderer);
            ipAddress.getRect()->w *= 4;
            ipAddress.getRect()->h *= 4;
            if (SDL_HasIntersection(mousePointer.getRect(), enterButton.getRect())) {
                enterButton.load("../resources/img/enter-button2.png", renderer);
                enterPress = true;
            } else {
                enterButton.load("../resources/img/enter-button1.png", renderer);
            }
            enterButton.getRect()->w *= 3;
            enterButton.getRect()->h *= 3;
            if (SDL_HasIntersection(mousePointer.getRect(), exitButton.getRect())) {
                exitButton.load("../resources/img/exit-button2.png", renderer);
                exitPress = true;
            } else {
                exitButton.load("../resources/img/exit-button1.png", renderer);
            }
            exitButton.getRect()->w *= 3;
            exitButton.getRect()->h *= 3;

            ipAddress.setPosition(508, 500);
            enterButton.setPosition(575, 730);
            exitButton.setPosition(851, 730);
            break;
        case WAITING_CONNECTION:
            if (SDL_HasIntersection(mousePointer.getRect(), waitingConnectionButton.getRect())) {
                waitingConnectionPress = true;
                waitingConnectionButton.load("../resources/img/waiting-connection-button2.png", renderer);
            } else {
                waitingConnectionButton.load("../resources/img/waiting-connection-button1.png", renderer);
            }
            waitingConnectionButton.getRect()->w *= 3;
            waitingConnectionButton.getRect()->h *= 3;
            if (SDL_HasIntersection(mousePointer.getRect(), exitButton.getRect())) {
                exitButton.load("../resources/img/exit-button2.png", renderer);
                exitPress = true;
            } else {
                exitButton.load("../resources/img/exit-button1.png", renderer);
            }
            exitButton.getRect()->w *= 3;
            exitButton.getRect()->h *= 3;

            waitingConnectionButton.setPosition(422, 500);
            exitButton.setPosition(713, 670);
            break;
        case GAME_OVER:
            if (SDL_HasIntersection(mousePointer.getRect(), gameOver.getRect())) {
                gameOverPress = true;
                gameOver.load("../resources/img/game_over.png", renderer);
            } else {
                gameOver.load("../resources/img/game_over_1.png", renderer);
            }
            gameOver.getRect()->w *= 2;
            gameOver.getRect()->h *= 2;

            if (SDL_HasIntersection(mousePointer.getRect(), exitButton.getRect())) {
                exitButton.load("../resources/img/exit-button2.png", renderer);
                exitPress = true;
            } else {
                exitButton.load("../resources/img/exit-button1.png", renderer);
            }
            exitButton.getRect()->w *= 4;
            exitButton.getRect()->h *= 4;

            gameOver.setPosition(360, 200);
            exitButton.setPosition(684, 670);
            break;
        case WIN:
            if (SDL_HasIntersection(mousePointer.getRect(), win.getRect())) {
                winPress = true;
                win.load("../resources/img/you_win.png", renderer);
            } else {
                win.load("../resources/img/you_win_1.png", renderer);
            }
            win.getRect()->w *= 2;
            win.getRect()->h *= 2;

            if (SDL_HasIntersection(mousePointer.getRect(), exitButton.getRect())) {
                exitButton.load("../resources/img/exit-button2.png", renderer);
                exitPress = true;
            } else {
                exitButton.load("../resources/img/exit-button1.png", renderer);
            }
            exitButton.getRect()->w *= 4;
            exitButton.getRect()->h *= 4;

            win.setPosition(475,200);
            exitButton.setPosition(684, 670);
            break;
    }
}

void Menu::updateEvent(SDL_Event event) {
    // loop to write the ip address
    if (event.type == SDL_KEYDOWN) {
        if ((event.key.keysym.sym >= SDLK_0 && event.key.keysym.sym <= SDLK_9) || event.key.keysym.sym == SDLK_PERIOD) {
            if (position > 14) {
                position = 14;
            }
            ip_address[position] = event.key.keysym.sym;
            position++;
        }
        if (event.key.keysym.sym == SDLK_BACKSPACE) {
            position--;
            if (position < 0) {
                position = 0;
            }
            if (position == 0)
                ip_address[position] = ' ';
            else
                ip_address[position] = '\0';
        }
    }
}

void Menu::render(SDL_Renderer *renderer) {
    switch (currentMenuState) {
        case START:
            title.setPosition(188, 200);
            title.draw(renderer, NULL, 0);
            playButton.draw(renderer, NULL, 0);
            exitButton.draw(renderer, NULL, 0);
            break;
        case SERVER_CLIENT:
            title.setPosition(188, 200);
            title.draw(renderer, NULL, 0);
            serverButton.draw(renderer, NULL, 0);
            clientButton.draw(renderer, NULL, 0);
            exitButton.draw(renderer, NULL, 0);
            break;
        case IP_ADDRESS:
            title.setPosition(188, 200);
            title.draw(renderer, NULL, 0);
            ipAddress.draw(renderer, NULL, 0);
            enterButton.draw(renderer, NULL, 0);
            exitButton.draw(renderer, NULL, 0);
            display_text(renderer, ip_address, 1600/2, 620);
            break;
        case WAITING_CONNECTION:
            title.setPosition(188, 200);
            title.draw(renderer, NULL, 0);
            waitingConnectionButton.draw(renderer, NULL, 0);
            exitButton.draw(renderer, NULL, 0);
            break;
        case GAME_OVER:
            gameOver.draw(renderer, NULL, 0);
            exitButton.draw(renderer, NULL, 0);
            break;
        case WIN:
            win.draw(renderer,NULL,0);
            exitButton.draw(renderer,NULL,0);
            break;
    }
}

bool Menu::playIsPress() {
    return playPress;
}

bool Menu::exitIsPress() {
    return exitPress;
}

bool Menu::serverIsPress() {
    return serverPress;
}

bool Menu::clientIsPress() {
    return clientPress;
}

bool Menu::enterIsPress() {
    return enterPress;
}

bool Menu::waitingConnectionIsPress() {
    return waitingConnectionPress;
}

bool Menu::gameOverIsPress() {
    return gameOverPress;
}

bool Menu::winIsPress() {
    return winPress;
}

void Menu::display_text(SDL_Renderer *renderer, std::string text, int x, int y) {
    TTF_Font* minecraft_ttf = TTF_OpenFont("../resources/fonts/Minecraft.ttf", 80);
    SDL_Color White = {255, 255, 255};
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(minecraft_ttf, text.c_str(), White);
    SDL_Texture *Text = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    SDL_Rect Message_rect; //create a rect
    Message_rect.w = surfaceMessage->w; // controls the width of the rect
    Message_rect.h = surfaceMessage->h; // controls the height of the rect
    Message_rect.x = x - Message_rect.w/2;  //controls the rect's x coordinate (center text)
    Message_rect.y = y - Message_rect.h/2; // controls the rect's y coordinte (center text)
    SDL_RenderCopy(renderer, Text, NULL, &Message_rect);
    // Don't forget to free your surface and texture
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Text);
}
