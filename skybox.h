#ifndef SKYBOX_H
#define SKYBOX_H
#include "CSCIx229.h"
class skybox
{
    public:
        skybox(){}
        void skyboxRender(float dim,float asp);
    public:
        void bindtexture();
        int texture[5];
};

#endif // SKYBOX_H

