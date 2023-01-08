#include "Bullet.h"
#include "Game.h"

Bullet::Bullet() {
    x_pos = 0;
    y_pos = 0;
    x_speed = 0;
    y_speed = 0;
    angle = 0;
    x_source = 0;
    y_source = 0;
    x_destination = 0;
    y_destination = 0;
    moving = false;
}

void Bullet::setXSpeed(double speed) {
    x_speed = speed;
}

void Bullet::setYSpeed(double speed) {
    y_speed = speed;
}

void Bullet::setSpeed(double speed) {
    x_speed = speed;
    y_speed = speed;
}

void Bullet::setAngle(double angle) {
    this->angle = angle;
}

void Bullet::setAngle() {
    angle = (atan2(y_destination - y_source, x_destination - x_source) * 57.2957) + 90; // arc-tan(y/x) + 90
}

double Bullet::getAngle() {
    return angle;
}

void Bullet::setSource(int x, int y) {
    if (!moving) {
        x_pos = x;
        y_pos = y;
        x_source = x;
        y_source = y;
        setPosition(x - getXCenter(), y - getYCenter());
    }
}

int Bullet::getXSource() {
    return x_source;
}

int Bullet::getYSource() {
    return y_source;
}

void Bullet::setDestination(int x, int y) {
    if(!moving) {
        x_destination = x;
        y_destination = y;
    }
}

int Bullet::getXDestination() {
    return x_destination;
}

int Bullet::getYDestination() {
    return y_destination;
}

void Bullet::setMoving(bool is_moving) {
    this->moving = is_moving;
}

bool Bullet::isMoving() {
    return moving;
}

void Bullet::updateXPos(double x) {
    x_pos += x;
}

void Bullet::updateYPos(double y) {
    y_pos += y;
}

void Bullet::move() { // aggiungere sicurezza sui bordi
    // detect if it is moving, if yes calculate the next position, if not destroy it
    if (moving) {
        updateXPos(x_speed*1.0/Game::FPS);
        updateYPos(y_speed*1.0/Game::FPS);
    } else {
        destroy();
    }
    setPosition(round(x_pos - getRect()->w/2), round(y_pos - getRect()->h/2)); // translate the center
    // detect if it has arrived at destination
    int distance, distance_travelled;
    if (x_destination != -1 && y_destination != -1) {
        distance = pow(x_destination - x_source, 2) + pow(y_destination - y_source, 2);
        distance_travelled = pow(x_pos - x_source, 2) + pow(y_pos - y_source, 2);
        if (distance_travelled > distance) {
            moving = false;
        }
    } else if (x_pos > 1600 || x_pos < 0 || y_pos > 1000 || y_pos < 0) {
        moving = false;
    }

}

void Bullet::destroy() {
    moving = false;
    Picture::destroy();
}