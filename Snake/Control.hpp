#ifndef Control_hpp
#define Control_hpp

#include <stdio.h>

//#include "Game.hpp"
//#include "View.hpp"
class Snake;

class Control
{
public:
    Control(Snake * s);
    ~Control();
    
    Snake * snake;
};


#endif /* Control_hpp */
