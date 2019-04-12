#include "Control.hpp"


Control::Control(Snake * s)
{
    View * v = View::get();
    v->setonkey(this);
    snake = s;
}

Control::~Control()
{
}
