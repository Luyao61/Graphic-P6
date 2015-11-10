//
//  SphereFive.cpp
//  CSE167 Spring 2015 Starter Code
//

#include "SphereFive.h"
#include <GL/glut.h>
#include "Vector4.h"
#include "Globals.h"
using namespace std;

//SphereFive::SphereFive():Geode(){
//}

void SphereFive::render(Matrix4 pass_modelview){
    findBBox(pass_modelview);
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    glColor3f(1,0,0);
    glMultMatrixf(pass_modelview.ptr());
    glutSolidSphere(1.0, 15.0, 15.0);
    glPopMatrix();
    
    
    Globals::number_heads++;
    if (Globals::showBounding) {
        //drawBBox(pass_modelview);
    }
}

void SphereFive::drawBBox(Matrix4 pass_modelview){
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    
    Matrix4 scale;
    scale.makeScale(2.1,2.1,2.1);
    pass_modelview = pass_modelview * scale;
    glColor3f(1.0, 1.0, 1.0);
    
    glMultMatrixf(pass_modelview.ptr());
    glutWireSphere(0.5, 50, 50);
    glPopMatrix();
    
    
}


void SphereFive::findBBox(Matrix4 pass_modelview){

    Vector4 c, r;
    c.set(0, 0, 0, 1);
    r.set(1/1.4, 1/1.4, 1/1.4, 0);
    //r.set(1, 1, 1, 0);
    c = pass_modelview * c;
    center = c.toVector3();
    r = pass_modelview * r;
    radius = r.toVector3().magnitude();
}