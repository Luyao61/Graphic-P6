//
//  Skybox.cpp
//  CSE167 Spring 2015 Starter Code
//
//  Created by Li Yujia on 15/11/10.
//  Copyright © 2015年 RexWest. All rights reserved.
//

#include "Skybox.hpp"
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

Skybox::Skybox(){
    front = new Texture("skybox_water222_front.ppm");
    back = new Texture("skybox_water222_back.ppm");
    top = new Texture("skybox_water222_top.ppm");
    bot = new Texture("skybox_water222_base.ppm");
    left = new Texture("skybox_water222_left.ppm");
    right = new Texture("skybox_water222_right.ppm");
    toWorld.identity();
}
Skybox::~Skybox(){
    
}

void Skybox::draw(){
    front->bind();
    float halfSize = 10/2.0;
    
    
    //Set the OpenGL Matrix mode to ModelView (used when drawing geometry)
    glMatrixMode(GL_MODELVIEW);
    
    //Push a save state onto the matrix stack, and multiply in the toWorld matrix
    glPushMatrix();
    glMultMatrixf(toWorld.ptr());
    
    //Make cube!
    //Note: The glBegin, and glEnd should always be as close to the glNormal/glVertex calls as possible
    //These are special calls that 'freeze' many internal states of OpenGL.
    //Once the glBegin state is active many of the calls made to OpenGL (like glMultMatrixf) will be IGNORED!
    //As a good habit, only call glBegin just before you need to draw, and call end just after you finish
    front->bind();
    glBegin(GL_QUADS);
    // Draw front face:
    glNormal3f(0.0, 0.0, 1.0);
    glTexCoord2f(0, 1);
    glVertex3f(-halfSize, -halfSize,  halfSize);
    glTexCoord2f(1, 1);
    glVertex3f( halfSize, -halfSize,  halfSize);
    glTexCoord2f(1, 0);
    glVertex3f( halfSize,  halfSize,  halfSize);
    glTexCoord2f(0, 0);
    glVertex3f(-halfSize,  halfSize,  halfSize);
    glEnd();
    
    glBegin(GL_QUADS);
    back->bind();
    // Draw back face:
    glNormal3f(0.0, 0.0, -1.0);
    glTexCoord2f(0, 1);
    glVertex3f(-halfSize, -halfSize,  -halfSize);
    glTexCoord2f(1, 1);
    glVertex3f( halfSize, -halfSize,  -halfSize);
    glTexCoord2f(1, 0);
    glVertex3f( halfSize,  halfSize,  -halfSize);
    glTexCoord2f(0, 0);
    glVertex3f(-halfSize,  halfSize,  -halfSize);
    glEnd();

    glBegin(GL_QUADS);
    right->bind();
    // Draw right side:
    glNormal3f(0.0, 0.0, -1.0);
    glTexCoord2f(0, 1);
    glVertex3f(halfSize,  -halfSize,  halfSize);
    glTexCoord2f(1, 1);
    glVertex3f(halfSize,  -halfSize,  -halfSize);
    glTexCoord2f(1, 0);
    glVertex3f(halfSize,   halfSize,   -halfSize);
    glTexCoord2f(0, 0);
    glVertex3f(halfSize,  halfSize,   halfSize);
    glEnd();

    glBegin(GL_QUADS);
    left->bind();
    // Draw left side:
    glNormal3f(0.0, 0.0, -1.0);
    glTexCoord2f(0, 1);
    glVertex3f(-halfSize, -halfSize,   halfSize);
    glTexCoord2f(1, 1);
    glVertex3f(-halfSize, -halfSize,  -halfSize);
    glTexCoord2f(1, 0);
    glVertex3f(-halfSize,  halfSize,  -halfSize);
    glTexCoord2f(0, 0);
    glVertex3f(-halfSize,  halfSize,   halfSize);
    glEnd();

    glBegin(GL_QUADS);
    top->bind();
    // Draw top side:
    glNormal3f(0.0, 0.0, -1.0);
    glTexCoord2f(0, 1);
    glVertex3f(-halfSize,  halfSize,  -halfSize);
    glTexCoord2f(1, 1);
    glVertex3f( halfSize,  halfSize,  -halfSize);
    glTexCoord2f(1, 0);
    glVertex3f( halfSize,  halfSize,   halfSize);
    glTexCoord2f(0, 0);
    glVertex3f(-halfSize,  halfSize,   halfSize);
    glEnd();

    glBegin(GL_QUADS);
    bot->bind();
    // Draw bot side:
    glNormal3f(0.0, 0.0, -1.0);
    glTexCoord2f(0, 1);
    glVertex3f(-halfSize,  -halfSize,  -halfSize);
    glTexCoord2f(1, 1);
    glVertex3f( halfSize,  -halfSize,  -halfSize);
    glTexCoord2f(1, 0);
    glVertex3f( halfSize,  -halfSize,   halfSize);
    glTexCoord2f(0, 0);
    glVertex3f(-halfSize,  -halfSize,   halfSize);
    glEnd();

    
    //Pop the save state off the matrix stack
    //This will undo the multiply we did earlier
    glPopMatrix();
}