#include "gamestategame.h"
#include <cstring>

void Arrow::adjustedPosition(int *dst_x, int *dst_y)
{
    int w = this->image->w;
    int h = this->image->h;

    *dst_x = this->center_x - w / 2;
    *dst_y = this->center_y - h / 2;
}

GamestateGame::GamestateGame() :
    active_ball(NULL)
{
    for (int i = 0; i < top_row_size; i++)
    {
        top_row[i] = NULL;
    }

    old_keystate = NULL;
    cur_keystate = NULL;
}

GamestateGame::~GamestateGame()
{
}

void GamestateGame::init()
{
    for (int i = 90; i <= 270; i+=5) 
    {
        SDL_Surface *tmp = rotozoomSurface(arrow_img, i, 1, SMOOTHING_ON);
        arrow_angles.push_back(tmp);
    }

    playarea.x = 0;
    playarea.y = 0;
    playarea.w = SCREEN_WIDTH;
    playarea.h = SCREEN_HEIGHT;

    arrow.center_x = playarea.x + playarea.w / 2;
    arrow.center_y = playarea.y + playarea.h - 10;
    arrow.angle = 90;
    arrow.image = arrow_angles[static_cast<int>(arrow.angle/5)];
}

void GamestateGame::events()
{
    SDL_PumpEvents();
    int numkeys = 0;
    cur_keystate = SDL_GetKeyState(&numkeys);

    if (cur_keystate[SDLK_q] || cur_keystate[SDLK_ESCAPE])
        running = false;

    if (cur_keystate[SDLK_LEFT])
        arrow.angle += 1;
    else if (cur_keystate[SDLK_RIGHT])
        arrow.angle -= 1;

    if (keyPress(SDLK_SPACE))
        std::cout << arrow.angle << std::endl;

    updateArrow();

    if (keyPress(SDLK_RETURN) && active_ball == NULL)
        active_ball = new Ball(arrow.center_x - ball_img->w / 2,
                               arrow.center_y - ball_img->h / 2,
                               arrow.angle,
                               SDL_MapRGB(screen->format, 255, 0, 0)
                              );

    updateBalls();
    
    if (old_keystate != NULL)
        delete[] old_keystate;
    old_keystate = new Uint8[numkeys];
    memcpy((void *)old_keystate, (const void *)cur_keystate, numkeys);
}

void GamestateGame::draw()
{
    SDL_FillRect(screen, NULL, 0x0);
    SDL_FillRect(screen, &playarea, 0xffffff);
    SDL_Rect arrow_dest;
    int x, y;
    arrow.adjustedPosition(&x, &y);
    arrow_dest.x = x;
    arrow_dest.y = y;
    SDL_BlitSurface(arrow.image, NULL, screen, &arrow_dest);
    for (int i = 0; i < top_row_size; i++)
    {
        if (top_row[i] != NULL)
        {
            SDL_SetColorKey(ball_img, SDL_SRCCOLORKEY, top_row[i]->color);
            SDL_BlitSurface(ball_img, NULL, screen, &top_row[i]->position);
        }
    }
    if (active_ball != NULL)
    {
        SDL_SetColorKey(ball_img, SDL_SRCCOLORKEY, active_ball->color);
        SDL_BlitSurface(ball_img, NULL, screen, &active_ball->position);
    }
}

void GamestateGame::close()
{
    for (int i = 0; i < top_row_size; i++)
    {
        if (top_row[i] != NULL)
            delete top_row[i];
    }

    delete active_ball;

    for (std::vector<SDL_Surface *>::iterator it = arrow_angles.begin();
            it != arrow_angles.end();
            ++it)
    {
        delete *it;
    }
    arrow_angles.clear();
}

bool GamestateGame::keyPress(SDLKey key)
{
    if (old_keystate != NULL && cur_keystate != NULL)
        return old_keystate[key] && !cur_keystate[key];
    return false;
}

void GamestateGame::updateArrow()
{
    if (arrow.angle < 20)
        arrow.angle = 20;
    else if (arrow.angle > 160)
        arrow.angle = 160;

    arrow.image = arrow_angles[static_cast<int>(arrow.angle/5)];
}

void GamestateGame::updateBalls()
{
    for (int i = 0; i < top_row_size; i++)
    {
        if (top_row[i] != NULL)
        {
            if (top_row[i]->kill)
            {
                delete top_row[i];
                top_row[i] = NULL;
            }
        }
    }

    if (active_ball != NULL)
    {
        active_ball->update();
        if (active_ball->y <= 0)
        {
            int position = (int)(active_ball->x/48);

            if (top_row[position] == NULL)
            {
                // Debug
                std::cout << "Placing x=" << active_ball->x << " to position " << position <<std::endl;
            
                active_ball->x = position * 48;
                active_ball->y = 0;
                active_ball->position.x = position * 48;
                active_ball->position.y = 0;
                top_row[position] = active_ball;
            }
            else
            {
                delete active_ball;
            }

            active_ball = NULL;
        }
    }

}

