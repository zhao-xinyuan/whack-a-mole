/*****************************************************************************
Copyright: 2012, ustc All rights reserved.
contact:k283228391@126.com
File name: particalsystem.Cpp
Description:Partical in opengl.
Author:Silang Quan
Version: 1.0
Date: 2012.12.22
 *****************************************************************************/

#include "particalsystem.h"

ParticalSystem::ParticalSystem()
{
    //ctor
}

ParticalSystem::~ParticalSystem()
{
    //dtor
}

void ParticalSystem::init()
{
    int i;
    Color colors[3]={{1,0,0,1},{1,1,0,1}};
    for(i=0;i<ptlCount;i++)
    {
        //theta =(rand()%361)/360.0* 2*PI;
        Particle tmp={Vector3D(0,0,0),Vector3D(0.0,0.0,0.0),Vector3D(0,0,0),colors[rand()%2],0.0f,1+0.1*(rand()%10),0.3f};
        particles.push_back(tmp);
    }
    mySphere=gluNewQuadric();
}

void Snow::initSnow(float asp,float dim)
{
    int i;
    Color colors={1,1,1,1};
    for(i=0;i<ptlCount;i++)
    {
        int k=rand()%3;
        if(k==0)
        {
            Particle tmp={Vector3D(fmod(rand(),(2.0*asp*dim))-asp*dim, dim, fmod(rand(),(2.0*dim))-dim),
                      Vector3D(rand()%5,rand()%5,rand()%5),
                      Vector3D(0,0,0),colors,1.0f,1+0.1*(rand()%10),1.0};
                    particles.push_back(tmp);
        }
        else if(k==1)
        {
            Particle tmp={Vector3D(asp*dim, fmod(rand(),dim), fmod(rand(),(2.0*dim))-dim),
                      Vector3D(rand()%5,rand()%5,rand()%5),
                      Vector3D(0,0,0),colors,0.8f,1+0.1*(rand()%10),0.02f};
                    particles.push_back(tmp);
        }
        else
        {
            Particle tmp={Vector3D(-asp*dim, fmod(rand(),dim), fmod(rand(),(2.0*dim))-dim),
                      Vector3D(rand()%5,rand()%5,rand()%5),
                      Vector3D(0,0,0),colors,0.0f,1+0.1*(rand()%10),0.02f};
                    particles.push_back(tmp);
        }
    }
    texture=LoadTexBMP("snowflower.bmp");
}

void Snow::snowSimulate(float dt,float asp,float dim)
{
    snowAging(dt,asp,dim);
    applyGravity();
    kinematics(dt);
}

void Snow::snowAging(float dt,float asp,float dim)
{
    for(std::vector<Particle>::iterator iter=particles.begin();iter!=particles.end();iter++)
    {
        iter->age+=dt;
        if(iter->age>iter->life)
        {
            int k=rand()%3;
            if(k==0)
            {
                iter->position={Vector3D(fmod(rand(),(2.0*asp*dim))-asp*dim, dim, fmod(rand(),(2.0*dim))-dim)};

            }
            else if(k==1)
            {
                iter->position={Vector3D(0.9*asp*dim, fmod(rand(),dim), fmod(rand(),(2.0*dim))-dim)};
            }
            else
            {
               iter->position={Vector3D(-asp*dim, fmod(rand(),dim), fmod(rand(),(2.0*dim))-dim)};
            }
            iter->size=0.0;
            iter->age=0.0;
            iter->velocity=Vector3D(rand()%5,rand()%5,0.0);
        }
    }
}

void ParticalSystem::applyGravity()
{
    for(std::vector<Particle>::iterator iter=particles.begin();iter!=particles.end();iter++)
            iter->acceleration=Vector3D(0,gravity,0);
}

void Snow::snowRender(float th)
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,texture);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE);
    glShadeModel(GL_SMOOTH);
    for(std::vector<Particle>::iterator iter=particles.begin();iter!=particles.end();iter++)
    {
        float alpha = 1 - iter->age / iter->life;
        Vector3D tmp=iter->position;
        glColor4f(iter->color.r,iter->color.g,iter->color.b,alpha);
        if(iter->size==0)
        {
            //glColor4f(1.0f, 1.0f, 1.0f, 0.1);
            glPushMatrix();
            glRotatef(-th,0,1,0);
            //glRotatef(-ph,1,0,0);
            glTranslatef(tmp.x,tmp.y,tmp.z);
            glBegin(GL_QUADS);
            glTexCoord2f(0.0,0.0); glVertex2f(0.0,0.0);
            glTexCoord2f(1.0,0.0); glVertex2f(0.1,0.0);
            glTexCoord2f(1.0,1.0); glVertex2f(0.1,0.1);
            glTexCoord2f(0.0,1.0); glVertex2f(0.0,0.1);
            glEnd();
            glPopMatrix();
        }
    }
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
}

void Fire::initFire(float posX,float posY,float posZ)
{
    int i;
    Color white={1,1,1,1};
    for(i=0;i<ptlCount;i++)
    {
        //theta =(rand()%361)/360.0* 2*PI;
        Particle tmp={Vector3D(posX,posY,posZ),Vector3D(float((rand()%50)-25.0f)*10.0f,
                      float((rand()%50)-25.0f)*10.0f,float((rand()%50)-25.0f)*10.0f),
                      Vector3D(0.0f,0.8f,0.0f),white,0.0f,1.0f,3.0f};
        particles.push_back(tmp);
    }
    texture=LoadTexBMP("Particle.bmp");
}

void Fire::fireRender(float th)
{
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,texture);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE);
    glPushMatrix();
    glRotatef(-th,0,1,0);
    //glRotatef(-ph,1,0,0);
    for(std::vector<Particle>::iterator iter=particles.begin();iter!=particles.end();iter++)
    {
        float alpha = 1 - iter->age / iter->life;
        glColor4f(iter->color.r,iter->color.g,iter->color.b,alpha);
        glBegin(GL_TRIANGLE_STRIP);
        Vector3D tmp=iter->position;
        glTexCoord2d(1,1); glVertex3f(tmp.x+0.5f,tmp.y+0.5f,tmp.z); // Top Right
        glTexCoord2d(0,1); glVertex3f(tmp.x-0.5f,tmp.y+0.5f,tmp.z); // Top Left
        glTexCoord2d(1,0); glVertex3f(tmp.x+0.5f,tmp.y-0.5f,tmp.z); // Bottom Right
        glTexCoord2d(0,0); glVertex3f(tmp.x-0.5f,tmp.y-0.5f,tmp.z);
        glEnd();
    }
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
}

void ParticalSystem::kinematics(float dt)
{
    for(std::vector<Particle>::iterator iter=particles.begin();iter!=particles.end();iter++)
    {
        iter->position = iter->position+iter->velocity*dt;
        iter->velocity = iter->velocity+iter->acceleration*dt;
    }
}
void ParticalSystem::kinematics(float dt,float posX,float posY)
{
    for(std::vector<Particle>::iterator iter=particles.begin();iter!=particles.end();iter++)
    {
        iter->position = iter->position+iter->velocity*dt;
        if((iter->position.x>posX)&&(iter->position.y>(0.1+posY))){
            iter->acceleration.x=-0.0003f;
        } else if((iter->position.x<posX)&&(iter->position.y>(0.1+posY))){
            iter->acceleration.x=0.0003f;
        } else {
            iter->acceleration.x=0.0f;
        }
        iter->velocity = iter->velocity+iter->acceleration*dt;
    }
}
void Fire::fireAging(float posX,float posY,float posZ)
{
    for(std::vector<Particle>::iterator iter=particles.begin();iter!=particles.end();iter++)
    {
        iter->age+=iter->size;
        if(iter->age>iter->life)
        {
            iter->position=Vector3D(posX,posY,posZ);
            iter->age=0.0;
            iter->velocity=Vector3D(float((rand()%60)-30.0f)/750,
                                    float((rand()%60)-30.0f)/1000,
                                    float((rand()%60)-30.0f)/750);
            iter->acceleration=Vector3D(0.0,0.0008,0.0);
            iter->color={1.0f,1.0f,1.0f,1.0f};
            iter->size=float(rand()%100)/1000.0f+0.003f;
        }
        else if (iter->age>0.6f)
        {
            iter->color={1.0f,0.0f,0.0f,1.0f};
        }
        else if (iter->age>0.4f)
        {
            iter->color={1.0f,0.5f,0.0f,0.0};
        }
        else if (iter->age>0.25f)
        {
            iter->color={1.0f,1.0f,0.0f,1.0f};
        }
        else if (iter->age>0.15f)
        {
            iter->color={1.0f,0.0f,0.0f,1.0f};
        }
    }
}

void Fire::fireSimulate(float posX,float posY,float posZ)
{
    fireAging(posX,posY,posZ);
    kinematics(1.0,posX,posY);
}
