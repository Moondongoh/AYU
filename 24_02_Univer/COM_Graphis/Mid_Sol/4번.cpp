#include <gl/glut.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <string.h>
static int Day = 0, Time = 0;
float rotationAngle = 0.0f;
bool Mode = false;
float colortmp = 0.1;
float colorarr[] = { 1.0, 0.0 };
int even = 0;


void drawNumber(const char* number, float x, float y) {
   glColor3f(0.0f, 0.0f, 0.0f);  // 검정색
   glRasterPos2f(x, y);
   for (int i = 0; i < strlen(number); i++) {
       glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, number[i]);
   }
}

void MyDisplay() {
   glClear(GL_COLOR_BUFFER_BIT);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   glPushMatrix();
   glRotatef(Time, 0.0f, 0.0f, 1.0f);
   glBegin(GL_LINES);
   glColor3f(0.1, 0.0, 0.0);
   glVertex2f(0.0, 0.0);
   glVertex2f(0.0, 0.4);
   glEnd();
   glPopMatrix();
   glPushMatrix();
   glRotatef(Day, 0.0f, 0.0f, 1.0f);
   glBegin(GL_LINES);
   glColor3f(1.0, 0.0, colortmp);
   glVertex2f(0.0, 0.0);
   glVertex2f(0.0, 0.7);
   glEnd();
   glPopMatrix();
   glBegin(GL_LINE_LOOP);
   glVertex2f(-0.7f, -0.7f);
   glVertex2f(0.7f, -0.7f);
   glVertex2f(0.7f, 0.7f);
   glVertex2f(-0.7f, 0.7f);
   glEnd();

   drawNumber("12", -0.1f, 0.6f);  // 상단
   drawNumber("3", 0.6f, -0.05f);   // 우측
   drawNumber("6", -0.05f, -0.65f); // 하단
   drawNumber("9", -0.65f, -0.05f); // 좌측

   glutSwapBuffers();
}

void MyKeyboard(unsigned char key, int x, int y) {
   switch (key) {
   case 'd':
       if (Day == -270) {
           Time = (Time - 90) % 360;
       }
       Day = (Day - 90) % 360;
       glutPostRedisplay();
       break;
   case 't':
       Time = (Time + 45) % 360;
       glutPostRedisplay();
       break;
   default:
       break;
   }
}

void MyTimer(int Value) {
   if (Mode == true) {
       even += 1;
       if (even == 2) {
           if (colortmp == colorarr[0])
               colortmp = colorarr[1];
           else colortmp = colorarr[0];
           even = 0;

       }
       else {

       }
       if (Day == -315) {
           Time = (Time - 90) % 360;
       }
       Day = (Day - 45) % 360;
   }
   glutPostRedisplay();
   glutTimerFunc(500, MyTimer, 1);
}

void MyMainMenu(int entryID) {
   if (entryID == 1)
       Mode = true;
   else if (entryID == 2)
       Mode = false;
   else if (entryID == 3) {
       Time = 0;
       Day = 0;
   }

   glutPostRedisplay();
}

int main(int argc, char** argv) {
   int window_width = 320;
   int window_height = 320;
   //int screen_width = glutGet(GLUT_SCREEN_WIDTH);
   //int screen_height = glutGet(GLUT_SCREEN_HEIGHT);
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize(500, 500);
   glutInitWindowPosition(1430, 0);
   glutCreateWindow("Moon");
   glClearColor(1.0, 1.0, 1.0, 1.0);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

   GLint MyMainMenuID = glutCreateMenu(MyMainMenu);
   glutAddMenuEntry("start", 1);
   glutAddMenuEntry("stop", 2);
   glutAddMenuEntry("init", 3);
   glutAttachMenu(GLUT_RIGHT_BUTTON);


   glutDisplayFunc(MyDisplay);
   glutKeyboardFunc(MyKeyboard);

   glutTimerFunc(500, MyTimer, 3);


   glutMainLoop();
   return 0;
}
