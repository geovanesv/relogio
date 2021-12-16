
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include<string.h>

// define glu objects
int about_int=0;

int M_TWOPI=0;


GLUquadricObj *Cylinder;
GLUquadricObj *Disk;

struct tm *newtime;
time_t ltime;

GLfloat rx, ry, rz, angle;

// iluminação
GLfloat LightAmbient[]= { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat LightDiffuse[]= { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat LightPosition[]= { 5.0f, 25.0f, 15.0f, 1.0f };
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };

static int light_state = 1; // light on = 1, light off = 0
static int view_state = 1; // Ortho view = 1, Perspective = 0


void Sprint( int x, int y, char *st)
{
    int l,i;

    l=strlen( st );
    glRasterPos3i( x, y, -1);
    for( i=0; i < l; i++)
        {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, st[i]);
    }

}

static void TimeEvent(int te)
{
    /*int timent;
    int i;

    rx = 30 * cos( angle );
    ry = 30 * sin( angle );
    rz = 30 * cos( angle );
    angle += 0.01;
    if (angle >M_TWOPI) angle = 0;
    //M_TWOPI
*/
    glutPostRedisplay();
    glutTimerFunc( 100, TimeEvent, 1);
}

void init(void)
{


   glClearColor (0.0, 0.0, 0.0, 0.0);
   glShadeModel (GL_SMOOTH);
   glEnable(GL_DEPTH_TEST);
   // A iluminação é adicionada à cena
   glLightfv(GL_LIGHT1 ,GL_AMBIENT, LightAmbient);
   glLightfv(GL_LIGHT1 ,GL_DIFFUSE, LightDiffuse);
   glLightfv(GL_LIGHT1 ,GL_POSITION, LightPosition);
   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT1);


  Cylinder = gluNewQuadric();
   gluQuadricDrawStyle( Cylinder, GLU_FILL);
   gluQuadricNormals( Cylinder, GLU_SMOOTH);
   gluQuadricOrientation( Cylinder, GLU_OUTSIDE);
   gluQuadricTexture( Cylinder, GL_TRUE);

   Disk = gluNewQuadric();
   gluQuadricDrawStyle( Disk, GLU_FILL);
   gluQuadricNormals( Disk, GLU_SMOOTH);
   gluQuadricOrientation( Disk, GLU_OUTSIDE);
   gluQuadricTexture( Disk, GL_TRUE);


}

void Draw_engrenagem( void )
{

    int i;
    glPushMatrix();
    //gluCylinder(Cylinder, 2.5, 2.5, 1, 16, 16);
    gluDisk(Disk, 0, 0.9, 32, 16);
    glTranslatef(0,0,1);
    //gluDisk(Disk, 0, 2.5, 32, 16);
    glPopMatrix();
}


void Draw_relogio( GLfloat cx, GLfloat cy, GLfloat cz )
{

  int hour_ticks , sec_ticks;
  glPushMatrix();

  glTranslatef(cx,cy,cz);
  glRotatef( 180, 1.0, 0.0, 0.0);


  glPushMatrix(); // Desenhe um grande cubo
  glColor3f(1.0, 1.0, 1.0);
  glTranslatef( 0.0, 0.0, 6.0);
  glutWireCube(15.0);
  glPopMatrix();

  glPushMatrix(); // Draw clock face
  glTranslatef( 0, 0, 1.0);
  gluDisk(Disk, 0, 6.75, 32, 16);

  glPopMatrix();

  glPushMatrix();// Desenho ponteiro horas
  glColor3f(0.0, 0.0, 1.0);
  glTranslatef( 0, 0, 0.0);
  glRotatef( (360/12) * newtime->tm_hour  + (360/60) * (60 / (newtime->tm_min+1)), 0.0, 0.0, 1.0);
  glPushMatrix();
  glTranslatef(0.0, 0.0, 2.0);
  Draw_engrenagem();
  glPopMatrix();
  glRotatef( 90, 1.0, 0.0, 0.0);
  gluCylinder(Cylinder, 0.75, 0, 4, 16, 16);
  glPopMatrix();

  glPushMatrix();// Deseho ponteiro minutos
  glColor3f(1.0, 0.0, 0.0);
  glTranslatef( 0, 0, 0.0);
  glRotatef( (360/60) * newtime->tm_min, 0.0, 0.0, 1.0);
  glPushMatrix();
  glTranslatef(0.0, 0.0, 3.0);
  glScalef(0.5, 0.5, 1.0);
  Draw_engrenagem();
  glPopMatrix();
  glRotatef( 90, 1.0, 0.0, 0.0);
  gluCylinder(Cylinder, 0.5, 0, 6, 16, 16);
  glPopMatrix();

  glPushMatrix();// desenho ponteiro segundos
  glColor3f(1.0, 0.0, 0.0);
  glTranslatef( 0, 0, -0.0);
  glRotatef( (360/60) * newtime->tm_sec, 0.0, 0.0, 1.0);
  glPushMatrix();
  glTranslatef(0.0, 0.0, 4.0);
  glScalef(0.25, 0.25, 1.0);
  Draw_engrenagem();
  glPopMatrix();
  glRotatef( 90, 1.0, 0.0, 0.0);
  gluCylinder(Cylinder, 0.25, 0, 6, 16, 16);
  glPopMatrix();

//pontos horas
  for(hour_ticks = 0; hour_ticks < 12; hour_ticks++)
      {
      glPushMatrix();
      glColor3f(0.0, 0.5, 0.5); 
      glTranslatef(0.0, 0.0, 0.0);
      glRotatef( (360/12) * hour_ticks, 0.0, 0.0, 1.0);
      glTranslatef( 6.0, 0.0, 0.0);
      glutSolidCube(0.5);

      glPopMatrix();
  }

//pontos segundos
  for(sec_ticks = 0; sec_ticks < 60; sec_ticks++)
     {
      glPushMatrix();
      glTranslatef(0.0, 0.0, 0.0);
      glRotatef( (360/60) * sec_ticks, 0.0, 0.0, 1.0);
      glTranslatef(6.0, 0.0, 0.0);
      glutSolidCube(0.25);
      glPopMatrix();
    }

  glPopMatrix();
}

void num()
{
    if(view_state == 1){
      glColor3f( 0.0, 0.0, 1.0);
      Sprint(-5.9,-0.9,"9"); 
      Sprint(-0.2,-5.9,"6");
      Sprint(-0.95,5.7,"12");
      Sprint(5.8,-0.2,"3");
   }
 }

void display(void)
{

  time(&ltime); 
  newtime = localtime(&ltime); // Converter para a hora local

  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


  glMatrixMode (GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-8.0, 8.0, -8.0, 8.0, 1.0, 60.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glDisable(GL_LIGHTING);
  glDisable(GL_COLOR_MATERIAL);

  glColor3f( 1.0, 1.0, 1.0);

   Sprint(-4,-8, asctime(newtime));

  if (view_state == 0)
     {
     glMatrixMode (GL_PROJECTION);
     glLoadIdentity();

     gluPerspective(60.0, 1, 1.0, 60.0);
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
     gluLookAt( rx, 0.0, rz, 0.0, 0.0, -14.0, 0, 1, 0);
     }

    if (light_state == 1)
      {
       glEnable(GL_LIGHTING);
       glEnable(GL_COLOR_MATERIAL);  // Enable for lighing
      }else
      {
      glDisable(GL_LIGHTING);
      glDisable(GL_COLOR_MATERIAL);  // Disable for no lighing
  }
  
Draw_relogio( 0.0, 0.0, -14.0);

num();

glutSwapBuffers();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (500, 500);
   glutInitWindowPosition (10, 10);
   glutCreateWindow (argv[0]);
   glutSetWindowTitle("Relogio");
   init ();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutTimerFunc( 10, TimeEvent, 1);
   glutMainLoop();
   return 0;
}
