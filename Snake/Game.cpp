#include "Game.hpp"
#include "View.hpp"
#include "AI.hpp"

#include <time.h>
#include <stdlib.h>

#define RAABBIT_TIME 4
#define SNAKE_TIME 400000000

using namespace std::placeholders;

Game::Game()
{
    View * v = View::get();
    struct timespec t;
    
//    Coord c(10, 20);
//    Rabbit * r = new Rabbit(c);
//    rabbits.push_back(r);
    

    for(int i = 0; i < 15; i ++) {
    rabbitgenerate();
    View::get()->ontime_deligater.pop_back();
    }
    
    t = {0, SNAKE_TIME};
    v->setontimer(t, std::bind(&Game::move, this));
    
    t = {RAABBIT_TIME, 0};
    v->setontimer(t, std::bind(&Game::rabbitgenerate, this));
    
}

Snake::Snake()
{
    alive = true;
    dir = UP;
    Coord c = Game::get()->GetFreeCoord();
    body.push_back(Coord(++c.first, c.second));
    body.push_back(Coord(++c.first, c.second));
    body.push_back(Coord(++c.first, c.second));
    //body.push_back(Coord(++c.first, c.second));
    //body.push_back(Coord(++c.first, c.second));
}

void Snake::set_direction(Dir d)
{
    if((d == LEFT || d == RIGHT) && (dir == LEFT || dir == RIGHT))  return;
    if((d == UP || d == DOWN) && (dir == UP || dir == DOWN))  return;
    dir = d;
}

void Game::paint(SnakePainter ps, RabbbitPainter pr)
{
    for(const auto s : snakes) {
        
        bool head = false;
        
        for(const auto & c : s->body) {
            ps(c, head ? BODY : s->dir);
            head = true;
        }
    }
    
    for(const auto & r : rabbits) {
        pr(r);
    }
}

Coord Game::GetFreeCoord()
{
    Coord c;
    
    while(1)
    {
        c.first = rand() % View::get()->x;
        c.second = rand() % View::get()->y;
        
        if(c.first == 0 || c.first == 1)    c.first += 5;// worktime.tv_nsec % rand() % View::get()->x;
        if(c.second == 0 || c.second == 1)   c.second += 5;// worktime.tv_nsec % View::get()->y;
        
        if(c.first == View::get()->x - 1)     c.first -= 5;
        if(c.second == View::get()->y - 1)     c.second -= 5;
        
        if(checkplace(c)) {
            return c;
    }
    }
    return c;
}


Game * Game::inst;

Game * Game::get()
{
    if(inst != nullptr)    return Game::inst;
    Game::inst = new Game;
    return Game::inst;
}


void Game::add(Snake * s)
{
    snakes.push_back(s);
}

void Game::move()
{
    bool all_die = true;
    
    for(auto s: snakes)
        if(s->alive)
        {
            all_die = false;
            break;
        }
    
    if(all_die)
    {
        View::get()->~View();
    }
    
    View::get()->AI_deligater->OnMove();
    
    for(auto s: snakes)
        if(s->alive)
            s->move();
    
    View::get()->Draw();
    
    struct timespec t;
    t = {0, SNAKE_TIME};
    View::get()->setontimer(t, std::bind(&Game::move, this));
}

void Game::rabbitgenerate()
{
    Coord c;
    srand(1);
    
    struct timespec t;
    t = {RAABBIT_TIME, 0};
    View::get()->setontimer(t, std::bind(&Game::rabbitgenerate, this));
    
    while(1) {
        
        c.first = rand() % View::get()->x;
        c.second = rand() % View::get()->y;
        
        if(c.first == 0)     c.first ++;
        if(c.second == 0)    c.second ++;
        
        if(c.first == View::get()->x - 1)     c.first --;
        if(c.second == View::get()->y - 1)     c.second --;
        
        if(checkplace(c)) {
            rabbits.push_back(c);
            return;
        }
    }
}

bool Game::checkplace(Coord c)
{
    for(const auto s : snakes)
        for(const auto & sb : s->body)
            if(c == sb) return false;
    
    for(const auto & r : rabbits)
        if(c == r) return false;
    
    if(c.first >= 0 && c.first <= 1)    return false;
    if(c.second >= 0 && c.second <= 1)   return false;
    
    if(c.first >= View::get()->x - 1)     return false;
    if(c.second >= View::get()->y - 1)     return false;
    
    return true;
}


Coord Game::near(Coord c)
{
    
    if(rabbits.size() == 0) return Coord(0, 0);
    
    Coord r(0, 0);
    int min = rabbits.front().distance(c);
    r = rabbits.front();
    
    for(auto p : rabbits)
    {
        if(min > p.distance(c)) {
            min = p.distance(c);
            r = p;
        }
    }
    return r;
}

int mod(int a)
{
    if(a > 0)   return a;
    else return -a;
}

int Coord::distance(const Coord &c) const
{
    return mod(c.first - first) + mod(c.second - second);
}


char Game::checkplacesnake(Coord c)
{
    for(const auto s : snakes)
        for(const auto & sb : s->body)
            if(c == sb)  return 's';
    
    for(const auto & r : rabbits)
        if(c == r)
        {
            //rabbits.remove(r);
            return 'r';
        }
    
    if(c.first == 1 || c.second == 1 || c.second == View::get()->x || c.second == View::get()->y) return 'b';
    
    return ' ';
}

void Game::KillRabbit(Coord c)
{
    for(const auto & r : rabbits)
        if(c == r)
        {
            rabbits.remove(r);
            return;
        }
    
//    printf("NoNONO\n");
//    int i = 0;
//    scanf("%d\n", &i);
}


void Snake::move()
{
    Coord a = body.front();
    
    a = NextPosition(dir, a);
    
    //body.push_front(a);
    switch (Game::get()->checkplacesnake(a)) {
        case ' ':
            body.push_front(a);
            body.pop_back();
            break;
            
        case 's':
            alive = false;
            //View::get()->~View();
            break;
            
        case 'b':
            alive = false;
            //View::get()->~View();
            break;
            
        case 'r':
        {
            Game::get()->KillRabbit(a);
            body.push_front(a);
            break;
        }
            
        default:
            break;
    }
}


Coord Snake::NextPosition(Dir d, Coord a)
{
    switch (d) {
        case UP:
            a.second --;
            break;
            
        case DOWN:
            a.second ++;
            break;
            
        case LEFT:
            a.first --;
            break;
            
        case RIGHT:
            a.first ++;
            break;
            
        default:
            break;
            
            
    }
    return a;
}

