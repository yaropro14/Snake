#ifndef ControlHuman_hpp
#define ControlHuman_hpp

#include <stdio.h>
#include "Game.hpp"
#include "Control.hpp"
#include "Keypressable.hpp"


class ControlHuman : public Control, public Keypressable
{
public:
    ControlHuman(Snake * s);
    ~ControlHuman();
    void onkey(char key);
};

#endif /* ControlHuman_hpp */
