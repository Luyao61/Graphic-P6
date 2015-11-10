//
//  Geode.cpp
//  CSE167 Spring 2015 Starter Code
//


#include "Geode.h"
#include "Matrix4.h"
#include "Globals.h"
#include "Vector3.h"

using namespace::std;

Geode::Geode() : Node(){
    //this->modelview.identity();
}

void Geode::setModelView(Matrix4 pass_modelview){
    this->modelview = pass_modelview;
}

Matrix4 Geode::getModelView(){
    return this->modelview;
}

//Set ModelView matrix for current render, Call render()
void Geode::draw(Matrix4 C){
    this->modelview = C;
    if (! Globals::isCulling ) {
        render(modelview);
        //center.print("center 1: ");
        if (Globals::showBounding) {
            glMatrixMode(GL_MODELVIEW);
            glPushMatrix();
            Matrix4 m;
            m.identity();
            m.makeTranslate(center);
            glColor3f(1.0, 1.0, 1.0);
            glMultMatrixf(m.ptr());
            glutWireSphere(radius, 50, 50);
            glPopMatrix();
            //cout<< "show bounding box" <<endl;
        }
    }
    else{
        findBBox(modelview);
        //
        
        float dist1, dist2, dist3, dist4, dist5, dist6;
        
        dist1 = (center - Globals::camera.ntr).dot(Globals::camera.n1);
        dist2 = (center - Globals::camera.ftr).dot(Globals::camera.n2);
        dist3 = (center - Globals::camera.ntl).dot(Globals::camera.n3);
        dist4 = (center - Globals::camera.ftr).dot(Globals::camera.n4);
        dist5 = (center - Globals::camera.ftl).dot(Globals::camera.n5);
        dist6 = (center - Globals::camera.nbr).dot(Globals::camera.n6);
       
        //center.print("center 2: ");
        //cout<< " " << radius  << " "<< dist1 << " " << dist2 << " " << dist3 << " " << dist4 << " "<< dist5 <<  " " << dist6<<std::endl;
        if (dist1 > -radius && dist2 > -radius && dist3 > -radius && dist4 > -radius && dist5 > -radius && dist6 > -radius) {
        //if (dist1 > 0 && dist2 > 0 && dist3 > 0 && dist4 > 0 && dist5 > 0 && dist6 > 0) {
            render(modelview);
            if (Globals::showBounding) {
                glMatrixMode(GL_MODELVIEW);
                glPushMatrix();
                Matrix4 m;
                m.identity();
                m.makeTranslate(center);
                glColor3f(1.0, 1.0, 1.0);
                glMultMatrixf(m.ptr());
                glutWireSphere(radius, 50, 50);
                glPopMatrix();
                //cout<< "show bounding box" <<endl;
            }
        }
    }
}

