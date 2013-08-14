#ifndef GAMESTATEMENU_H
#define GAMESTATEMENU_H

#include "gamestate.h"

class GamestateMenu : public Gamestate
{
public:
    GamestateMenu ();
    virtual ~GamestateMenu ();

    void init();
    void events();
    void draw();
    void close();

private:
};

#endif /* end of include guard: GAMESTATEMENU_H */
