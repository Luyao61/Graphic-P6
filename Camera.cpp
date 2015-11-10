#include "Camera.h"

Camera::Camera()
{
    c.identity();
    e.set(0.0, 0.0, 20.0);
    d.set(0.0, 0.0, 0.0);
    up.set(0.0, 1.0, 0.0);
    
    update();
    
    //Pre-define a camera matrix (and its inverse) that are shifted 'e' from the origin
    //This is used as a default camera position for Project 1
    //c.set(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, e[0], e[1], e[2], 1);
    //ci.set(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, -e[0], -e[1], -e[2], 1);
}

Camera::~Camera()
{
    //Delete and dynamically allocated memory/objects here
}

Matrix4& Camera::getMatrix()
{
    update();
    return c;
}

Matrix4& Camera::getInverseMatrix()
{
    update();
    return ci;
}

void Camera::update()
{
    //Update the Camera Matrix using d, e, and up
    //Solve for the z, x, and y axes of the camera matrix
    //Use these axes and the e vector to create a camera matrix c
    
    Vector3 z_c = e.subtract(d).multiply(1/e.subtract(d).magnitude());
    Vector3 x_c = up.cross(z_c).multiply(1/(up.cross(z_c).magnitude()));
    Vector3 y_c = up.multiply(1/up.magnitude());
    c.set( *x_c.ptr(), *(x_c.ptr()+1), *(x_c.ptr()+2), 0.0,
          *y_c.ptr(), *(y_c.ptr()+1), *(y_c.ptr()+2), 0.0,
          *z_c.ptr(), *(z_c.ptr()+1), *(z_c.ptr()+2), 0.0,
          *e.ptr(), *(e.ptr()+1), *(e.ptr()+2), 1.0);
    
     //Use c to solve for an inverse camera matrix ci
    ci = c.rigidInverse();
    
    
    p = Vector3(e);
    d1 = Vector3(d - p);
    up1 = Vector3(up);
    d1 = d1.normalize();
    up1 = up1.normalize();
    right = d1.cross(up1);
    right = right.normalize();
    
    Hnear = nearDist/sqrtf(3.0)*2.0;
    Wnear = nearDist/sqrtf(3.0)*2.0;
    Hfar = farDist/sqrtf(3.0)*2.0 ;
    Wfar = farDist/sqrtf(3.0)*2.0 ;
    
    
    fc = p + d1 * farDist;
    
    ftl = fc + (up1 * (Hfar/2)) - (right * (Wfar/2));
    ftr = fc + (up1 * (Hfar/2)) + (right * (Wfar/2));
    fbl = fc - (up1 * (Hfar/2)) - (right * (Wfar/2));
    fbr = fc - (up1 * (Hfar/2)) + (right * (Wfar/2));
    
    nc = p + d1 * nearDist;
    
    ntl = nc + (up1 * (Hnear/2)) - (right * (Wnear/2));
    ntr = nc + (up1 * (Hnear/2)) + (right * (Wnear/2));
    nbl = nc - (up1 * (Hnear/2)) - (right * (Wnear/2));
    nbr = nc - (up1 * (Hnear/2)) + (right * (Wnear/2));
    
    //front normal
    n1 = (nbr-ntr).cross(ntl-ntr);
    n1 = n1.normalize();
    //back normal
    n2 = (ftl-ftr).cross(fbr-ftr);
    n2 = n2.normalize();
    //left normal
    n3 = (ntl-ftl).cross(fbl-ftl);
    n3 = n3.normalize();
    //right normal
    n4 = (fbr-ftr).cross(ntr-ftr);
    n4 = n4.normalize();
    //top normal
    n5 = (ftr-ftl).cross(ntl-ftl);
    n5 = n5.normalize();
    //bot normal
    n6 = (fbr-nbr).cross(nbl-nbr);
    n6 = n6.normalize();

    
}

void Camera::set(Vector3& e, Vector3& d, Vector3& up)
{
    this->e = e;
    this->d = d;
    this->up = up;
    update();
}

void Camera::reset(){
    c.identity();
    e.set(0.0, 0.0, 20.0);
    d.set(0.0, 0.0, 0.0);
    up.set(0.0, 1.0, 0.0);
    update();

}
