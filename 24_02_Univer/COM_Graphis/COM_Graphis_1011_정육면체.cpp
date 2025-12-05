//// 5-13 정점배열
//
//#include <gl/glut.h>					
//#include <gl/gl.h>						
//#include <gl/glu.h>
//
//GLfloat MyVertices[8][3] = { {-0.25,-0.25,0.25}, {-0.25,0.25,0.25}, {0.25,0.25,0.25}, {0.25,-0.25,0.25},
//{-0.25,-0.25,-0.25}, {-0.25,0.25,-0.25}, {0.25,0.25,-0.25}, {0.25,-0.25,-0.25} };
////GLfloat MyVertices[8][3] = {{-0.25,-0.25,-0.25}, {-0.25,0.25,-0.25}, {0.25,0.25,-0.25}, {0.25,-0.25,-0.25}, 
////{-0.25,-0.25,0.25}, {-0.25,0.25,0.25}, {0.25,0.25,0.25}, {0.25,-0.25,0.25}};
//
//// 앞장 뒷장 색상 
////GLfloat MyColors[8][3]={{0.2,0.2,0.2}, {1.0,0.0,0.0}, {1.0, 1.0, 0.0}, {0.0,1.0,0.0}, {0.0,0.0,1.0}, 
////{1.0,0.0,1.0}, {1.0,1.0,1.0}, {0.0,1.0,1.0}};
//GLfloat MyColors[8][3] = { {1.0,0.0,0.0}, {0.8,0.8,0.8}, {0.0,1.0,0.0}, {0.8,0.8,0.8}, {0.2,0.2,0.2},
//{0.0,0.0,1.0}, {0.2,0.2,0.2}, {0.2,0.2,0.2} };
//
//GLubyte MyVertexList[24] = { 0,3,2,1, 2,3,7,6, 0,4,7,3, 1,2,6,5, 4,5,6,7, 0,1,5,4 }; //ori
////GLubyte MyVertexList[24]={0,3,2,1, 2,3,7,6, 1,2,6,5, 0,4,7,3, 4,5,6,7, 0,1,5,4};
////GLubyte MyVertexList[24]={0,4,7,3, 4,5,6,7, 0,1,5,4, 0,3,2,1, 2,3,7,6, 1,2,6,5};
//
///*
//        5      6
//
//        4      7
//    2      1
//
//    0      3
//    front : 0   back : 4   left : 5    right : 1    top : 3    bottom : 2
//*/
//
//
//void MyDisplay() {
//    //배경
//    glClear(GL_COLOR_BUFFER_BIT);
//
//    glFrontFace(GL_CCW);
//    //glEnable(GL_CULL_FACE);
//    //glCullFace(GL_FRONT);//GL_BACK);//FRONT);
//    //glCullFace(GL_BACK);
//
//    //glPolygonMode(GL_FRONT, GL_FILL);
//    //glPolygonMode(GL_BACK, GL_LINE);
//
//    //배열 사용 선언
//    glEnableClientState(GL_COLOR_ARRAY);
//    glEnableClientState(GL_VERTEX_ARRAY);
//
//    glColorPointer(3, GL_FLOAT, 0, MyColors);
//    glVertexPointer(3, GL_FLOAT, 0, MyVertices);
//
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//    //gluLookAt(0,0,1,   0,0,0,   0,1,0);
//    //glRotatef(30.0, 1.0, .0, .0);
//    glRotatef(45.0, 1.0, 1.0, 1.0);
//    //for(GLint i = 0; i < 6; i++) 					
//    GLint i = 0;
//    i = 0;
//    glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, &MyVertexList[4 * i]);
//    i = 3;
//    glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, &MyVertexList[4 * i]);
//    i = 1;
//    //glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, &MyVertexList[4*i]);
//    i = 2;
//    //glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, &MyVertexList[4*i]);
//    i = 2;
//    //glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, &MyVertexList[4*i]);
//
//    i = 4;
//    //glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, &MyVertexList[4 * i]);
//
//    i = 5;
//    glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, &MyVertexList[4*i]);
//
//    glFlush();
//}
//
//int main(int argc, char** argv) {
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_RGB);
//    glutInitWindowSize(300, 300);
//    glutInitWindowPosition(0, 0);
//    glutCreateWindow("OpenGL Drawing Example");
//    glClearColor(1.0, 1.0, 1.0, 1.0);
//
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
//
//    glutDisplayFunc(MyDisplay);
//    glutMainLoop();
//    return 0;
//}
//
//
//
////glViewport(0, 0, 300, 300);  
//
///*glColor3f(1.0, 1.0, 0.0);
//glBegin(GL_POLYGON);
//    glVertex3fv(MyVertices[0]);
//    glVertex3fv(MyVertices[3]);
//    glVertex3fv(MyVertices[2]);
//    glVertex3fv(MyVertices[1]);
//glEnd();
//*/


#include <gl/glut.h>					
#include <gl/gl.h>						
#include <gl/glu.h>	
int MyListID, MyListID2, MyListID3;

void MyCreateList() {
    MyListID = glGenLists(2);
    glNewList(MyListID, GL_COMPILE);
    glBegin(GL_POLYGON);
    glColor3f(0.5, 0.5, 0.5);
    glVertex3f(-0.5, -0.5, 0.0);
    glVertex3f(0.5, -0.5, 0.0);
    glVertex3f(0.5, 0.5, 0.0);
    glVertex3f(-0.5, 0.5, 0.0);
    glEnd();
    glEndList();

    //MyListID2 = glGenLists(2);
    MyListID2 = MyListID + 1;
    glNewList(MyListID2, GL_COMPILE);
    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.0, 0.5);
    glVertex3f(-0.2, -0.5, 0.0);
    glVertex3f(0.8, -0.5, 0.0);
    glVertex3f(0.8, 0.5, 0.0);
    glVertex3f(-0.2, 0.5, 0.0);
    glEnd();
    glEndList();

    //ID+1 더하면 생성가능 밑에 추가 필수
    MyListID3 = MyListID + 2;
    glNewList(MyListID3, GL_COMPILE);
    glBegin(GL_POLYGON);
    glColor3f(0.5, 0.0, 0.0);
    glVertex3f(-0.1, -0.5, 0.0);
    glVertex3f(0.8, -0.5, 0.0);
    glVertex3f(0.8, 0.5, 0.0);
    glVertex3f(-0.1, 0.5, 0.0);
    glEnd();
    glEndList();
}

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    glViewport(0, 0, 300, 300);
    glCallList(MyListID);
    glCallList(MyListID2);
    glCallList(MyListID3);  // 이부분
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(300, 300);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("OpenGL Example Drawing");
    glClearColor(1.0, 1.0, 1.0, 1.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, 1.0, -1.0);

    glutDisplayFunc(MyDisplay);
    MyCreateList();

    glutMainLoop();
    return 0;
}