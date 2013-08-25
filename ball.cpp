#include "ball.h"

int Ball::count = 0;

Ball::Ball(double x, double y, double angle, Uint32 color) :
    x(x), 
    y(y),
    angle(angle),
    kill(false),
    color(color),
    top_left(NULL),
    top_right(NULL),
    left(NULL),
    right(NULL),
    bot_left(NULL),
    bot_right(NULL)
{
    count++;
}

Ball::~Ball()
{
}

/**
 * Checks if the current Ball collides with the Ball provided in parameter
 * Returns Direction.NONE if not colliding
 * Returns the corresponding Direction if colliding
 * Does not modify either Ball's state
 */
Direction Ball::collide(Ball &other)
{
    double cx = x + BALL_WIDTH / 2;
    double cy = y + BALL_HEIGHT / 2;
    
    double other_cx = other.x + BALL_WIDTH / 2;
    double other_cy = other.y + BALL_HEIGHT / 2;
        
    double radius = BALL_WIDTH / 2;
    double distance = sqrt((other_cx - cx) * (other_cx - cx) + (other_cy - cy) * (other_cy - cy));

    if (distance < BALL_WIDTH)
    {
        bool left = false;
        if (cx < other_cx)
            left = true;

        int ydir; // -1 for TOP, 1 for BOT, 0 otherwise
        double yoffset = cy - other_cy;

        if (yoffset < -distance / 2) // Equilateral triangle magic!!!
            ydir = -1;
        else if (yoffset > distance / 2)
            ydir = 1;
        else
            ydir = 0;

        if (left)
        {
            if (ydir < 0)
                return TOPLEFT;
            else if (ydir > 0)
                return BOTLEFT;
            else
                return LEFT;
        }
        else
        {
            if (ydir < 0)
                return TOPRIGHT;
            else if (ydir > 0)
                return BOTRIGHT;
            else
                return RIGHT;
        }

    }
    return NONE;
}

void Ball::move()
{
    // Debug
    std::cout << angle << ": (" << position.x << "," << position.y << ")" << std::endl;

    double velocity = 2;

    x = x + velocity * cos(angle * PI / 180.0);
    if (x < 0)
        angle = 180 - angle;
    else if (x + BALL_WIDTH > SCREEN_WIDTH)
        angle = 180 - angle;

    y = y - velocity * sin(angle * PI / 180.0);

}

void Ball::update()
{
    position.x = (int) x;
    position.y = (int) y;
}

void Ball::assign(Ball& attached, Direction dir)
{
    switch(dir)
    {
        case TOPLEFT:
            assign_tl(&attached);
            break;
        case TOPRIGHT:
            assign_tr(&attached);
            break;
        case LEFT:
            assign_l(&attached);
            break;
        case RIGHT:
            assign_r(&attached);
            break;
        case BOTLEFT:
            assign_bl(&attached);
            break;
        case BOTRIGHT:
            assign_br(&attached);
            break;
    }
}

void Ball::assign_tl(Ball *attached)
{
    top_left = attached;
    if (attached->right != NULL)
    {
        top_right = attached->right;
        if (top_right->bot_right != NULL)
        {
            right = top_right->bot_right;
        }
    }
    if (attached->bot_left != NULL)
    {
        left = attached->bot_left;
        if (left->bot_right != NULL)
        {
            bot_left = left->bot_right;
        }
    }
}

void Ball::assign_tr(Ball *attached)
{
    top_right = attached;
    if (attached->left != NULL)
    {
        top_left = attached->left;
        if (top_left->bot_left != NULL)
        {
            left = top_left->bot_left;
        }
    }
    if (attached->bot_right != NULL)
    {
        right = attached->bot_right;
        if (right->bot_left != NULL)
        {
            bot_right = left->bot_left;
        }
    }
}

void Ball::assign_l(Ball *attached)
{
    left = attached;
    if (attached->top_right != NULL)
    {
        top_left = attached->top_right;
        if (top_left->right != NULL)
        {
            top_right = top_left->right;
        }
    }
    if (attached->bot_right != NULL)
    {
        bot_left = attached->bot_right;
        if (bot_left->right != NULL)
        {
            bot_right = bot_left->right;
        }
    }
}

void Ball::assign_r(Ball *attached)
{
    right = attached;
    if (attached->top_left != NULL)
    {
        top_right = attached->top_left;
        if (top_right->left != NULL)
        {
            top_left = top_right->left;
        }
    }
    if (attached->bot_left != NULL)
    {
        bot_right = attached->bot_left;
        if (bot_right->left != NULL)
        {
            bot_left = bot_right->left;
        }
    }
}

void Ball::assign_bl(Ball *attached)
{
    bot_left = attached;
    if (attached->top_left != NULL)
    {
        left = attached->top_left;
        if (left->top_right != NULL)
        {
            top_left = left->top_right;
        }
    }
    if (attached->right != NULL)
    {
        bot_right = attached->right;
        if (bot_right->top_right != NULL)
        {
            right = bot_right->top_right;
        }
    }
}

void Ball::assign_br(Ball *attached)
{
    bot_right = attached;
    if (attached->top_right != NULL)
    {
        right = attached->top_right;
        if (right->top_left != NULL)
        {
            top_right = right->top_left;
        }
    }
    if (attached->left != NULL)
    {
        bot_left = attached->left;
        if (bot_left->top_left != NULL)
        {
            left = bot_left->top_left;
        }
    }
}

