#include "View.hpp"
#include "Tui.hpp"
#include "Keypressable.hpp"
#include "Game.hpp"

View::~View(){
}

View * View::inst;

View * View::get()
{
    if(inst != nullptr)    return inst;
    
    inst = new Tui;
    return inst;
}
