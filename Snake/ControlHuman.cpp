#include "ControlHuman.hpp"
#include "View.hpp"
#include <stdio.h>


ControlHuman::ControlHuman(Snake * s):Control(s)
{
    View * v = View::get();
    v->setonkey(this);
}


ControlHuman::~ControlHuman()
{
}


void ControlHuman::onkey(char key)
{
    Game * g = Game::get();
    
    switch (key) {
        case 'a':
            snake->set_direction(LEFT);
            break;
            
        case 'd':
            snake->set_direction(RIGHT);
            break;
            
        case 'w':
            snake->set_direction(UP);
            break;
            
        case 's':
            snake->set_direction(DOWN);
            break;
            
        default:
            break;
    }
    
    g->move();
    
            
    View * v = View::get();
    v->Draw();
}
