#ifndef Tui_hpp
#define Tui_hpp

#include "View.hpp"
#include "Game.hpp"

#include <termios.h>


class Tui : public View
{
public:
    Tui();
    ~Tui();
    
    //Keypressable * onkey_delegater;
    
    void snakepainter(Coord c, Dir d);
    void rabbitpainter(Coord c);
    
    void Draw();
    void Run();
    void Cls();
    void Gotoxy(int r, int c);
    int minx();
    int miny();
    void sizeofwin();
    
private:
    struct termios old;
    void Xline(int y);
    void Yline(int x);
    int x, y;
};


#endif /* Tui_hpp */
