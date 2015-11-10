#include <iostream>

#ifdef __APPLE__
    #include <GLUT/glut.h>
    //#include <GL/freeglut.h>
#else
    #include <GL/glut.h>
#endif

#include "Window.h"
#include "Cube.h"
#include "Matrix4.h"
#include "Globals.h"
#include "Group.h"
#include "MatrixTransform.h"
#include "SphereFive.h"
#include "CubeFive.h"
#include <math.h>

int Window::width  = 512;   //Set window width in pixels here
int Window::height = 512;   //Set window height in pixels here

int frame=0;
int t; //time
int timebase=0;

SphereFive *sphere5 = new SphereFive();
CubeFive *cube5 = new CubeFive();
MatrixTransform *robot, *head, *torso, *left_arm, *right_arm, *left_leg, *right_leg;
MatrixTransform *platoon1, *platoon2;
int army_size = 10;
//int army_size = 40;
//int army_size = 20;
std::vector<std::vector<MatrixTransform*>> robot_army_1(army_size, std::vector<MatrixTransform*> (army_size));
std::vector<std::vector<MatrixTransform*>> robot_army_2(army_size, std::vector<MatrixTransform*> (army_size));

bool increase = true;
float rotate = -10.0;

int frame1=-1;
bool animate = false;
float fps = 0.0;
void Window::initialize(void)
{
    //set_light();
    Vector4 lightPos(0.0, 10.0, 15.0, 1.0);
    Globals::light.position = lightPos;
    Globals::light.quadraticAttenuation = 0.02;
    createRobot();
    platoon1 = new MatrixTransform();
    for (int i = 0 ; i<army_size; i++) {
        for (int j = 0; j<army_size; j++) {
            robot_army_1[i][j] = new MatrixTransform();
            robot_army_1[i][j] -> translate(3.5 + j*6, 0 ,-i*5);
            robot_army_1[i][j] ->addChild(robot);
            platoon1->addChild(robot_army_1[i][j]);
        }
    }
    
    platoon2 = new MatrixTransform();
    for (int i = 0 ; i<army_size; i++) {
        for (int j = 0; j<army_size; j++) {
            robot_army_2[i][j] = new MatrixTransform();
            robot_army_2[i][j] -> translate(-3.5 - j*6,0,-i*5);
            robot_army_2[i][j] ->addChild(robot);
            platoon2->addChild(robot_army_2[i][j]);
        }
    }
}

//----------------------------------------------------------------------------
// Callback method called when system is idle.
// This is called at the start of every new "frame" (qualitatively)
void Window::idleCallback()
{
    //Set up a static time delta for update calls
    Globals::updateData.dt = 1.0/60.0;// 60 fps

    //Call the display routine to draw the cube
    displayCallback();
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when graphics window is resized by the user
void Window::reshapeCallback(int w, int h)
{
    width = w;                                                       //Set the window width
    height = h;                                                      //Set the window height
    glViewport(0, 0, w, h);                                          //Set new viewport size
    glMatrixMode(GL_PROJECTION);                                     //Set the OpenGL matrix mode to Projection
    glLoadIdentity();                                                //Clear the projection matrix by loading the identity
    gluPerspective(60.0, double(width)/(double)height, 1.0, 1000.0); //Set perspective projection viewing frustum
}

//----------------------------------------------------------------------------
// Callback method called by GLUT when window readraw is necessary or when glutPostRedisplay() was called.
void Window::displayCallback()
{
    frame++;
    t=glutGet(GLUT_ELAPSED_TIME);
    if (t - timebase > 1000) {
        //printf("FPS:%4.2f\n",
//               frame*1000.0/(t-timebase));
        fps = frame*1000.0/(t-timebase);
        timebase = t;
        frame = 0;
        //std::cout << "Robots: "<<Globals::number_heads << std::endl;
        //printf("#Robots:%d\n",Globals::number_heads);
    }

    Globals::number_heads = 0;
    //Clear color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //Set the OpenGL matrix mode to ModelView
    glMatrixMode(GL_MODELVIEW);
    
    //Push a matrix save point
    //This will save a copy of the current matrix so that we can
    //make changes to it and 'pop' those changes off later.
    glPushMatrix();
    
    //Replace the current top of the matrix stack with the inverse camera matrix
    //This will convert all world coordiantes into camera coordiantes
    
    glLoadMatrixf(Globals::camera.getInverseMatrix().ptr());
    
    walkRobot();
    if (animate) {
        frame1++;
        animate1();
        if(frame1 == 1300){
            animate = false;
            frame1 = -1;
        }
    }

    Matrix4 m;
    m.identity();
    platoon1->draw(m);
    platoon2->draw(m);
    
    glDisable( GL_DEPTH_TEST ) ; // also disable the depth test so renders on top
    glDisable(GL_LIGHTING);
    //glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0,1.0,1.0);
    glRasterPos2i(-10,10);
    //glColor3f(1.0,0.0,0.0);
    char buf[300];
    //std::string num =  "# of Robots:" + std::to_string(Globals::number_heads);
    sprintf( buf, "Robots: %d", Globals::number_heads) ;
    const char * p = buf ;
    do glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, *p ); while( *(++p) ) ;

    glRasterPos2i(-10,8);
    char buf1[300];
    sprintf( buf1, "FPS: %4.2f\n", fps) ;
    p = buf1 ;
    do glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, *p ); while( *(++p) ) ;

    glEnable( GL_DEPTH_TEST ) ; // Turn depth testing back on
    glEnable(GL_LIGHTING);

   
    //Bind the light to slot 0.  We do this after the camera matrix is loaded so that
    //the light position will be treated as world coordiantes
    //(if we didn't the light would move with the camera, why is that?)
    Globals::light.bind(0);

    //Pop off the changes we made to the matrix stack this frame
    glPopMatrix();
    
    //Tell OpenGL to clear any outstanding commands in its command buffer
    //This will make sure that all of our commands are fully executed before
    //we swap buffers and show the user the freshly drawn frame
    glFlush();
    
    //Swap the off-screen buffer (the one we just drew to) with the on-screen buffer
    glutSwapBuffers();
}


//TODO: Keyboard callbacks!
//No more Keyboard instructions
void Window::processNormalKeys(unsigned char key, int x, int y) {
    if (key == 27) {
        exit(0);
    }
    else if(key == 'b' || key == 'B'){
        Globals::showBounding = !Globals::showBounding;
    }
    else if(key == 'c' || key == 'C'){
        Globals::isCulling = !Globals::isCulling;
    }
    else if(key == 'a' || key == 'A'){
        Matrix4 r;
        r.makeRotateY(0.1);
        Globals::camera.e = r * Globals::camera.e;
        Globals::camera.update();
    }
    else if(key == 'd' || key == 'D'){
        Matrix4 r;
        r.makeRotateY(-0.1);
        Globals::camera.e = r * Globals::camera.e;
        Globals::camera.update();
    }
    else if(key == 'w' || key == 'W'){
        Matrix4 r;
        r.makeScale(0.9);
        Globals::camera.e = r * Globals::camera.e;
        Globals::camera.update();
    }
    else if(key == 's' || key == 'S'){
        Matrix4 r;
        r.makeScale(1.1);
        Globals::camera.e = r * Globals::camera.e;
        Globals::camera.update();
    }
    else if(key == 'r' || key == 'R'){
        Globals::camera.e = Vector3(0,0,20);
        Globals::camera.update();
    }
    else if(key =='m' || key == 'M'){
        animate = !animate;
    }

}

//TODO: Function Key callbacks!
void Window::processSpecialKeys(int key, int x, int y) {

}

//TODO: Mouse callbacks!
void Window::processMouse(int button, int state, int x, int y){

}


//TODO: Mouse Motion callbacks!
void Window::processMouseActiveMotion(int x, int y){

}

void Window::processMouseMotion(int x, int y){

}


void Window::createRobot(){
    robot = new MatrixTransform();
    
    head = new MatrixTransform();
    //head->scale(0.5, 0.5, 0.5);
    //head->translate(0.0, 0.0, 0.0);
    
    torso = new MatrixTransform();
    torso->scale(3.0,4.0,3.0);
    torso->translate(0.0, -3.5, 0.0);
    
    left_arm = new MatrixTransform();
    left_arm->scale(1, 2, 1);
    left_arm->translate(-2.5, -3, 0);
    
    right_arm = new MatrixTransform();
    right_arm->scale(1, 2, 1);
    right_arm->translate(2.5, -3, 0);
    
    left_leg = new MatrixTransform();
    left_leg->scale(1, 2, 1);
    left_leg->translate(-1, -7, 0);
    
    right_leg = new MatrixTransform();
    right_leg->scale(1, 2, 1);
    right_leg->translate(1, -7, 0);
    
    head->name = "Head";
    head->addChild(sphere5);
    
    torso->name = "Torso";
    torso->addChild(cube5);
    
    left_leg->name = "left_leg";
    left_leg->addChild(cube5);
    
    left_arm->name = "left_arm";
    left_arm->addChild(cube5);
    
    right_leg->name = "right_leg";
    right_leg->addChild(cube5);
    
    right_arm->name = "right_arm";
    right_arm->addChild(cube5);
    
    robot->addChild(head);
    robot->addChild(torso);
    robot->addChild(left_arm);
    robot->addChild(left_leg);
    robot->addChild(right_arm);
    robot->addChild(right_leg);
}

void Window::walkRobot(){
    increase ? rotate++ : rotate--;
    if (rotate==-10 || rotate ==10) increase = !increase;
    
    left_arm->translate(0, 2, 0);
    left_arm->rotateX(rotate/100*3.14/2);
    left_arm->translate(0, -2, 0);
    
    right_arm->translate(0, 2, 0);
    right_arm->rotateX(-rotate/100*3.14/2);
    right_arm->translate(0, -2, 0);
    
    left_leg->translate(0, 6, 0);
    left_leg->rotateX(-rotate/100*3.14/2);
    left_leg->translate(0, -6, 0);
    
    right_leg->translate(0, 6, 0);
    right_leg->rotateX(rotate/100*3.14/2);
    right_leg->translate(0, -6, 0);
}

void Window::animate1(){
    
    if (0<=frame1 && frame1<=100) {
        for (int i = 0 ; i<army_size; i++) {
            for (int j = 0; j<army_size; j++) {
                robot_army_1[i][j]->selfRotateY(M_PI/100.0);
            }
        }
        for (int i = 0 ; i<army_size; i++) {
            for (int j = 0; j<army_size; j++) {
                robot_army_2[i][j]->selfRotateY(-M_PI/100.0);
            }
        }

    }
    
    if (100<frame1 && frame1<200) {
        platoon1->translate(0.0, 0.0, -0.1);
        platoon2->translate(0.0, 0.0, -0.1);
    }
    
    if (200<=frame1 && frame1<=250 ){
        for (int i = 0 ; i<army_size; i++) {
            for (int j = 0; j<army_size; j++) {
                robot_army_1[i][j]->selfRotateY(-M_PI/100.0);
            }
        }
        for (int i = 0 ; i<army_size; i++) {
            for (int j = 0; j<army_size; j++) {
                robot_army_2[i][j]->selfRotateY(M_PI/100.0);
            }
        }
    }
    if (250<frame1 && frame1<300) {
        platoon1->translate(0.1, 0.0, 0.0);
        platoon2->translate(-0.1, 0.0, 0.0);
    }
    if (300<=frame1 && frame1<=350 ){
        for (int i = 0 ; i<army_size; i++) {
            for (int j = 0; j<army_size; j++) {
                robot_army_1[i][j]->selfRotateY(-M_PI/100.0);
            }
        }
        for (int i = 0 ; i<army_size; i++) {
            for (int j = 0; j<army_size; j++) {
                robot_army_2[i][j]->selfRotateY(M_PI/100.0);
            }
        }
    }
    if (350<frame1 && frame1<450) {
        platoon1->translate(0.0, 0.0, 0.1);
        platoon2->translate(0.0, 0.0, 0.1);
    }


    if (450<=frame1 && frame1<=525) {
        for (int i = 0 ; i<army_size; i++) {
            for (int j = 0; j<army_size; j++) {
                robot_army_1[i][j]->selfRotateY(-M_PI/100.0);
            }
        }
        for (int i = 0 ; i<army_size; i++) {
            for (int j = 0; j<army_size; j++) {
                robot_army_2[i][j]->selfRotateY(M_PI/100.0);
            }
        }
    }
    if (525<frame1 && frame1<825) {
        platoon1->translate(-0.1, 0.0, -0.1);
        platoon2->translate(0.1, 0.0, -0.1);
    }

    if (850<frame1 && frame1<1150) {
        platoon1->translate(0.1, 0.0, 0.1);
        platoon2->translate(-0.1, 0.0, 0.1);
    }
    if (1150<=frame1 && frame1<=1225) {
        for (int i = 0 ; i<army_size; i++) {
            for (int j = 0; j<army_size; j++) {
                robot_army_1[i][j]->selfRotateY(M_PI/100.0);
            }
        }
        for (int i = 0 ; i<army_size; i++) {
            for (int j = 0; j<army_size; j++) {
                robot_army_2[i][j]->selfRotateY(-M_PI/100.0);
            }
        }
    }
    if (1250<frame1 && frame1<1300) {
        platoon1->translate(-0.1, 0.0, 0.0);
        platoon2->translate(0.1, 0.0, 0.0);
    }

}

