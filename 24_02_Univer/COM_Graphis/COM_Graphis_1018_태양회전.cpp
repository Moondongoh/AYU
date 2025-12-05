// 6-6
#include <gl/glut.h>
#include <gl/gl.h>
#include <gl/glu.h>
static int Day = 0, Time = 0;
void MyDisplay( ){
   glClear (GL_COLOR_BUFFER_BIT);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity( );

   glColor3f (1.0, 0.0, 0.0);
   glutWireSphere(0.2, 20, 16);  //Sun
   
   glPushMatrix( );							
       glRotatef ((GLfloat) Day, 0.0, 0.0, 1.0);				
       glTranslatef (0.7, 0.0, 0.0);  /////////////////						
       glRotatef ((GLfloat) Time, 0.0, 0.0, 1.0);		
       glColor3f (0.0, 1.0, 0.0);
       glutWireSphere(0.1, 10, 8);// Earth
	   
       //glPushMatrix( );						
           glRotatef ((GLfloat) Time, 0.0, 0.0, 1.0);			
           glTranslatef (0.2, 0.0, 0.0); /////////////////				
           glColor3f (0.0, 0.0, 1.0);
           glutWireSphere(0.04, 10, 8);  // Moon
			glBegin(GL_LINES);
				glVertex3f(0.0, 0.0, 0.0);
				glVertex3f(0.5, 0.5, 0.0);
			glEnd();

       //glPopMatrix( );

	   glColor3f (1.0, 0.0, 1.0);    //CTM
       glutWireSphere(0.05, 20, 16);  // ?????

		glBegin(GL_LINES);
			glVertex3f(0.0, 0.0, 0.0); // 회전 선
			glVertex3f(0.5, 0.5, 0.0);
		glEnd();

   glPopMatrix();

   //glColor3f (0.0, 1.0, 1.0);     //CTM
   //glutWireSphere(0.02, 20, 16);

   glutSwapBuffers();
}

void MyKeyboard (unsigned char key, int x, int y){
   switch (key) {
      case 'd':
         Day = (Day + 90) % 360;
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

int main(int argc, char** argv){
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize (500, 500); 
   glutInitWindowPosition (0, 0);
   glutCreateWindow("OpenGL Sample Drawing"); 
   glClearColor (1.0, 1.0, 1.0, 1.0);

   glMatrixMode(GL_PROJECTION);    
   glLoadIdentity( );    
   glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);  

   glutDisplayFunc(MyDisplay); 
   glutKeyboardFunc(MyKeyboard);

   glutMainLoop( );
   return 0;
}