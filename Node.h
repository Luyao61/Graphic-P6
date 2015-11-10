//
//  Node.hpp
//  CSE167 Spring 2015 Starter Code
//


#ifndef Node_h
#define Node_h

#include <stdio.h>
#include "Matrix4.h"

class Node
{
    
public:
    //variables
    std::string name;
    float minX, minY, minZ, maxX, maxY, maxZ;
    
    //constructors
    Node();
    Node(std::string newname);
    
    //methods
    void setName(std::string newname);
    std::string getName();
    
    virtual void draw(Matrix4 C) = 0;
    //virtual void update() = 0;

};

#endif /* Node_h */
