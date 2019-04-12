#ifndef Model_hpp
#define Model_hpp

#include <stdio.h>
#include <iostream>
#include <list>

//#include "ControlHuman.hpp"

using Coord = std::pair <int, int>;
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
    
    void move();
    
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
};


#endif /* Model_hpp */ 
