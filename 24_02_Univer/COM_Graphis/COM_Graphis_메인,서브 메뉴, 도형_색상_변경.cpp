//********** 메뉴,서브 메뉴,도형 색상 변경**********

//#include <gl/glut.h>					
//#include <gl/gl.h>						
//#include <gl/glu.h>
//
//GLboolean IsSphere = true;
//GLboolean Ishere = true;
//GLboolean IsSmall = true;
//GLboolean IsBig = true;
//
//int color = 0;
//int isR = 0;
//int isG = 0;
//int isB = 0;
//
//
//void MyDisplay() {
//    glClear(GL_COLOR_BUFFER_BIT);
//    glColor3f(0.5, 0.0, 0.5);
//    if(color == 0)
//        glColor3f(0.5, 0.5, 0.5);
//    else if(color ==1)
//        glColor3f(1, 0, 0);
//    else if(color ==2)
//        glColor3f(0, 1, 0);
//    else if(color ==3)
//        glColor3f(0, 0, 1);
//
//    if (IsSphere) {
//        if (IsSmall)
//            glutWireSphere(0.2, 15, 15);  // 작은 원구
//        else
//            glutWireSphere(0.4, 15, 15);  // 큰 원구
//    }
//    else if (Ishere) {
//        if (IsSmall)
//            glutWireTeapot(0.3);  // 작은 찻잔
//        else
//            glutWireTeapot(0.6);  // 큰 찾잔
//    }
//    else { 
//        if (IsSmall)
//            glutWireTorus(0.1, 0.3, 40, 20);  // 작은 원환체
//        else
//            glutWireTorus(0.2, 0.5, 40, 20);  // 큰 원환체
//    }
//
//    glFlush();
//}
//
//void MyMainMenu(int entryID) {
//    if (entryID == 1) {
//        IsSphere = true;				    //원구 그리기
//        Ishere = false;
//    }
//    else if (entryID == 2)
//    {
//        IsSphere = false;				    //원환체 그리기
//        Ishere = false;
//    }			    
//    else if (entryID == 3)
//    {
//        IsSphere = false;
//        Ishere = true;							//프로그램 종료
//    }
//    else if (entryID == 4)
//        exit(0);							//프로그램 종료
//    glutPostRedisplay();
//}
//
//void MySubMenu(int entryID) {
//    if (entryID == 1)
//    {
//        IsSmall = true;                //작은 크기로 그리기
//        IsBig = false;					
//    } 		    
//    else if (entryID == 2)
//    {
//        IsSmall = false;
//        IsBig = true;					//큰 크기로 그리기
//    }
//        glutPostRedisplay();
//}
//
//void MySubMenu2(int entryID) {
//    if (entryID == 1)
//        color = 1;					//색상 R로 바꾸기
//    else if (entryID == 2)
//        color = 2;					//색상 G로 바꾸기
//    else if (entryID == 3)
//        color = 3;					//색상 B로 바꾸기
//    glutPostRedisplay();
//}
//
//int main(int argc, char** argv) {
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_RGB);
//    glutInitWindowSize(300, 300);
//    glutInitWindowPosition(0, 0);
//    glutCreateWindow("OpenGL Example Drawing");
//
//    glClearColor(1.0, 1.0, 1.0, 1.0);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
//
//    GLint MySubMenuID = glutCreateMenu(MySubMenu);
//    glutAddMenuEntry("Small One", 1);
//    glutAddMenuEntry("Big One", 2);
//
//    GLint MySubMenuID2 = glutCreateMenu(MySubMenu2);
//    glutAddMenuEntry("R", 1);
//    glutAddMenuEntry("G", 2);
//    glutAddMenuEntry("B", 3);
//
//    GLint MyMainMenuID = glutCreateMenu(MyMainMenu);
//    glutAddMenuEntry("Draw Sphere", 1);
//    glutAddMenuEntry("Draw Torus", 2);
//    glutAddMenuEntry("Draw Teapot", 3);
//    glutAddSubMenu("Change Size", MySubMenuID);
//    glutAddSubMenu("Change Color", MySubMenuID2);
//    glutAddMenuEntry("Exit", 4);
//    glutAttachMenu(GLUT_RIGHT_BUTTON);
//
//    glutDisplayFunc(MyDisplay);
//
//    glutMainLoop();
//
//    return 0;
//}
