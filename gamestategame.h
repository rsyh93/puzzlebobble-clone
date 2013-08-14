#ifndef GAMESTATEGAME_H
#define GAMESTATEGAME_H

#include <SDL/SDL.h>
#include <SDL/SDL_rotozoom.h>
#include <vector>

#include "gamestate.h"
#include "ball.h"

// Debug
#include <iostream>

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern const int SCREEN_BPP;

extern SDL_Surface *screen;
extern SDL_Surface *arrow_img;
extern SDL_Surface *ball_img;
extern bool running;

static const int top_row_size = 10;

struct Arrow
{
    int center_x, center_y;
    double angle;
    SDL_Surface *image;
    void adjustedPosition(int *dst_x, int *dst_y);
};

//struct Ball
//{
//    SDL_Rect position;
//}

class GamestateGame : public Gamestate
{
public:
    GamestateGame();
    virtual ~GamestateGame();

    void init();
    void events();
    void draw();
    void close();

private:
    bool keyPress(SDLKey key);
    void updateArrow();
    void updateBalls();
    Ball *top_row[top_row_size];
    Ball *active_ball;
    std::vector<SDL_Surface *> arrow_angles;
    SDL_Rect playarea;
    Arrow arrow;
    Uint8 *old_keystate;
    Uint8 *cur_keystate;
};



#endif /* end of include guard: GAMESTATEGAME_H */
