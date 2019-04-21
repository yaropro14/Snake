//
//  AI.hpp
//  Snake
//
//  Created by Yaroslav on 19/04/2019.
//  Copyright © 2019 Yaroslav. All rights reserved.
//

#ifndef AI_hpp
#define AI_hpp

#include <stdio.h>

#include "Control.hpp"

class AI : public Control
{
public:
    AI(Snake * s);
    ~AI();
    
    void OnMove();
    
    Snake * snake;
};

#endif /* AI_hpp */
