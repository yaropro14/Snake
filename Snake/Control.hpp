#ifndef Control_hpp
#define Control_hpp

#include <stdio.h>

#include "Game.hpp"
#include "View.hpp"

class Control: public Keypressable
{
public:
    Control(Snake * s);
    ~Control();
    
    Snake * snake;
};


#endif /* Control_hpp */
