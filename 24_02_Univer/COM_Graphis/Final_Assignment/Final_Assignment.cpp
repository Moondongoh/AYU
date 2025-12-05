//#include <cmath>
//#include <GL/glut.h>
//#define M_PI 3.14159265358979323846
//
//// 차량의 초기 위치 및 각도
//float carX = 0.0f, carY = 0.0f, carZ = 0.0f;
//float carAngle = 0.0f; // 차량의 회전 각도
//
//// 키보드 입력 콜백
//void keyboardCallback(unsigned char key, int x, int y) {
//    float speed = 0.1f;           // 전진 및 후진 속도
//    float rotationSpeed = 5.0f;   // 각도 회전 속도
//
//    switch (key) {
//    case 'w': // 전진
//        carX += speed * cos(carAngle * M_PI / 180.0f);
//        carZ += speed * sin(carAngle * M_PI / 180.0f);
//        break;
//    case 's': // 후진
//        carX -= speed * cos(carAngle * M_PI / 180.0f);
//        carZ -= speed * sin(carAngle * M_PI / 180.0f);
//        break;
//    case 'a': // 좌회전
//        carAngle += rotationSpeed;
//        break;
//    case 'd': // 우회전
//        carAngle -= rotationSpeed;
//        break;
//    case 27: // ESC 키로 종료
//        exit(0);
//    }
//
//    glutPostRedisplay(); // 화면 갱신
//}
//
//// 3D 차량 그리기
//void drawCar() {
//    glPushMatrix();
//    glTranslatef(carX, carY, carZ);      // 자동차 위치 이동
//    glRotatef(carAngle, 0.0f, 1.0f, 0.0f); // 자동차 회전
//
//    // 자동차 몸체
//    glColor3f(.0f, 1.0f, 0.0f);
//    glScalef(0.6f, 0.3f, 1.2f); // 앞뒤로 긴 형태로 스케일 변경
//    glutSolidCube(0.5f);
//
//    // 자동차 윗부분
//    glPushMatrix();
//    glTranslatef(0.0f, 0.25f, 0.0f);
//    glScalef(0.4f, 0.5f, 0.8f);
//    glutSolidCube(0.5f);
//    glPopMatrix();
//
//    glPopMatrix();
//}
//
//// 화면 그리기
//void display() {
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//    glLoadIdentity();
//
//    // 카메라 설정: 차량과 동일한 시점으로
//    float cameraX = carX - 2.0f * cos(carAngle * M_PI / 180.0f);
//    float cameraY = 1.0f; // 카메라 높이
//    float cameraZ = carZ - 2.0f * sin(carAngle * M_PI / 180.0f);
//
//    gluLookAt(cameraX, cameraY, cameraZ,  // 카메라 위치 (차량 뒤쪽)
//        carX, carY, carZ,          // 카메라가 바라보는 곳 (차량 위치)
//        0.0, 1.0, 0.0);           // 상단 방향
//
//    // 바닥 (도로)
//    glColor3f(0.3f, 0.3f, 0.3f);
//    glBegin(GL_QUADS);
//    glVertex3f(-10.0f, 0.0f, -10.0f);
//    glVertex3f(-10.0f, 0.0f, 10.0f);
//    glVertex3f(10.0f, 0.0f, 10.0f);
//    glVertex3f(10.0f, 0.0f, -10.0f);
//    glEnd();
//
//    // 건물
//    glColor3f(0.9f, 0.9f, 0.9f);
//    for (float x = -5.0f; x <= 5.0f; x += 2.0f) {
//        for (float z = -5.0f; z <= 5.0f; z += 2.0f) {
//            glPushMatrix();
//            glTranslatef(x, 0.5f, z);
//            glScalef(1.0f, 2.0f, 1.0f);
//            glutSolidCube(1.0f);
//            glPopMatrix();
//        }
//    }
//
//    // 자동차 그리기
//    drawCar();
//
//    glutSwapBuffers();
//}
//
//// 윈도우 크기 조정
//void reshape(int width, int height) {
//    glViewport(0, 0, width, height);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluPerspective(60.0, (float)width / height, 0.1, 100.0); // 원근 투영
//    glMatrixMode(GL_MODELVIEW);
//}
//
//// 메인 함수
//int main(int argc, char** argv) {
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
//    glutInitWindowSize(800, 600);
//    glutCreateWindow("3D 자동차 시뮬레이션");
//
//    // 초기화
//    glEnable(GL_DEPTH_TEST); // 깊이 테스트 활성화
//    glClearColor(0.8f, 0.8f, 1.0f, 1.0f);
//
//    // 콜백 등록
//    glutDisplayFunc(display);
//    glutReshapeFunc(reshape);
//    glutKeyboardFunc(keyboardCallback);
//
//    glutMainLoop();
//    return 0;
//}


#include <cmath>
#include <GL/glut.h>
#include <string>
#define M_PI 3.14159265358979323846

// 차량의 초기 위치 및 각도
float carX = 0.0f, carY = 0.0f, carZ = 0.0f;
float carAngle = 0.0f; // 차량의 회전 각도

// 텍스트 그리기 함수
void drawText(const char* text, float x, float y) {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0); // 2D 평면 설정

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glRasterPos2f(x, y);
    for (const char* c = text; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

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
    case 'a': // 우회전 (기존 좌회전 기능을 우회전으로 변경)
        carAngle -= rotationSpeed;
        break;
    case 'd': // 좌회전 (기존 우회전 기능을 좌회전으로 변경)
        carAngle += rotationSpeed;
        break;
    case 27: // ESC 키로 종료
        exit(0);
    }

    glutPostRedisplay(); // 화면 갱신
}
// 도로 및 건물 그리기
void drawEnvironment() {
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
}

// 특정 뷰포트 설정 및 렌더링
void renderViewport(int x, int y, int width, int height, float cameraX, float cameraY, float cameraZ, float lookX, float lookY, float lookZ, const char* label) {
    // 뷰포트 설정
    glViewport(x, y, width, height);
    glLoadIdentity();
    gluLookAt(cameraX, cameraY, cameraZ, lookX, lookY, lookZ, 0.0, 1.0, 0.0);
    drawEnvironment();

    // 텍스트 표시
    glColor3f(0.0f, 0.0f, 0.0f); // 텍스트 색상 (검정)
    drawText(label, 0.4f, 0.9f); // 텍스트 위치 (뷰포트 상단 중앙)
}

// 화면 그리기
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 차량 내부에서 각 시점 설정
    float cameraHeight = 0.5f;
    float cameraDepth = 0.5f;

    // 정면 시점
    float frontX = carX + cos(carAngle * M_PI / 180.0f);
    float frontZ = carZ + sin(carAngle * M_PI / 180.0f);

    // 후면 시점
    float backX = carX - cos(carAngle * M_PI / 180.0f);
    float backZ = carZ - sin(carAngle * M_PI / 180.0f);

    // 왼쪽 시점
    float leftX = carX + cos((carAngle + 90.0f) * M_PI / 180.0f);
    float leftZ = carZ + sin((carAngle + 90.0f) * M_PI / 180.0f);

    // 오른쪽 시점
    float rightX = carX + cos((carAngle - 90.0f) * M_PI / 180.0f);
    float rightZ = carZ + sin((carAngle - 90.0f) * M_PI / 180.0f);

    // 뷰포트 4개로 나누기
    int halfWidth = glutGet(GLUT_WINDOW_WIDTH) / 2;
    int halfHeight = glutGet(GLUT_WINDOW_HEIGHT) / 2;

    // 정면 시점
    renderViewport(0, halfHeight, halfWidth, halfHeight, carX, cameraHeight, carZ, frontX, cameraHeight, frontZ, "정면");

    // 후면 시점
    renderViewport(halfWidth, halfHeight, halfWidth, halfHeight, carX, cameraHeight, carZ, backX, cameraHeight, backZ, "후면");

    // 왼쪽 시점
    renderViewport(0, 0, halfWidth, halfHeight, carX, cameraHeight, carZ, leftX, cameraHeight, leftZ, "왼쪽");

    // 오른쪽 시점
    renderViewport(halfWidth, 0, halfWidth, halfHeight, carX, cameraHeight, carZ, rightX, cameraHeight, rightZ, "오른쪽");

    glutSwapBuffers();
}

// 윈도우 크기 조정
void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (float)width / height, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

// 메인 함수
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("차량 내부에서 4개 시점");

    // 초기화
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.8f, 0.8f, 1.0f, 1.0f);

    // 콜백 등록
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboardCallback);

    glutMainLoop();
    return 0;
}