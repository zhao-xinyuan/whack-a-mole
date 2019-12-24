#include"snowman.h"

snowman::snowman(int Time1)
{
    Time=Time1;
    srand(Time);
    hit=0.0;
    timeout=0.0;
    position=rand()%6;

}

void snowman::render(double asp,double dim,int obj1)
{

    if(hit==1 || timeout ==1)
    {
        srand(time(0)+Time);
        position=rand()%6;
        timeout=0;
                hit=0;
                start=clock();
            }
            if(position==0)
            {
                glPushMatrix();
                glTranslatef(0.0,-1.2*dim+0.1*dim*endtime,-0.3*dim);
                glScaled(0.3,0.3,0.3);
                glCallList(obj1);
                glPopMatrix();
            }
            else if(position==1)
            {
                glPushMatrix();
                glTranslatef(0.0,-1.2*dim+0.1*dim*endtime,-0.9*dim);
                glScaled(0.3,0.3,0.3);
                glCallList(obj1);
                glPopMatrix();
            }
            else if(position==2)
            {
                glPushMatrix();
                glTranslatef(0.5*asp*dim,-1.2*dim+0.1*dim*endtime,-0.3*dim);
                glRotatef(-15,0.0,1.0,0.0);
                glScaled(0.3,0.3,0.3);
                glCallList(obj1);
                glPopMatrix();
            }
            else if(position==3)
            {
                glPushMatrix();
                glTranslatef(0.5*asp*dim,-1.2*dim+0.1*dim*endtime,-0.9*dim);
                glScaled(0.3,0.3,0.3);
                glCallList(obj1);
                glPopMatrix();
            }
            else if(position==4)
            {
                glPushMatrix();
                glTranslatef(-0.5*asp*dim,-1.2*dim+0.1*dim*endtime,-0.3*dim);
                glRotatef(15,0.0,1.0,0.0);
                glScaled(0.3,0.3,0.3);
                glCallList(obj1);
                glPopMatrix();
            }
            else if(position==5)
            {
                glPushMatrix();
                glTranslatef(-0.5*asp*dim,-1.2*dim+0.1*dim*endtime,-0.9*dim);
                glScaled(0.3,0.3,0.3);
                glCallList(obj1);
                glPopMatrix();
            }

}

void snowman::timeOut()
{
    if (!timeout)
    {
         end=clock();
         endtime=(double)(end-start)/CLOCKS_PER_SEC;
         //printf("endtime=%f\n",endtime);
         //printf("timeout=%d\n",timeout);
         if(endtime>3.0)
         {
             timeout=1;
         }
    }
}

void snowman::clicked(int x,int y)
{
    //printf("x=%d y=%d\n",x,y);
    if(abs(x-300)<30 && abs(y-490)<60 && position==0)
        hit=1;
    else if(abs(x-180)<30 && abs(y-490)<60 && position==4)
        hit=1;
    else if(abs(x-420)<30 && abs(y-490)<60 && position==2)
        hit=1;
    else if(abs(x-220)<30 && abs(y-430)<60 && position==5)
        hit=1;
    else if(abs(x-300)<30 && abs(y-430)<60 && position==1)
        hit=1;
    else if(abs(x-380)<30 && abs(y-430)<60 && position==3)
        hit=1;
}
