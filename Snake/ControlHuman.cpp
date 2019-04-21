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
    //Game * g = Game::get();
    
    switch (key) {
        case 'a':
            if(snake->dir == LEFT)  break;
            snake->set_direction(LEFT);
            break;
            
        case 'd':
            if(snake->dir == RIGHT)  break;
            snake->set_direction(RIGHT);
            break;
            
        case 'w':
            if(snake->dir == UP)  break;
            snake->set_direction(UP);
            break;
            
        case 's':
            if(snake->dir == DOWN)  break;
            snake->set_direction(DOWN);
            break;
            
        default:
            break;
    }
}
