//
//  AI.cpp
//  Snake
//
//  Created by Yaroslav on 19/04/2019.
//  Copyright © 2019 Yaroslav. All rights reserved.
//

#include <iostream>
#include <random>
#include <cstdlib>
#include <algorithm>
#include <list>

#include "AI.hpp"
#include "View.hpp"


AI::AI(Snake * s) : Control(s)
{
    snake = s;
    View::get()->setonAI(this);
}

AI::~AI()
{
}


void AI::OnMove()
{
    Dir d[4] = {UP, DOWN, LEFT, RIGHT};
    
    std::random_device rd;
    std::mt19937 g(rd());
    
    std::shuffle(d, d + 4, g);
    //int i = std::rand();
    Coord r = Game::get()->near(snake->body.front());
    
    snake->dir = NO;
    
    bool ok = false;
 
    Game * game = Game::get();
    
    if(r != Coord(0, 0)){
        int now = r.distance(snake->body.front());
        
        for(auto p : d)
        {
            snake->dir = p;
            char next_p = game->checkplacesnake(snake->NextPosition(p, snake->body.front()));
            int next = r.distance(snake->NextPosition(p, snake->body.front()));
            if(next < now && (next_p == ' ' || next_p == 'r'))
            {
                ok = true;
                break;
            }
        }
    }
    
    if(!ok)
        for(auto p : d)
        {
            snake->dir = p;
            Coord c = snake->NextPosition(p, snake->body.front());
            if(game->checkplacesnake(c) == ' ')
            {
                //snake->dir = p;
                break;
            }
        }
    
//    snake->move();
}
