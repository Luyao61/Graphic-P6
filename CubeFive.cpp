//
//  CubeFive.cpp
//  CSE167 Spring 2015 Starter Code
//

#include "CubeFive.h"
#include <GL/glut.h>
#include "Vector4.h"
#include "Globals.h"
using namespace std;

//CubeFive::CubeFive():Geode(){
//}

void CubeFive::render(Matrix4 pass_modelview){
    findBBox(pass_modelview);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glColor3f(0.0, 1.0, 0.0);
    glMultMatrixf(pass_modelview.ptr());
    glutSolidCube(1);
    glPopMatrix();
    
    if (Globals::showBounding) {
        //drawBBox(pass_modelview);
    }
}


void CubeFive::drawBBox(Matrix4 pass_modelview){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    
    Matrix4 scale;
    scale.makeScale(1.8,1.8,1.8);
    pass_modelview = pass_modelview * scale;
    glColor3f(1.0, 1.0, 1.0);

    glMultMatrixf(pass_modelview.ptr());
    glutWireSphere(0.5, 50,50);
    glPopMatrix();
}

void CubeFive::findBBox(Matrix4 pass_modelview){
    
    Vector4 c, r;
    c.set(0, 0, 0, 1);
    r.set(0.5, 0.5, 0.5, 0);
    c = pass_modelview * c;
    center = c.toVector3();
    r = pass_modelview * r;
    radius = r.toVector3().magnitude();
}
