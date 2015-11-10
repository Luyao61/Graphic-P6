//
//  MatrixTransform.hpp
//  CSE167 Spring 2015 Starter Code
//


#ifndef MatrixTransform_h
#define MatrixTransform_h

#include <stdio.h>
#include "Matrix4.h"
#include "Group.h"

class MatrixTransform: public Group
{
    
public:
    //variables
    Matrix4 M;
    
    
    //constructors
    MatrixTransform();
    
    //methods
    void draw(Matrix4 C);
    //void update();
    
    void scale(float,float,float);
    void translate(float,float,float);
    void rotateX(float);
    
    void selfRotateY(float);
    
};

#endif /* MatrixTransform_h */
