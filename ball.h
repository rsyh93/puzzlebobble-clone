#ifndef BALL_H
#define BALL_H

#include <SDL/SDL.h>
#include <cmath>

#define PI 3.14159265358979
#define BALL_WIDTH 48
#define BALL_HEIGHT 48
//Debug
#include <iostream>

extern const int SCREEN_WIDTH;

enum Direction
{
    TOPLEFT,
    TOPRIGHT,
    LEFT,
    RIGHT,
    BOTLEFT,
    BOTRIGHT,
    NONE
};

class Ball
{
public:
    Ball(double x, double y, double angle, Uint32 color);
    virtual ~Ball();
    Direction collide(Ball &other);
    void assign(Ball& attached, Direction dir);
    void move();
    void update();
    bool kill;
    double x, y;
    double angle;
    Uint32 color;
    SDL_Rect position;

    static int count;
    Ball *top_left, *top_right, *left, *right, *bot_left, *bot_right;

private:
    void assign_tl(Ball* attached);
    void assign_tr(Ball* attached);
    void assign_l(Ball* attached);
    void assign_r(Ball* attached);
    void assign_bl(Ball* attached);
    void assign_br(Ball* attached);
};

#endif /* end of include guard: BALL_H */
