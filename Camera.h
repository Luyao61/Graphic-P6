#ifndef CSE167_Camera_h
#define CSE167_Camera_h

#include "Matrix4.h"
#include "Vector3.h"
#include "Vector4.h"
#include <math.h>

class Camera
{
private:
    
protected:
    
    Matrix4 c;   //Camera Matrix
    Matrix4 ci;  //Inverse of Camera Matrix

    
public:
    
    Vector3 e;   //Center of Projection
    Vector3 d;   //Look At
    Vector3 up;  //Up Vector ^
    
    Vector3 p; // camera position
    Vector3 d1; //camera direction
    Vector3 up1, right;
    float nearDist = 1;
    float farDist = 1000;
    float Hnear, Wnear, Hfar, Wfar;
    Vector3 fc, ftl, ftr, fbr, fbl, nc, ntl, ntr, nbl, nbr;
    Vector3 n1,n2,n3,n4,n5,n6;

    
    Camera(void);
    ~Camera(void);
    
    void update(void);
    
    Matrix4& getMatrix(void);
    Matrix4& getInverseMatrix(void);
    
    void set(Vector3&, Vector3&, Vector3&);
    
    void reset(void);
    
};

#endif
