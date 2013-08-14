#include "ball.h"

Ball::Ball(double x, double y, double angle, Uint32 color) :
    x(x), 
    y(y),
    angle(angle),
    kill(false),
    color(color)
{
    count++;
}

Ball::~Ball()
{
}

void Ball::update()
{
    std::cout << angle << ": (" << position.x << "," << position.y << ")" << std::endl;

    double velocity = 2;

    x = x + velocity * cos(angle * PI / 180.0);
    if (x < 0)
        angle = 180 - angle;
    else if (x + WIDTH > SCREEN_WIDTH)
        angle = 180 - angle;

    y = y - velocity * sin(angle * PI / 180.0);
    if (y < 0) 
        kill = true;

    position.x = (int) x;
    position.y = (int) y;
}
