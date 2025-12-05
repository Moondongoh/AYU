#include <gl/glut.h>					
#include <gl/gl.h>						
#include <gl/glu.h>	

GLfloat Delta = 0.0;
GLfloat Speed = 0.0001;  // 이동 속도 (양수일 때 오른쪽, 음수일 때 왼쪽)

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.5, 0.8);
    glVertex3f(-1.0 + Delta, -0.5, 0.0);
    glVertex3f(0.0 + Delta, -0.5, 0.0);
    glVertex3f(0.0 + Delta, 0.5, 0.0);
    glVertex3f(-1.0 + Delta, 0.5, 0.0);
    glEnd();
    glutSwapBuffers();
}

void MyIdle() {
    Delta = Delta + Speed;  // 현재 방향으로 Delta 값을 증가

    // 화면 양 끝에 도달했는지 확인하고, 도달하면 반대 방향으로 전환
    if (Delta > 1.0 || Delta < 0.0) {
        Speed = -Speed;  // 방향 반전
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
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

    glutDisplayFunc(MyDisplay);
    glutIdleFunc(MyIdle);

    glutMainLoop();
    return 0;
}