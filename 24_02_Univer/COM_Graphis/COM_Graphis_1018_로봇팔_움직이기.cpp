#include <GL/glut.h>

void drawArm(); // 팔 그리기 함수
int mode = 0; // 1이면 앞으로 팔 뻗기, 2이면 원상태로 복구

void Draw_Body() {
    // 몸통을 원기둥으로 표현
    GLUquadric* quadric = gluNewQuadric();
    gluCylinder(quadric, 0.5, 0.5, 1.0, 20, 20); // 반지름 0.5, 높이 1.0의 원기둥
    gluDeleteQuadric(quadric);
}

void Draw_UpperArm() {
    GLUquadric* quadric = gluNewQuadric();
    gluCylinder(quadric, 0.3, 0.3, 0.8, 20, 20); // 상완은 조금 더 작은 원기둥
    gluDeleteQuadric(quadric);
}

void Draw_LowerArm() {
    GLUquadric* quadric = gluNewQuadric();
    gluCylinder(quadric, 0.2, 0.2, 0.7, 20, 20); // 하완은 더 작은 원기둥
    gluDeleteQuadric(quadric);
}

void Draw_Hand() {
    // 손은 구로 표현
    GLUquadric* quadric = gluNewQuadric();
    gluSphere(quadric, 0.2, 20, 20); // 반지름 0.2의 구를 그려서 손을 표현
    gluDeleteQuadric(quadric);
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 0.1, 100.0);  // near 값을 0.1로 수정

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // 카메라 위치를 조정
    gluLookAt(3.0, 3.0, 5.0,  // 카메라 위치를 대각선 방향으로 이동
        0.0, 0.0, 0.0,  // 원점을 바라봄
        0.0, 1.0, 0.0);

    // 전체 모델을 약간 이동
    glTranslatef(0.0, -1.0, 0.0);  // y축으로 약간 아래로 이동

    if (mode == 1) {
        glPushMatrix();
        glRotatef(-45, 1.0, 0.0, 0.0);  // 팔을 45도만 들어올림
        drawArm();
        glPopMatrix();
    }
    else if (mode == 2) {
        drawArm();
    }

    glutSwapBuffers();
}


void keyboard(unsigned char key, int x, int y) {
    // 키보드 입력을 통해 모드를 변경
    if (key == '1') {
        mode = 1; // 1번 키를 누르면 팔을 앞으로 뻗음
    }
    else if (key == '2') {
        mode = 2; // 2번 키를 누르면 팔을 원상태로 복구
    }
    glutPostRedisplay(); // 화면 갱신
}

void drawArm() {
    glPushMatrix();

    // 몸통
    Draw_Body();

    // 상완 (어깨)
    glTranslatef(0.0, 0.0, 1.0);
    glRotatef(90, 1.0, 0.0, 0.0);
    Draw_UpperArm();

    // 하완 (팔꿈치)
    glTranslatef(0.0, 0.0, 0.8);
    Draw_LowerArm();

    // 손
    glTranslatef(0.0, 0.0, 0.7);
    Draw_Hand();

    glPopMatrix();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Arm Movement");

    // 조명 설정
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat light_position[] = { 5.0, 5.0, 5.0, 1.0 };
    GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    // 재질 설정
    GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
    GLfloat mat_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 100.0 };

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glEnable(GL_DEPTH_TEST);
    glClearColor(1.0, 1.0, 1.0, 1.0);

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}