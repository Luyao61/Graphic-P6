#ifndef CSE167_Window_h
#define CSE167_Window_h

#include "Vector4.h"

class Window	  // OpenGL output window related routines
{
    
public:
    
    static int width, height; 	            // window size
    
    static void initialize(void);
    static void idleCallback(void);
    static void reshapeCallback(int, int);
    static void displayCallback(void);
    static void processNormalKeys(unsigned char key, int x, int y);
    static void processSpecialKeys(int key, int x, int y);
    static void processMouse(int button, int state, int x, int y);
    static void processMouseActiveMotion(int x, int y);
    static void processMouseWheel(int button, int dir, int x, int y);
    static void processMouseMotion(int x, int y);
    
    static void createRobot();
    static void walkRobot();
    static void animate1();
};

#endif

