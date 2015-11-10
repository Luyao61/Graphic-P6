//
//  SphereFive.hpp
//  CSE167 Spring 2015 Starter Code
//


#ifndef SphereFive_h
#define SphereFive_h

#include <stdio.h>
#include "Geode.h"

class SphereFive : public Geode
{

public:
    
    //variables
    
    //constructors
    //SphereFive();
    //methods
    void render(Matrix4 pass_modelview);
    void findBBox(Matrix4);
    
    void drawBBox(Matrix4);
};

#endif /* SphereFive_h */
