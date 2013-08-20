#ifndef BALL_H
#define BALL_H

#include <SDL/SDL.h>
#include <cmath>

#define PI 3.14159265358979
#define WIDTH 48
//Debug
#include <iostream>

extern const int SCREEN_WIDTH;

class Ball
{
public:
    Ball(double x, double y, double angle, Uint32 color);
    virtual ~Ball();
    void update();
    bool kill;
    double x, y;
    double angle;
    Uint32 color;
    SDL_Rect position;

    static int count;

private:
};

#endif /* end of include guard: BALL_H */
