//
//  Geode.hpp
//  CSE167 Spring 2015 Starter Code
//

#ifndef Geode_h
#define Geode_h

#include <stdio.h>
#include "Node.h"
#include "Matrix4.h"
#include "Vector3.h"

class Geode : public Node
{
    
public:
    
    //variables
    Matrix4 modelview;
    Vector3 center;
    float radius;
    
    //constructors
    Geode();
    
    //methods
    void setModelView(Matrix4 pass_modelview);
    Matrix4 getModelView();

    void draw(Matrix4 C);
    virtual void render(Matrix4 pass_modelview) = 0;
    virtual void findBBox(Matrix4 pass_modelview) = 0;
};

#endif /* Geode_h */
