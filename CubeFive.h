//
//  CubeFive.hpp
//  CSE167 Spring 2015 Starter Code
//


#ifndef CubeFive_h
#define CubeFive_h

#include <stdio.h>
#include "Geode.h"

class CubeFive : public Geode
{
    
public:
    //variables
    
    //constructors
//    CubeFive();
    
    //methods
    void render(Matrix4 pass_modelview);
    void findBBox(Matrix4);

    void drawBBox(Matrix4);
};

#endif /* CubeFive_h */
