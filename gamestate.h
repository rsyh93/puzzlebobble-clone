#ifndef GAMESTATE_H
#define GAMESTATE_H

class Gamestate {
public:
    Gamestate();
    virtual ~Gamestate();

    virtual void init();
    virtual void events();
    virtual void draw();
    virtual void close();

private:
   
};

#endif /* end of include guard: GAMESTATE_H */
