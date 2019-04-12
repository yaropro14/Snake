#include <stdio.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <signal.h>
#include <fstream>


#include "Tui.hpp"
#include "Game.hpp"

using namespace std::placeholders;


static void sizechange(int y)
{
    View * v = View::get();
    v->Draw();
}

void Tui::sizeofwin()
{
    struct winsize size;
    ioctl(1, TIOCGWINSZ, &size);
    x = size.ws_col;
    y = size.ws_row;
    
}


Tui::Tui()
{
    sizeofwin();
    struct sigaction sa = {0};
    sa.sa_handler = sizechange;
    sa.sa_flags = SA_RESTART;
    sigaction(SIGWINCH, &sa, 0);
    struct termios a;
    tcgetattr(0, &a);
    old = a;
    cfmakeraw(&a);
    tcsetattr(0, TCSAFLUSH, &a);
}


Tui::~Tui()
{
    tcgetattr(TCSAFLUSH, &old);
    Cls();
    printf("Good bye\n");
}


void Tui::Draw()
{
    sizeofwin();
    
    Cls();
    
    Xline(0);
    Xline(miny());
    
    Yline(0);
    Yline(minx());
    
    fflush(stdout);
    Gotoxy(minx()/2, miny()/2);
    
    game->paint(std::bind(&View::snakepainter, this, _1, _2), std::bind(&View::rabbitpainter, this, _1));
}

void Tui::snakepainter(Coord c, Dir d)
{
    Gotoxy(c.first, c.second);
    putchar("^V><*"[d]);
}

void Tui::rabbitpainter(Coord c)
{
    Gotoxy(c.first, c.second);
    std::cout<<"r";
}


void Tui::Xline(int y)
{
    //Gotoxy(0, y);
    for (int i = 0; i < minx(); i ++)
    {
        Gotoxy(i, y);
        printf("#");
    }
}


void Tui::Yline(int x)
{
    for (int i = 1; i <= miny(); i ++)
    {
        Gotoxy(x, i);
        printf("#");
    }
        
}


void Tui::Cls()
{
    printf("\e[H\e[J");
}


void Tui::Gotoxy(int r, int c)
{
    printf("\e[%d;%dH", c, r);
}


void Tui::Run()
{
    //printf("Hello, world. Snake\n");
    char c = getchar();
    Draw();
    
    while(1)
    {
        Gotoxy(minx()/2, miny()/2);
        if(c == 'q')    return;
        onkey_delegater->onkey(c);
        Draw();
        c = getchar();
    }
    
}


int Tui::minx()
{
    return x;
}


int Tui::miny()
{
    return y;
}
