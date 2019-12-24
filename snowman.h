#include <ctime>
#include <GL/glut.h>
#include <stdio.h>

#ifndef SNOWMAN_H
#define SNOWMAN_H
class snowman
{
    public:
        snowman(int time);
        void render(double asp,double dim,int obj);
        void timeOut();
        void clicked(int x,int y);
    private:
        int hit;
        int timeout;
        int position;
        clockid_t start;
        clockid_t end;
        double endtime;
        int Time;

};
#endif // SNOWMAN_H

