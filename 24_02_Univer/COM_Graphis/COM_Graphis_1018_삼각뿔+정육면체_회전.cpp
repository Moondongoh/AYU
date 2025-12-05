// 삼각뿔 정육면체
#include <stdlib.h>
#include <GL/glut.h>
#include <cmath>

float rotationAngle = 0.0f;

void drawCube() {
    glPushMatrix();
    glScalef(1.0f, 1.0f, 1.0f);
    glutSolidCube(1.0);
    glPopMatrix();
}

void drawPyramid() {
    glPushMatrix();
    glTranslatef(0.0f, 0.5f, 0.0f);
    glBegin(GL_TRIANGLES);
    // Front
    glVertex3f(0.0f, 0.5f, 0.0f);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    // Right
    glVertex3f(0.0f, 0.5f, 0.0f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    // Back
    glVertex3f(0.0f, 0.5f, 0.0f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    // Left
    glVertex3f(0.0f, 0.5f, 0.0f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glEnd();
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(3.0, 3.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glPushMatrix();
    glRotatef(rotationAngle, 0.0f, 1.0f, 0.0f);

    // 정육면체 그리기
    glColor3f(0.5f, 0.5f, 1.0f);
    drawCube();

    // 삼각뿔 그리기
    glColor3f(1.0f, 0.5f, 0.5f);
    drawPyramid();

    glPopMatrix();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)w / (float)h, 0.1, 100.0);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'r':
        rotationAngle += 5.0f;
        if (rotationAngle > 360.0f) rotationAngle -= 360.0f;
        break;
    case 'R':
        rotationAngle -= 5.0f;
        if (rotationAngle < 0.0f) rotationAngle += 360.0f;
        break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Cube with Pyramid");

    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}