#include <stdio.h>

#include "View.hpp"
#include "Game.hpp"
#include "Control.hpp"
#include "ControlHuman.hpp"
#include "Tui.hpp"
#include "AI.hpp"


int main()
{
    srand(time(NULL));
    View * v = View::get();
    Game * g = Game::get();
    Snake s;
    ControlHuman h(&s);
    Snake * s2 = new Snake();
    AI ai(s2);
    
    g->add(&s);
    g->add(s2);
//    g->rabbits.back().first = s2->body.front().first + 1;
//    g->rabbits.back().second = s2->body.front().second;
    v->set_model(g);
    v->Draw();
    v->Run();
    v->~View();
    
    return 0;
}
