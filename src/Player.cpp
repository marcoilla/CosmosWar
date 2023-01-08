#include "Player.h"
#include "Game.h"

Player::Player() {
    id = 0;
    x_pos = 0;
    y_pos = 0;
    frame = 0;
    width_frame = 0;
    height_frame = 0;
    life = 3;
    angle = 90;
    bullet_c = 0;
    up = 0;
    down = 0;
    left = 0;
    right = 0;
    data[0] = 0;
    data[1] = 0;
    data[2] = 0;
    data[3] = 0;
}

int Player::getId() {
    return id;
}

void Player::setId(int id) {
    this->id = id;
    data[0] = id;
}

int Player::getXPos() {
    return x_pos;
}

int Player::getYPos() {
    return y_pos;
}

void Player::setXPos(double x) {
    x_pos = x;
}

void Player::setYPos(double y) {
    y_pos = y;
}

void Player::setPosition(double x, double y) {
    x_pos = x;
    y_pos = y;
    Picture::setPosition(x - width_frame/2, y - height_frame/2);
}

void Player::setAngle(double angle) {
    this->angle = angle;
}

void Player::setAngle(int y, int x) {
    angle = (atan2(y - (getY() + getYCenter()), x - (getX() + getXCenter()))*57.2957) + 90; // arc-tan(y/x) + 90
    data[2] = x;
    data[3] = y;
}

double Player::getAngle() {
    return angle;
}

int* Player::getData() {
    return data;
}

Bullet* Player::getBullets() {
    return bullets;
}

int Player::getBullet() {
    return bullet_c;
}

int Player::getLife() {
    return life;
}

int Player::getUp() {
    return up;
}

int Player::getDown() {
    return down;
}

int Player::getLeft() {
    return left;
}

int Player::getRight() {
    return right;
}

int Player::getBulletsSize() {
    return bullets_size;
}

void Player::updateXPos(double x) {
    x_pos += x;
}

void Player::updateYPos(double y) {
    y_pos += y;;
}

bool Player::loadPicture(const char *file, SDL_Renderer *renderer) {
    if (!load(file, renderer)) {
        return false;
    }
    width_frame = getRect()->w/frame_rate;
    height_frame = getRect()->h;
    return true;
}

void Player::setClip() {
    if (width_frame>0 && height_frame>0) {
        for (int i = 0; i < frame_rate; ++i) {
            frame_clip[i].x = 0 + i*(width_frame);
            frame_clip[i].y = 0;
            frame_clip[i].w = width_frame;
            frame_clip[i].h = height_frame;
        }
    }
    setRect({getRect()->x, getRect()->y, width_frame, height_frame});
}

void Player::drawFrame(SDL_Renderer *renderer) {
    if (life > 0)
        draw(renderer, &frame_clip[frame], getAngle());
}

void Player::handleInput(SDL_Event input, int mouse_x, int mouse_y, SDL_Renderer *renderer, SoundMixer &soundMixer) {
    if (life > 0) {
        if (input.type == SDL_KEYDOWN) {
            switch (input.key.keysym.scancode) {
                case SDL_SCANCODE_W:
                    up = 1;
                    if (frame == frame_rate - 1)
                        frame = 1;
                    else
                        frame++;
                    break;
                case SDL_SCANCODE_A:
                    left = 1;
                    if (frame == frame_rate - 1)
                        frame = 1;
                    else
                        frame++;
                    break;
                case SDL_SCANCODE_S:
                    down = 1;
                    if (frame == frame_rate - 1)
                        frame = 1;
                    else
                        frame++;
                    break;
                case SDL_SCANCODE_D:
                    right = 1;
                    if (frame == frame_rate - 1)
                        frame = 1;
                    else
                        frame++;
                    break;
            }
        } else if (input.type == SDL_KEYUP) {
            switch (input.key.keysym.scancode) {
                case SDL_SCANCODE_W:
                    up = 0;
                    frame = 0;
                    break;
                case SDL_SCANCODE_A:
                    left = 0;
                    frame = 0;
                    break;
                case SDL_SCANCODE_S:
                    down = 0;
                    frame = 0;
                    break;
                case SDL_SCANCODE_D:
                    right = 0;
                    frame = 0;
                    break;
            }
        } else if (input.type == SDL_MOUSEBUTTONDOWN) {
            if(input.button.button == SDL_BUTTON_LEFT) {
                shot(mouse_x, mouse_y, renderer);
                soundMixer.playSoundShot();
            }
        }
        data[1] = event_to_int(input);
    } else {
        data[1] = 0;
    }
}

void Player::move(SoundMixer &soundMixer) {
    if (life > 0) {
        updateXPos(300.0*cos((getAngle() - 90)*M_PI/180)*1.0/Game::FPS*up);
        updateYPos(300.0*sin((getAngle() - 90)*M_PI/180)*1.0/Game::FPS*up);
        updateXPos(300.0*cos((getAngle() + 180)*M_PI/180)*1.0/Game::FPS*left);
        updateYPos(300.0*sin((getAngle() + 180)*M_PI/180)*1.0/Game::FPS*left);
        updateXPos(300.0*cos((getAngle() + 90)*M_PI/180)*1.0/Game::FPS*down);
        updateYPos(300.0*sin((getAngle() + 90)*M_PI/180)*1.0/Game::FPS*down);
        updateXPos(300.0*cos(getAngle()*M_PI/180)*1.0/Game::FPS*right);
        updateYPos(300.0*sin(getAngle()*M_PI/180)*1.0/Game::FPS*right);
        setPosition(x_pos, y_pos); // translate the center
        if (x_pos > 1600 || x_pos < 0 || y_pos > 1000 || y_pos < 0) {
            // bounce back
            updateXPos(-300.0*cos((getAngle() - 90)*M_PI/180)*1.0/Game::FPS*up);
            updateYPos(-300.0*sin((getAngle() - 90)*M_PI/180)*1.0/Game::FPS*up);
            updateXPos(-300.0*cos((getAngle() + 180)*M_PI/180)*1.0/Game::FPS*left);
            updateYPos(-300.0*sin((getAngle() + 180)*M_PI/180)*1.0/Game::FPS*left);
            updateXPos(-300.0*cos((getAngle() + 90)*M_PI/180)*1.0/Game::FPS*down);
            updateYPos(-300.0*sin((getAngle() + 90)*M_PI/180)*1.0/Game::FPS*down);
            updateXPos(-300.0*cos(getAngle()*M_PI/180)*1.0/Game::FPS*right);
            updateYPos(-300.0*sin(getAngle()*M_PI/180)*1.0/Game::FPS*right);
            soundMixer.playSoundCollision();
        }
    }
}

void Player::shot(int x, int y, SDL_Renderer *renderer) {
    Bullet *bullet = &bullets[bullet_c];
    if (id == 0)
        bullet->load("../resources/img/bullet0.png", renderer);
    else
        bullet->load("../resources/img/bullet1.png", renderer);
    bullet->setSource(getXCenter() + getX(), getYCenter() + getY());
    bullet->setDestination(x, y);
    bullet->setAngle();
    bullet->setXSpeed(1000.0*cos(((bullet->getAngle() - 90)*M_PI)/180));
    bullet->setYSpeed(1000.0*sin(((bullet->getAngle() - 90)*M_PI)/180));
    bullet->setMoving(true);
}

void Player::handleBullets(SDL_Renderer *renderer) {
    if (life > 0) {
        // shot bullets
        for (int i = 0; i < bullets_size; ++i) {
            bullets[i].move();
            bullets[i].draw(renderer, NULL, bullets[i].getAngle());
            if(bullets[i].getTexture() == NULL) {
                bullet_c = i;
            }
        }
    } else {
        // shot particles
        for (int i = 0; i < bullets_size; ++i) {
            bullets[i].move();
            bullets[i].draw(renderer, NULL, bullets[i].getAngle());
        }
    }

}

void Player::hit(SDL_Renderer *renderer) {
    if (life > 0)
        life--;
    if (life == 0) {
        for(int i = 0; i < 5; i++) {
            if (id == 0)
                bullets[i].load("../resources/img/particle0.png", renderer);
            else
                bullets[i].load("../resources/img/particle1.png", renderer);
            bullets[i].setSource(getXCenter() + getX(), getYCenter() + getY());
            bullets[i].setDestination(-1, -1);
            bullets[i].setXSpeed(500.0*cos(72*i*M_PI/180));
            bullets[i].setYSpeed(500.0*sin(72*i*M_PI/180));
            bullets[i].setMoving(true);
        }
        destroy();
    }

}

void Player::reset() {
    id = 0;
    x_pos = 0;
    y_pos = 0;
    frame = 0;
    life = 3;
    angle = 90;
    bullet_c = 0;
    up = 0;
    down = 0;
    left = 0;
    right = 0;
    data[0] = 0;
    data[1] = 0;
    data[2] = 0;
    data[3] = 0;
    for (int i = 0; i < 5; ++i) {
        bullets[i].setMoving(false);
        bullets[i].destroy();
    }
}