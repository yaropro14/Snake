#ifndef Model_hpp
#define Model_hpp

#include <stdio.h>
#include <iostream>
#include <list>
#include <cstdlib>


//#include "ControlHuman.hpp"

//using Coord = std::pair <int, int>;
//using Rabbit = Coord;

struct Coord : public std::pair<int, int>
{
    using Base = std::pair<int, int>;
    int distance(const Coord & c) const;
    using Base::Base;
};

using Rabbit = Coord;


enum Dir
{
    UP,
    DOWN,
    RIGHT,
    LEFT,
    BODY,
    NO
    
};

using SnakePainter = std::function<void(Coord, Dir)>;
using RabbbitPainter = std::function<void(Coord)>;

class Snake {
public:
    Snake();
    
    bool alive;
    
    void move();
    
    Coord NextPosition(Dir d, Coord a);
    
    Snake(const Snake & s):
    dir(s.dir), body(s.body)
    {}
    
    Snake & operator = (const Snake & s){
        dir = s.dir;
        body = s.body;
        return * this;
    }
    
    std::list <Coord> body;
    void set_direction(Dir d);
    Dir dir;
};


class Game {
protected:
    Game();
    
public:
    static Game * inst;
    
    void move();
    
    static Game * get();
    
    std::list <Snake *> snakes;
    std::list <Rabbit> rabbits;
    
    void paint(SnakePainter ps, RabbbitPainter pr);
    void add(Snake * s);
    void rabbitgenerate();
    bool checkplace(Coord c);
    char checkplacesnake(Coord c);
    Coord near(Coord c);
    Coord GetFreeCoord();
    void KillRabbit(Coord c);
};


#endif /* Model_hpp */ 
