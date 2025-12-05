//#include <gl/glut.h>						
//#include <gl/gl.h>							
//#include <gl/glu.h>						
//
//void MyDisplay() {
//    glClear(GL_COLOR_BUFFER_BIT);
//    
//
//    glColor3f(0, 1, 1);
//    glPointSize(5);
//    glBegin(GL_POLYGON); // 점, 선, 다각형 **반시계 방향으로 테두리를 돌려라**
//    glVertex3f(-0.5, -0.3, 0.0); // 점
//    glVertex3f(0.5, -0.3, 0.0); // 점
//    glVertex3f(0.5, 0.3, 0.0); // 점
//    //glVertex3f(0.0, 0.0, 0.0); // 점
//    glVertex3f(-0.5, 0.3, 0.0); // 점
//    glEnd();
//     // 프로그램 상에는 그려졌지만 보이는 화면에는 안보임 paint기능
//
//    glColor3f(1, 0, 1);
//
//    glBegin(GL_POLYGON); // 점, 선, 다각형 **반시계 방향으로 테두리를 돌려라**
//    glVertex3f(-0.7, -0.01, 0.0); // 점
//    glVertex3f(0.7, -0.01, 0.0); // 점
//    glVertex3f(0.5, 0.5, 0.0); // 점
//    glVertex3f(0.5, 0.5, 0.0); // 점
//    glVertex3f(-0.5, 0.5, 0.0); // 점
//    glEnd();
//
//    glColor3f(0, 0, 1);
//    glBegin(GL_POLYGON); // 점, 선, 다각형 **반시계 방향으로 테두리를 돌려라**
//    glVertex3f(-0.1, -0.1, 0.0); // 점
//    glVertex3f(0.1, -0.1, 0.0); // 점
//    glVertex3f(0.1, -0.2, 0.0); // 점
//    //glVertex3f(0.0, 0.0, 0.0); // 점
//    glVertex3f(-0.1, -0.2, 0.0); // 점
//    glEnd();
//    glFlush();
//}
//
//int main(int argc, char** argv) {
//    glutInit(&argc, argv); // 초기화
//    glutCreateWindow("OpenGL Drawing Example"); // 창 이름 설정
//    
//    // scene
//
//    glutDisplayFunc(MyDisplay);
//
//    glutMainLoop();
//    return 0;
//}


//#include <gl\GL.h>
//#include <gl\GLU.h>

#include <gl/glut.h>						
#include <gl/gl.h>							
#include <gl/glu.h>		

void MyDisplay() {					//디스플레이 콜백함수	
    glClear(GL_COLOR_BUFFER_BIT);	//GL 상태변수 설정
    glViewport(0, 0, 300, 300);
    glColor3f(1.0, 1.0, 1.0);

    glBegin(GL_POLYGON);       	 	//입력 기본요소 정의	
    glVertex3f(-0.5, -0.5, 0.0);
    glVertex3f(0.5, -0.5, 0.0);
    glVertex3f(0.5, 0.5, 0.0);
    glVertex3f(-0.5, 0.5, 0.0);
    glEnd();

    //glColor3f(1.0, .0, 1.0); 				
    //glutWireTeapot(0.9);	

    glFlush();
}

int main(int argc, char** argv) {
    int i;

    glutInit(&argc, argv); 			//GLUT 윈도우 함수
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(300, 300);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("OpenGL Sample Drawing");
    glClearColor(0.0, 0.0, 0.0, 0.0);	//GL 상태변수 설정

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

    glutDisplayFunc(MyDisplay);  	  	//GLUT 콜백함수 등록

    glutMainLoop();					//이벤트 루프 진입
    return 0;
}
