#include "Game.hpp"

Game::Game()
{
    rabbits.push_back(Rabbit(20, 30));
    rabbits.push_back(Rabbit(40, 10));
    rabbits.push_back(Rabbit(80, 20));
    rabbits.push_back(Rabbit(120, 15));
}

Snake::Snake()
{
    dir = UP;
    body.push_back(Coord(10, 11));
    body.push_back(Coord(10, 12));
    body.push_back(Coord(10, 13));
    body.push_back(Coord(10, 14));
    body.push_back(Coord(10, 15));
}

void Snake::set_direction(Dir d)
{
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
    for(auto s: snakes)
        s->move();
}

void Snake::move()
{
    Coord a = body.front();
    
    switch (dir) {
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
    
    body.push_front(a);
    
    body.pop_back();
}

