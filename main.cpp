#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "gamestatemenu.h"
#include "gamestategame.h"

const int SCREEN_WIDTH = 480;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

SDL_Surface *screen;
SDL_Surface *arrow_img;
SDL_Surface *ball_img;
Gamestate *state;
bool running;

SDL_Surface *load_image(const char* filename)
{
    SDL_Surface* tmp = IMG_Load(filename);
    if (tmp == NULL)
    {
        printf("Unable to load image \"%s\": %s", filename, SDL_GetError());
        return NULL;
    }

    SDL_Surface *optimized = SDL_DisplayFormatAlpha(tmp);
    if (optimized == NULL)
    {
        printf("Unable to optimize image \"%s\": %s", filename, SDL_GetError());
        return NULL;
    }
    SDL_FreeSurface(tmp);
    return optimized;
}

bool init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        return false;
    }
    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_DOUBLEBUF);
    if (screen == NULL)
    {
        return false;
    }

    return true;
}

bool load_resources()
{
    state = new GamestateGame();
    arrow_img = load_image("down_arrow.png");
    if (arrow_img == NULL)
        return false;
    
    ball_img = load_image("black_ball.png");
    if (ball_img == NULL)
        return false;

    return true;
}

void quit()
{
    delete state;
    SDL_Quit();
}

int main(int argc, char** argv)
{
    if (!init())
    {
        return -1;
    }
    if (!load_resources())
    {
        return -1;
    }

    Uint32 start;
    Uint32 diff;
    double ms_per_frame = 1000/100.0;

    running = true;
    state->init();
    while (running)
    {
        start = SDL_GetTicks();
        state->events();
        state->draw();
        SDL_Flip(screen);
        diff = SDL_GetTicks() - start;
        if (diff < ms_per_frame)
            SDL_Delay(ms_per_frame - diff);
    }
    state->close();

    quit();
}
