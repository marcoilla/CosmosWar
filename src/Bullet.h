#ifndef ARCADE_GAME_BULLET_H
#define ARCADE_GAME_BULLET_H

#include "include.h"
#include "Picture.h"

class Bullet : public Picture {
public:
    // constructor
    Bullet();
    // getter and setter
    void setXSpeed(double speed);
    void setYSpeed(double speed);
    void setSpeed(double speed);
    void setAngle(double angle);
    void setAngle();
    double getAngle();
    void setSource(int x,int y);
    int getXSource();
    int getYSource();
    void setDestination(int x,int y);
    int getXDestination();
    int getYDestination();
    void setMoving(bool is_moving);
    bool isMoving();
    // methods
    void move();
    // destructor
    void destroy();

private:
    // attributes
    // position
    double x_pos;
    double y_pos;
    // speed (pixels per second)
    double x_speed;
    double y_speed;
    // angle of movement
    double angle;
    // source position
    int x_source;
    int y_source;
    // destination position
    int x_destination;
    int y_destination;
    // state of movement
    bool moving;
    // methods
    void updateXPos(double x);
    void updateYPos(double y);
};


#endif //ARCADE_GAME_BULLET_H
