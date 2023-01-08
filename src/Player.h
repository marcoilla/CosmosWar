#ifndef ARCADE_GAME_PLAYER_H
#define ARCADE_GAME_PLAYER_H

#include "include.h"
#include "Picture.h"
#include "Bullet.h"
#include "SoundMixer.h"

class Player : public Picture {
public:
    // constructor
    Player();
    // getter and setter
    int getId();
    void setId(int id);
    int getXPos();
    int getYPos();
    void setXPos(double x);
    void setYPos(double y);
    void setPosition(double x, double y);
    void setAngle(double angle);
    void setAngle(int y, int x);
    double getAngle();
    int* getData();
    Bullet* getBullets();
    int getBullet();
    int getLife();
    int getUp();
    int getDown();
    int getLeft();
    int getRight();
    int getBulletsSize();
    void updateXPos(double x);
    void updateYPos(double y);
    //void setSource(int x,int y);
    // methods
    /*enum StateType {
        Normal=1,
        Pause=2
    };*/
    bool loadPicture(const char *file, SDL_Renderer *renderer);
    void drawFrame(SDL_Renderer *renderer);
    void setClip();
    //SDL_Rect getHitBox();
    void handleInput(SDL_Event input, int mouse_x, int mouse_y, SDL_Renderer *renderer, SoundMixer &soundMixer);
    void move(SoundMixer &soundMixer);
    void shot(int x, int y, SDL_Renderer *renderer);
    void handleBullets(SDL_Renderer *renderer);
    void hit(SDL_Renderer *renderer);
    void reset();
private:
    // attributes
    static const int frame_rate = 8;
    static const int bullets_size = 5;
    // identifier
    int id;
    // position
    double x_pos;
    double y_pos;
    // frame information
    int frame;
    int width_frame;
    int height_frame;
    SDL_Rect frame_clip[frame_rate];
    // bullets
    int bullet_c;
    Bullet bullets[bullets_size];
    // life points
    int life;
    // angle of movement
    double angle;
    // movement status
    int up, down, left, right;
    // data of players to send/recv
    int data[4];
};

#endif //ARCADE_GAME_PLAYER_H
