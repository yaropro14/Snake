#ifndef View_hpp
#define View_hpp

#include "Keypressable.hpp"
#include "Game.hpp"


class View {
public:
    Keypressable * onkey_delegater;
    Game * game;
    
    static View * inst;
    
    static View * get();
    
    void virtual snakepainter(Coord c, Dir d) = 0;
    void virtual rabbitpainter(Coord c) = 0;
    
    void setonkey(Keypressable * key)
    {
        onkey_delegater = key;
    }
    
    void set_model(Game * g) {
        game = g;
    }
    
    void virtual Draw() = 0;
    void virtual Run() = 0;
    
    virtual ~View() = 0;
};


#endif /* View_hpp */

