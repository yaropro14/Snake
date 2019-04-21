#include <stdio.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <signal.h>
#include <fstream>
#include <unistd.h>



#include "Tui.hpp"
#include "Game.hpp"



using namespace std::placeholders;


static void sizechange(int y)
{
    View::get()->Draw();
}

void Tui::sizeofwin()
{
    struct winsize size;
    ioctl(1, TIOCGWINSZ, &size);
    x = 101;
    y = 101;
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
    
    //int x = View::get()->x;
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
    
    Gotoxy(minx()/2, miny()/2);
    
    game->paint(std::bind(&View::snakepainter, this, _1, _2), std::bind(&View::rabbitpainter, this, _1));
    
    fflush(stdout);
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
    char c;
    Draw();
    
    struct pollfd arr;
    struct timespec start_time, finish_time, worktime;
    
    
    //int x = View::get()->x;
    
    while(1)
    {
        arr.fd = 0 ;
        arr.events = POLLIN;

        clock_gettime(CLOCK_REALTIME,  &start_time);
        int n = poll(&arr, 1, (int)ontime_deligater.front().first);
        clock_gettime(CLOCK_REALTIME,  &finish_time);
        
        if(n == 1) {
            //printf("onkey\n");
            read(arr.fd, &c, 1);
            Gotoxy(minx()/2, miny()/2);
            if(c == 'q')    return;
            
            onkey_delegater->onkey(c);
        }
        
        worktime.tv_sec = finish_time.tv_sec - start_time.tv_sec;
        worktime.tv_nsec = finish_time.tv_nsec - start_time.tv_nsec;
        int d = (int)(worktime.tv_sec * 1000) + (int)(worktime.tv_nsec / 1000000);
        //ontime_deligater.front().first -= d;
        
        //printf("time = %d\n", ontime_deligater.first);
        //int i;
        //scanf("%d", &i);
        
        
        for(int i = 0; i < ontime_deligater.size(); i ++) {
            std::pair<long, timeoutable> a = ontime_deligater.front();
            ontime_deligater.pop_front();
            a.first -= d;
            ontime_deligater.push_back(a);
        }
        
        for(int i = 0; i < ontime_deligater.size(); i ++) {
            std::pair<long, timeoutable> a = ontime_deligater.front();
            ontime_deligater.pop_front();
            
            if(a.first <= 0) {
                a.second();
            }
            
            else ontime_deligater.push_back(a);
        }
        
        /*if(ontime_deligater.front().first == 500)
        {
            
        }*/
        
        
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
