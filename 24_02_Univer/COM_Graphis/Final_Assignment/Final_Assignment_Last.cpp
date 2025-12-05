#include <vector>
#include <cstdlib> 
#include <ctime>   
#include <cmath>
#include <GL/glut.h>
#include <string>
#define M_PI 3.14159265358979323846

// 건물 속성을 저장할 구조체
struct Building {
    float x, z;     // 위치
    float height;   // 높이
    float red, green, blue; // 색상
};

// 건물 리스트
std::vector<Building> buildings;

// 차량의 초기 위치 및 각도
float carX = 0.0f, carY = 0.0f, carZ = 0.0f;
float carAngle = 0.0f; // 차량의 회전 각도

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
    case 'a': // 우회전 
        carAngle -= rotationSpeed;
        break;
    case 'd': // 좌회전 
        carAngle += rotationSpeed;
        break;
    case 27: // ESC 키로 종료
        exit(0);
    }

    glutPostRedisplay(); // 화면 갱신
}

void initializeEnvironment() {
    srand(static_cast<unsigned>(time(0))); //초기화

    for (float x = -5.0f; x <= 5.0f; x += 2.0f) {
        for (float z = -5.0f; z <= 5.0f; z += 2.0f) {
            Building building;
            building.x = x;
            building.z = z;
            building.height = 1.0f + static_cast<float>(rand() % 5);
            building.red = static_cast<float>(rand() % 100) / 100.0f;
            building.green = static_cast<float>(rand() % 100) / 100.0f;
            building.blue = static_cast<float>(rand() % 100) / 100.0f;
            buildings.push_back(building);
        }
    }
}


void drawEnvironment() {
    // 검은색 도로
    glColor3f(0.1f, 0.1f, 0.1f);
    glBegin(GL_QUADS);
    glVertex3f(-10.0f, 0.0f, -10.0f);
    glVertex3f(-10.0f, 0.0f, 10.0f);
    glVertex3f(10.0f, 0.0f, 10.0f);
    glVertex3f(10.0f, 0.0f, -10.0f);
    glEnd();

    // 흰색 도로
    glColor3f(1.0f, 1.0f, 1.0f); 
    glBegin(GL_QUADS);
    glVertex3f(-6.5f, 0.01f, -6.5f); //약간 위
    glVertex3f(-6.5f, 0.01f, 6.5f);
    glVertex3f(6.5f, 0.01f, 6.5f);
    glVertex3f(6.5f, 0.01f, -6.5f);
    glEnd();

    // 건물 그리기
    for (const auto& building : buildings) {
        glColor3f(building.red, building.green, building.blue); 
        glPushMatrix();
        glTranslatef(building.x, building.height / 2.0f, building.z); 
        glScalef(1.0f, building.height, 1.0f);                     
        glutSolidCube(1.0f);
        glPopMatrix();
    }
}


void renderViewport(int x, int y, int width, int height, float cameraX, float cameraY, float cameraZ, float lookX, float lookY, float lookZ, const char* label) {
    glViewport(x, y, width, height); 
    glLoadIdentity();
    gluLookAt(cameraX, cameraY, cameraZ, lookX, lookY, lookZ, 0.0, 1.0, 0.0);
    drawEnvironment();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    int windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);

    // 상단 (후면)
    renderViewport(0, 2 * windowHeight / 3, windowWidth, windowHeight / 3, carX, 0.5f, carZ,
        carX - cos(carAngle * M_PI / 180.0f), 0.5f, carZ - sin(carAngle * M_PI / 180.0f),
        "후면");

    // 하단 왼쪽 (우측)
    renderViewport(0, 0, windowWidth / 3, 2 * windowHeight / 3, carX, 0.5f, carZ,
        carX + cos((carAngle - 90.0f) * M_PI / 180.0f), 0.5f, carZ + sin((carAngle - 90.0f) * M_PI / 180.0f),
        "우측");

    // 하단 중간 (정면)
    renderViewport(windowWidth / 3, 0, windowWidth / 3, 2 * windowHeight / 3, carX, 0.5f, carZ,
        carX + cos(carAngle * M_PI / 180.0f), 0.5f, carZ + sin(carAngle * M_PI / 180.0f),
        "정면");

    // 하단 오른쪽 (좌측)
    renderViewport(2 * windowWidth / 3, 0, windowWidth / 3, 2 * windowHeight / 3, carX, 0.5f, carZ,
        carX + cos((carAngle + 90.0f) * M_PI / 180.0f), 0.5f, carZ + sin((carAngle + 90.0f) * M_PI / 180.0f),
        "좌측");

    glutSwapBuffers();
}

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

    // 환경 초기화
    initializeEnvironment();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("2020E7014_문동오_Computer_Graphiis_Final_Assigment");

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