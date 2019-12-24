/*****************************************************************************
Copyright: 2012, ustc All rights reserved.
contact:k283228391@126.com
File name: particalsystem.h
Description:Partical in opengl.
Author:Silang Quan
Version: 1.0
Date: 2012.12.01
 *****************************************************************************/

#ifndef PARTICALSYSTEM_H
#define PARTICALSYSTEM_H
#include <vector>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include "particle.h"
#include "CSCIx229.h"
#define PI 3.1415926
class ParticalSystem
{
    public:
        ParticalSystem();
        ParticalSystem(int _count,float _gravity){ptlCount=_count;gravity=_gravity;}
        void init();
        void applyGravity();
        void kinematics(float dt);
        void kinematics(float dt,float posX,float posY);
        virtual ~ParticalSystem();
    protected:
    int ptlCount;
    float gravity;
    std::vector<Particle> particles;
    GLUquadricObj *mySphere;
};

class Snow: public ParticalSystem
{
    public:
        Snow(){}
        Snow(int _count,float _gravity){ptlCount=_count;gravity=_gravity;}
        void initSnow(float asp,float dim);
        void snowAging(float dt,float asp,float dim);
        void snowSimulate(float dt,float asp,float dim);
        void snowRender(float th);
        virtual ~Snow(){}
    private:
        int texture;
};

class Fire: public ParticalSystem
{
    public:
        Fire(){}
        Fire(int _count,float _gravity){ptlCount=_count;gravity=_gravity;}
        void initFire(float posX,float posY,float posZ);
        void fireAging(float posX,float posY,float posZ);
        void fireSimulate(float posX,float posY,float posZ);
        void fireRender(float th);
        void fireShrink();
        virtual ~Fire(){}
    private:
        int texture;
};
#endif // PARTICALSYSTEM_H
