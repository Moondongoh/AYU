#include <cmath>
#include <GL/glut.h>
#define M_PI 3.14159265358979323846

// 차량의 초기 위치 및 각도
float carX = 0.0f, carY = 0.0f, carZ = 0.0f;
float carAngle = 0.0f; // 차량의 회전 각도

// 키보드 입력 콜백
void keyboardCallback(unsigned char key, int x, int y) {
    float speed = 0.1f;           // 전진 및 후진 속도
    float rotationSpeed = 5.0f;   // 각도 회전 속도

    switch (key) {
    case 'w': // 전진
        carX += speed * cos(carAngle * M_PI / 180.0f);
        carZ += speed * sin(carAngle * M_PI / 180.0f);
        break;
    case 's': // 후진
        carX -= speed * cos(carAngle * M_PI / 180.0f);
        carZ -= speed * sin(carAngle * M_PI / 180.0f);
        break;
    case 'a': // 좌회전
        carAngle += rotationSpeed;
        break;
    case 'd': // 우회전
        carAngle -= rotationSpeed;
        break;
    case 27: // ESC 키로 종료
        exit(0);
    }

    glutPostRedisplay(); // 화면 갱신
}

// 3D 차량 그리기
void drawCar() {
    glPushMatrix();
    glTranslatef(carX, carY, carZ);      // 자동차 위치 이동
    glRotatef(carAngle, 0.0f, 1.0f, 0.0f); // 자동차 회전

    // 자동차 몸체
    glColor3f(.0f, 1.0f, 0.0f);
    glScalef(0.6f, 0.3f, 1.2f); // 앞뒤로 긴 형태로 스케일 변경
    glutSolidCube(0.5f);

    // 자동차 윗부분
    glPushMatrix();
    glTranslatef(0.0f, 0.25f, 0.0f);
    glScalef(0.4f, 0.5f, 0.8f);
    glutSolidCube(0.5f);
    glPopMatrix();

    glPopMatrix();
}

// 화면 그리기
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    // 카메라 설정: 차량과 동일한 시점으로
    float cameraX = carX - 2.0f * cos(carAngle * M_PI / 180.0f);
    float cameraY = 1.0f; // 카메라 높이
    float cameraZ = carZ - 2.0f * sin(carAngle * M_PI / 180.0f);

    gluLookAt(cameraX, cameraY, cameraZ,  // 카메라 위치 (차량 뒤쪽)
        carX, carY, carZ,          // 카메라가 바라보는 곳 (차량 위치)
        0.0, 1.0, 0.0);           // 상단 방향

    // 바닥 (도로)
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_QUADS);
    glVertex3f(-10.0f, 0.0f, -10.0f);
    glVertex3f(-10.0f, 0.0f, 10.0f);
    glVertex3f(10.0f, 0.0f, 10.0f);
    glVertex3f(10.0f, 0.0f, -10.0f);
    glEnd();

    // 건물
    glColor3f(0.9f, 0.9f, 0.9f);
    for (float x = -5.0f; x <= 5.0f; x += 2.0f) {
        for (float z = -5.0f; z <= 5.0f; z += 2.0f) {
            glPushMatrix();
            glTranslatef(x, 0.5f, z);
            glScalef(1.0f, 2.0f, 1.0f);
            glutSolidCube(1.0f);
            glPopMatrix();
        }
    }

    // 자동차 그리기
    drawCar();

    glutSwapBuffers();
}

// 윈도우 크기 조정
void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (float)width / height, 0.1, 100.0); // 원근 투영
    glMatrixMode(GL_MODELVIEW);
}

// 메인 함수
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("3D 자동차 시뮬레이션");

    // 초기화
    glEnable(GL_DEPTH_TEST); // 깊이 테스트 활성화
    glClearColor(0.8f, 0.8f, 1.0f, 1.0f);

    // 콜백 등록
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboardCallback);

    glutMainLoop();
    return 0;
}
