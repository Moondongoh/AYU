// 마우스 이용해 직사각형 그리고 도형 색 바꾸기

//#include <gl/glut.h>						
//#include <gl/gl.h>							
//#include <gl/glu.h>	
//
//int color = 0;
//
//GLint TopLeftX, TopLeftY, BottomRightX, BottomRightY;
//
//void MyDisplay() {
//    glViewport(0, 0, 300, 300);
//    glClear(GL_COLOR_BUFFER_BIT);
//   
//    if (color == 1)
//       glColor3f(1.0, 0, 0);
//    else if (color == 2)
//       glColor3f(0, 1.0, 0);
//    else if (color == 3)
//       glColor3f(0, 0, 1.0);
//    else
//       glColor3f(0.5, 0.5, 0.5);           // 값이 모두 같다면 "회색"
//
//    glBegin(GL_POLYGON);
//    glVertex3f(TopLeftX / 300.0, (300 - TopLeftY) / 300.0, 0.0);
//    glVertex3f(TopLeftX / 300.0, (300 - BottomRightY) / 300.0, 0.0);
//    glVertex3f(BottomRightX / 300.0, (300 - BottomRightY) / 300.0, 0.0);
//    glVertex3f(BottomRightX / 300.0, (300 - TopLeftY) / 300.0, 0.0);
//    glEnd();
//
//    //glBegin(GL_POINTS);
//
//       /*
//       glVertex3f(TopLeftX, (300-TopLeftY), 0.0);
//       glVertex3f(TopLeftX+1, (300-TopLeftY), 0.0);
//       glVertex3f(TopLeftX, (300-TopLeftY)+1, 0.0);
//       glVertex3f(TopLeftX+1, (300-TopLeftY)+1, 0.0);
//       */
//       /*glVertex3f(TopLeftX/300.0, (300-BottomRightY)/300.0, 0.0);
//       glVertex3f(TopLeftX/300.0, (300-TopLeftY)/300.0, 0.0);
//       glVertex3f(TopLeftX/300.0+0.005, (300-TopLeftY)/300.0, 0.0);
//       glVertex3f(TopLeftX/300.0, (300-TopLeftY)/300.0+0.005, 0.0);
//       glVertex3f(TopLeftX/300.0+0.005, (300-TopLeftY)/300.0+0.005, 0.0);
//       glVertex3f(TopLeftX/300.0, (300-BottomRightY)/300.0, 0.0);
//       glVertex3f(BottomRightX/300.0, (300-BottomRightY)/300.0, 0.0);
//       glVertex3f(BottomRightX/300.0, (300-TopLeftY)/300.0, 0.0); */
//       //glEnd( );
//
//    glFlush();
//}
//
//void MyMouseClick(GLint Button, GLint State, GLint X, GLint Y) {
//    if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN) {
//        TopLeftX = X;
//        TopLeftY = Y;
//    }
//}
//
//void MyMouseMove(GLint X, GLint Y) {
//    BottomRightX = X;
//    BottomRightY = Y;
//    glutPostRedisplay();
//}
//
//void MyKeyboard(unsigned char KeyPressed, int X, int Y) {
//        switch (KeyPressed) {
//        case 'r':
//            color = 1; break;
//        case 'g':
//            color = 2; break;
//        case 27:       			//'esc' 키의 아스키 코드 값
//            exit(0); break;
//        case 'b':
//            color = 3; break;
//        }
//        glutPostRedisplay();
//    }
//
//int main(int argc, char** argv) {
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_RGB);
//    glutInitWindowSize(300, 300);
//    glutInitWindowPosition(0, 0);
//    glutCreateWindow("OpenGL Drawing Example");
//
//    glClearColor(1.0, 1.0, 1.0, 1.0);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//
//    //glOrtho(0.0, 300.0, 0.0, 300.0, -1.0, 1.0);
//    //glOrtho(-1.0, 1.0,   -1.0, 1.0,   -1.0, 1.0); // Ori
//    glOrtho(0.0, 1.0, 0.0, 1.0, 0.0, 1.0);
//
//    glutDisplayFunc(MyDisplay);
//    glutMouseFunc(MyMouseClick);
//    glutKeyboardFunc(MyKeyboard);
//    glutMotionFunc(MyMouseMove); //PassiveMotion사용시 클릭을 놔야지 그려짐 but 이미지가 계속 갱신
//
//    glutMainLoop();
//    return 0;
//}