** 도형 2개 각 타이머 생성 후 움직이기

#include <gl/glut.h>					
#include <gl/gl.h>						
#include <gl/glu.h>	

//GLfloat Delta = 0.0;
//GLfloat Speed = 0.0001;  // 이동 속도 (양수일 때 오른쪽, 음수일 때 왼쪽)
GLfloat DeltaX = 0.0;
GLfloat DeltaY = 0.0;
GLfloat SpeedX = 0.0001;  // X축 이동 속도 (양수일 때 오른쪽, 음수일 때 왼쪽)
GLfloat SpeedY = 0.0001;  // Y축 이동 속도 (양수일 때 위쪽, 음수일 때 아래쪽)

void MyDisplay() {
   glClear(GL_COLOR_BUFFER_BIT);
   glBegin(GL_POLYGON);
   glColor3f(0.0, 0.5, 0.8);
   glVertex3f(-1.0 + DeltaX, -0.5, 0.0);
   glVertex3f(0.0 + DeltaX, -0.5, 0.0);
   glVertex3f(0.0 + DeltaX, 0.5, 0.0);
   glVertex3f(-1.0 + DeltaX, 0.5, 0.0);
   glEnd();

   glColor3f(0, 0, 1);
   glBegin(GL_POLYGON); // 점, 선, 다각형 **반시계 방향으로 테두리를 돌려라**
   glVertex3f(-0.5, -0.5 + DeltaY, 0.0); // 점
   glVertex3f(0.5, -0.5 + DeltaY, 0.0); // 점
   //glVertex3f(0.1, -0.2, 0.0); // 점
   //glVertex3f(0.0, 0.0, 0.0); // 점
   glVertex3f(0.5, 0.5 + DeltaY, 0.0); // 점
   glEnd();

   glutSwapBuffers();
}
void MyTimer(int Value) 
{ // Value가 타이머 번호
   if (Value == 3)
   {
       DeltaX = DeltaX + SpeedX;
   }
   else
   {
       DeltaY = DeltaY + SpeedY;
   }
   glutPostRedisplay();
   glutTimerFunc(10, MyTimer, Value);
}

void MyIdle() {
   DeltaX = DeltaX + SpeedX;  // 현재 방향으로 Delta 값을 증가

   // 화면 양 끝에 도달했는지 확인하고, 도달하면 반대 방향으로 전환
   if (DeltaX > 1.0 || DeltaX < 0.0) {
       SpeedX = -SpeedX;  // 방향 반전
   }

   // y축 이동
   DeltaY = DeltaY + SpeedY;
   if (DeltaY > 1.0 || DeltaY < -1.0) {
       SpeedY = -SpeedY;  // y축 방향 반전
   }

   glutPostRedisplay();
}

int main(int argc, char** argv) {
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
   glutInitWindowSize(300, 300);
   glutInitWindowPosition(0, 0);
   glutCreateWindow("OpenGL Drawing Example");

   glClearColor(1.0, 1.0, 1.0, 1.0);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(-1.0, 1.0, -1.0, 1.0, 1.0, -1.0);

   glutDisplayFunc(MyDisplay);
   glutIdleFunc(MyIdle);
   glutTimerFunc(40, MyTimer, 3); // 3번 시계
   glutTimerFunc(20, MyTimer, 5); // 5번 시계

   glutMainLoop();
   return 0;
}
