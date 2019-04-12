#ifndef Keypressable_hpp
#define Keypressable_hpp

#include <stdio.h>

class Keypressable
{
public:
    virtual void onkey(char key) = 0;
};

#endif /* Keypressable_hpp */
