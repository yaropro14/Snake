#ifndef View_hpp
#define View_hpp

#include "Keypressable.hpp"
#include "Game.hpp"
//#include "Control.hpp"
//#include "AI.hpp"
class AI;

#include <poll.h>
#include <time.h>


using timeoutable = std::function<void()>;

class View {
public:
    Keypressable * onkey_delegater;
    std::list <std::pair < long, timeoutable>> ontime_deligater;
    AI * AI_deligater;
    
    Game * game;
    
    static View * inst;
    
    static View * get();
    
    void virtual snakepainter(Coord c, Dir d) = 0;
    void virtual rabbitpainter(Coord c) = 0;
    
    void setonkey(Keypressable * key)
    {
        onkey_delegater = key;
    }
    
    void setontimer(struct timespec timeout, timeoutable t)
    {
        std::pair <long , timeoutable> n;
        
        n.first = timeout.tv_nsec / 1000000 + timeout.tv_sec * 1000;
        n.second = t;
        
        //if(ontime_deligater.front().first >= n.first) ontime_deligater.push_front(n);
        ontime_deligater.push_back(n);
    }
    
    void setonAI(AI * ai)
    {
        AI_deligater = ai;
    }
    
    void set_model(Game * g) {
        game = g;
    }
    
    void virtual Draw() = 0;
    void virtual Run() = 0;
    
    virtual ~View() = 0;
    
    int x, y;
};


#endif /* View_hpp */

