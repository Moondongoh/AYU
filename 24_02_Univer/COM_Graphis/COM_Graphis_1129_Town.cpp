#include <cmath>
#include <GL/glut.h>
#define M_PI 3.14


// 조명 설정
void setupLighting() {
    GLfloat lightPosition[] = { 1.0f, 1.0f, 1.0f, 0.0f }; // 1시 방향 조명
    GLfloat lightAmbient[] = { 0.3f, 0.3f, 0.3f, 1.0f };  // 주변광
    GLfloat lightDiffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };  // 확산광
    GLfloat lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // 반사광

    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition); // 조명 위치 지정
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);   // 주변광 설정
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);   // 확산광 설정
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular); // 반사광 설정

    glEnable(GL_LIGHTING);      // 조명 활성화
    glEnable(GL_LIGHT0);        // GL_LIGHT0 활성화
    glEnable(GL_COLOR_MATERIAL); // 색상 재질 활성화
    glEnable(GL_DEPTH_TEST);     // 깊이 테스트 활성화
}


// 원 그리기
void drawCircle(float radius) {
    glBegin(GL_POLYGON);
    glColor3f(0.4f, 0.6f, 0.8f); // 파란색
    for (int i = 0; i < 360; i++) {
        float theta = i * M_PI / 180.0f;
        glVertex3f(radius * cos(theta), 0.0f, radius * sin(theta));
    }
    glEnd();
}

// 원기둥 그리기
void drawCylinder(float radius, float height) {
    GLUquadric* quad = gluNewQuadric();
    glRotatef(-90, 1.0f, 0.0f, 0.0f); // X축을 기준으로 -90도 회전
    glColor3f(0.6f, 0.4f, 0.2f); // 갈색
    gluCylinder(quad, radius, radius, height, 32, 32);
    gluDisk(quad, 0, radius, 32, 32); // 아래 원
    glTranslatef(0.0f, 0.0f, height);
    gluDisk(quad, 0, radius, 32, 32); // 위 원
    gluDeleteQuadric(quad);
}

// 사각뿔 그리기
void drawPyramid(float baseSize, float height) {
    glBegin(GL_TRIANGLES);
    glColor3f(0.9f, 0.7f, 0.2f); // 노란색

    // 앞면
    glVertex3f(-baseSize / 2, 0.0f, -baseSize / 2);
    glVertex3f(baseSize / 2, 0.0f, -baseSize / 2);
    glVertex3f(0.0f, height, 0.0f);

    // 오른쪽면
    glVertex3f(baseSize / 2, 0.0f, -baseSize / 2);
    glVertex3f(baseSize / 2, 0.0f, baseSize / 2);
    glVertex3f(0.0f, height, 0.0f);

    // 뒷면
    glVertex3f(baseSize / 2, 0.0f, baseSize / 2);
    glVertex3f(-baseSize / 2, 0.0f, baseSize / 2);
    glVertex3f(0.0f, height, 0.0f);

    // 왼쪽면
    glVertex3f(-baseSize / 2, 0.0f, baseSize / 2);
    glVertex3f(-baseSize / 2, 0.0f, -baseSize / 2);
    glVertex3f(0.0f, height, 0.0f);
    glEnd();
}

void drawCone(float radius, float height) {
    GLUquadric* quad = gluNewQuadric();
    glPushMatrix();
    glRotatef(-90, 1.0f, 0.0f, 0.0f); // X축을 기준으로 -90도 회전
    glColor3f(0.8f, 0.5f, 0.2f);      // 주황색
    gluCylinder(quad, radius, 0.0f, height, 32, 32); // 회전 후 그리기
    gluDisk(quad, 0, radius, 32, 32);               // 아래 원
    glPopMatrix();
    gluDeleteQuadric(quad);
}

// 직사각형 그리기
void drawRectangle(float width, float height, float depth) {
    glColor3f(0.4f, 0.8f, 0.4f); // 초록색
    glPushMatrix();
    glScalef(width, height, depth);
    glutSolidCube(1.0f);
    glPopMatrix();
}

// 신도시 단지
void drawDistrict(float x, float z) {
    // 원
    glPushMatrix();
    glTranslatef(x, 1.0f, z);
    drawCircle(1.0f);
    glPopMatrix();

    // 원기둥
    glPushMatrix();
    glTranslatef(x + 1.5f, 1.0f, z);
    drawCylinder(0.5f, 1.0f);
    glPopMatrix();

    // 사각뿔
    glPushMatrix();
    glTranslatef(x, 1.0f, z + 1.5f);
    drawPyramid(1.0f, 1.5f);
    glPopMatrix();

    // 원뿔
    glPushMatrix();
    glTranslatef(x - 1.5f, 1.0f, z);
    drawCone(0.5f, 1.0f);
    glPopMatrix();

    // 직사각형
    glPushMatrix();
    glTranslatef(x, 0.5f, z - 1.5f);
    drawRectangle(1.0f, 0.5f, 0.5f);
    glPopMatrix();
}

// 바닥 평면 그리기
void drawGround() {
    glColor3f(1.0f, 1.0f, 1.0f); // 하얀색
    glBegin(GL_QUADS);
    glVertex3f(-10.0f, 0.0f, -10.0f); // 왼쪽 아래
    glVertex3f(10.0f, 0.0f, -10.0f);  // 오른쪽 아래
    glVertex3f(10.0f, 0.0f, 10.0f);   // 오른쪽 위
    glVertex3f(-10.0f, 0.0f, 10.0f);  // 왼쪽 위
    glEnd();
}

// 마름모 선 그리기
void drawPathOutline() {
    glLineWidth(50.0f);
    glColor3f(0.0f, 0.0f, 0.0f); // 검은색 (선 색상)
    glBegin(GL_LINE_STRIP);

    // 마름모의 네 꼭짓점
    glVertex3f(-4.0f, 0.01f, 0.0f);  // 왼쪽
    glVertex3f(0.0f, 0.01f, -4.0f);  // 아래
    glVertex3f(7.0f, 0.01f, 0.0f);   // 오른쪽
    glVertex3f(0.0f, 0.01f, 7.5f);   // 위
    glVertex3f(-4.0f, 0.01f, 0.0f);  // 다시 왼쪽으로

    glEnd();
}


// 화면 출력
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    // 카메라 설정 (11시 방향에서 조망)
    gluLookAt(-8.0f, 8.0f, -8.0f,   // 카메라 위치
        0.0f, 0.0f, 0.0f,     // 카메라가 바라보는 지점
        0.0f, 1.0f, 0.0f);    // 상단 방향

    // 하얀색 바닥
    drawGround();

    drawPathOutline();

    // 신도시 단지 배치
    drawDistrict(-4.0f, -4.0f); // 단지 1
    drawDistrict(4.0f, -4.0f);  // 단지 2
    drawDistrict(-4.0f, 4.0f);  // 단지 3
    drawDistrict(4.0f, 4.0f);   // 단지 4
    drawDistrict(0.0f, 0.0f);   // 단지 5

    glutSwapBuffers();
}

// 윈도우 크기 조정
void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (float)width / height, 1.0, 100.0); // 원근 투영
    glMatrixMode(GL_MODELVIEW);
}

// 메인 함수
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("신도시 설계 - 3D 조감도");

    //glClearColor(0.8f, 0.8f, 1.0f, 1.0f); // 하늘색 배경
    setupLighting();                      // 조명 설정

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    glutMainLoop();
    return 0;
}
