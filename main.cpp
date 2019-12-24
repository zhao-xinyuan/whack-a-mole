#include "CSCIx229.h"
#include "snowman.h"
#include <particalsystem.h>
#include <ctime>
#include "skybox.h"
int axes=1;       //  Display axes
int mode=0;       //  Shader mode
int move=0;       //  Move light
int proj=1;       //  Projection type
int th=0;         //  Azimuth of view angle
int ph=0;         //  Elevation of view angle
int fov=90;       //  Field of view (for perspective)
double spc=1;     //  Specular intensity
double asp=1;     //  Aspect ratio
double dim=3.0;   //  Size of world
int zh=45;        //  Light azimuth
float RGBA[4] = {1,1,1,1};  //  Colors
int obj,obj1,obj2,obj3,obj4;
unsigned int texture[3];
float scale[10];
Snow ps;
Fire fs;
skybox box;
snowman sm(50);
snowman sm1(100);
//Draw the trees;
void tree()
{
    glPushMatrix();
    glTranslatef(0.8*asp*dim,-0.2*dim,-0.3*dim);
    glScalef(0.2,0.2,0.2);
    glCallList(obj2);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.8*asp*dim,-0.3*dim,-0.6*dim);
    glScalef(0.2,0.2,0.2);
    glCallList(obj3);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.8*asp*dim,-0.3*dim,-0.9*dim);
    glScalef(0.2,0.2,0.2);
    glCallList(obj2);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.9*asp*dim,-0.7*dim,-0.6*dim);
    glScalef(0.4,0.4,0.4);
    glCallList(obj2);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-0.9*asp*dim,-0.7*dim,-0.9*dim);
    glScalef(0.4,0.4,0.4);
    glCallList(obj2);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-0.8*asp*dim,-0.3*dim,-0.05*dim);
    glScalef(0.2,0.2,0.2);
    glCallList(obj2);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-0.8*asp*dim,-0.4*dim,-0.2*dim);
    glScalef(0.2,0.2,0.2);
    glCallList(obj2);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-0.8*asp*dim,-0.2*dim,-0.3*dim);
    glScalef(0.2,0.2,0.2);
    glCallList(obj3);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-0.8*asp*dim,-0.3*dim,-0.6*dim);
    glScalef(0.2,0.2,0.2);
    glCallList(obj2);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-0.8*asp*dim,-0.3*dim,-0.9*dim);
    glScalef(0.2,0.2,0.2);
    glCallList(obj3);
    glPopMatrix();
}
/*
 *  OpenGL (GLUT) calls this routine to display the scene
 */
void display()
{
   //  Erase the window and the depth buffer
   float Ambient[]  = {0.3,0.3,0.3,1.0};
   float Diffuse[] = {1.0,1.0,1.0,1.0};
   float Specular[] = {1.0,1.0,1.0,1.0};
   float Position[] = {-0.5*Sin(zh)*asp*dim,0.707*asp*dim*Cos(zh),0.5*Sin(zh)*asp*dim,0.0};
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   //  Enable Z-buffering in OpenGL
   glEnable(GL_DEPTH_TEST);
   //  Undo previous transformations
   glLoadIdentity();
   //  Perspective - set eye position
   if (proj)
   {
      double Ex = -dim*Sin(th)*Cos(ph);
      double Ey = +dim        *Sin(ph);
      double Ez = +dim*Cos(th)*Cos(ph);
      gluLookAt(Ex,Ey,Ez,0.0,0.0,0.0,0,Cos(ph),0);
   }
   //  Orthogonal - set world orientation
   else
   {
      glRotatef(ph,1,0,0);
      glRotatef(th,0,1,0);
   }
   // Set up lighting
   glEnable(GL_NORMALIZE);
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glLightfv(GL_LIGHT0,GL_AMBIENT ,Ambient);
   glLightfv(GL_LIGHT0,GL_DIFFUSE ,Diffuse);
   glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);
   glLightfv(GL_LIGHT0,GL_POSITION,Position);
   // Draw the skybox
   glColor3f(1.0,1.0,1.0);
   glEnable(GL_COLOR_MATERIAL);
   box.skyboxRender(dim,asp);
   glDisable(GL_COLOR_MATERIAL);
   //Draw the snow
   ps.snowRender(th);
   // Draw the tree
   tree();
   glPushMatrix();
   glTranslatef(0.0,-0.2*dim,0.0);
   glScaled(0.03,0.03,0.03);
   glCallList(obj);
   glPopMatrix();
   //Draw the snowman
   sm.render(asp,dim,obj1);
   sm1.render(asp,dim,obj1);
   glPushMatrix();
   //Draw the fire
   glEnable(GL_COLOR_MATERIAL);
   glTranslatef(asp*dim*0.7,-0.5*dim,-0.3*dim);
   glScalef(0.1,0.1,0.1);
   glCallList(obj4);
   glTranslatef(0.0,8.0,0.0);
   glScalef(0.8,0.8,0.8);
   fs.fireRender(th);
   glDisable(GL_COLOR_MATERIAL);
   glPopMatrix();
   glDisable(GL_LIGHTING);
   //  Render the scene and make it visible
   ErrCheck("display");
   glFlush();
   glutSwapBuffers();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void idle()
{
   //  Elapsed time in seconds
   double t = glutGet(GLUT_ELAPSED_TIME)/10000.0;
   if (move) zh = fmod(90*t,360.0);
   ps.snowSimulate(0.005,asp,dim);
   fs.fireSimulate(0.0,0.0,0.0);
   //  Tell GLUT it is necessary to redisplay the scene
   sm.timeOut();
   sm1.timeOut();
   glutPostRedisplay();
}



/*
 *  GLUT calls this routine when a key is pressed
 */
void key(unsigned char ch,int x,int y)
{
   //  Exit on ESC
   if (ch == 27)
      exit(0);
   //  Reset view angle
   //  Toggle light movement
   else if (ch == 's' || ch == 'S')
      move = 1-move;
   //  Move light
   else if (ch == '[')
      zh -= 1;
   else if (ch == ']')
      zh += 1;
   else if (ch == 'd')
   //  Reproject
   Project(proj?fov:0,asp,dim);
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void reshape(int width,int height)
{
   //  Ratio of the width to the height of the window
   asp = (height>0) ? (double)width/height : 1;
   //  Set the viewport to the entire window
   glViewport(0,0, width,height);
   //  Set projection
   Project(proj?fov:0,asp,dim);
}
void mouse(int button,int state,int x,int y)
{
    if(button==GLUT_LEFT_BUTTON)
    {
        if(state==GLUT_DOWN)
        {
            sm.clicked(x,y);
            sm1.clicked(x,y);
        }
        glutPostRedisplay();
    }
}
/*
 *  Start up GLUT and tell it what to do
 */
int main(int argc,char* argv[])
{
   //  Initialize GLUT
   glutInit(&argc,argv);
   //  Request double buffered, true color window with Z buffering at 600x600
   glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
   glutInitWindowSize(600,600);
   glutCreateWindow("Zhao Xinyuan");
   //  Set callbacks
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(key);
   glutMouseFunc(mouse);
   glutIdleFunc(idle);
   //  Pass control to GLUT so it can interact with the user
   obj=LoadOBJ("castle.obj");
   obj1=LoadOBJ("snowman.obj");
   obj2=LoadOBJ("tree1.obj");
   obj3=LoadOBJ("tree2.obj");
   obj4=LoadOBJ("base.obj");
   ps=Snow(500,-10);
   fs=Fire(10000,0.0);
   ps.initSnow(asp,dim);
   fs.initFire(0.0,0.0,0.0);
   box.bindtexture();
   ErrCheck("init");
   glutMainLoop();
   return 0;
}
