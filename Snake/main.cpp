#include <stdio.h>

#include "View.hpp"
#include "Game.hpp"
#include "Control.hpp"
#include "ControlHuman.hpp"
#include "Tui.hpp"


int main()
{
    View * v = View::get();
    Game * g = Game::get();
    Snake s;
    ControlHuman h(&s);
    g->add(&s);
    v->set_model(g);
    v->Draw();
    v->Run();
    v->~View();
    
    return 0;
}
