//
//  MatrixTransform.cpp
//  CSE167 Spring 2015 Starter Code
//

#include <iostream>
#include "MatrixTransform.h"
#include "Matrix4.h"

MatrixTransform::MatrixTransform():Group(){
    M = Matrix4();
    M.identity();
}

//Multiplies Matrix4 M with Matrix4 C
//Passes resulting Matrix4 down to children
//Group::draw()

void MatrixTransform::draw(Matrix4 C){
    Matrix4 M2 = C.multiply(this->M);
    Group::draw(M2);
}

/*
void MatrixTransform::update(){
    for(int i = 0; i < children->size();i++){

    increase ? i++ :i--;
    if (i==-10 || i ==10) increase = !increase;
    std::cout << this->name<<std::endl;

    std::string body_part = this->name;
    if (body_part == "left_arm") {
        std::cout << " left_arm 0 "<<std::endl;
        Matrix4 move;
        move = move.makeTranslate(0, 2, 0);
        M = move * M;
        
        move.identity();
        move = move.makeRotateY(i/10*3.14/8);
        M = move * M;

        move.identity();
        move = move.makeTranslate(0, -2, 0);
        M = move * M;
    }
    }
    
}
 */

void MatrixTransform::scale(float x, float y, float z){
        Matrix4 scale;
        scale.makeScale(x,y,z);
        M = M * scale;
}

void MatrixTransform::translate(float x, float y, float z){
    Matrix4 move;
    move = move.makeTranslate(x, y, z);    
    M = move * M;
}

void MatrixTransform::rotateX(float x){
    Matrix4 move;
    move = move.makeRotateX(x);
    M = move * M;
}

void MatrixTransform::selfRotateY(float x){
    Matrix4 move;
    move = move.makeRotateY(x);
    M = M * move;
}


