#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 600
#define HORSE_SIZE 10
#define NUM_HORSES 1
#define NUM_COLORS 7

typedef struct {
   float x;
   float y;
   int color;
   float speed;
   float size;
} Horse;

Horse horses[NUM_HORSES];
bool gameRunning = true;
int winner = -1;
float baseSpeed = 1.0;
float pl = 0.1;
int flag = 0;
float movx = 5;
float movy = 5;
int Ang = 0;
// 색상 배열 추가
float colors[NUM_COLORS][3] = {
   {1.0, 0.0, 0.0},  // 빨강
   {0.0, 1.0, 0.0},  // 초록
   {0.0, 0.0, 1.0},  // 파랑
   {1.0, 1.0, 0.0},  // 노랑
   {1.0, 0.0, 1.0},  // 마젠타
   {0.0, 1.0, 1.0},  // 시안
   {1.0, 0.5, 0.0}   // 주황
};

void initHorses() {
   srand(time(NULL));
   for (int i = 0; i < NUM_HORSES; i++) {
       /*horses[i].x = rand() % (WINDOW_WIDTH - HORSE_SIZE);
       horses[i].y = rand() % (WINDOW_HEIGHT - HORSE_SIZE);*/
       horses[i].x = 0;
       horses[i].y = 0;
       horses[i].color = (i % NUM_COLORS) + 1;
       horses[i].speed = baseSpeed;
       horses[i].size = HORSE_SIZE;
   }
}

void drawHorse(Horse horse) {
   glPushMatrix();
   glTranslatef(horse.x + horse.size / 2, horse.y + horse.size / 2, 0.0); // (x, y)로 이동
   glRotatef(Ang, 0, 0, 1); // 3도씩 회전 적용
   glTranslatef(-horse.size / 2, -horse.size / 2, 0.0); // 다시 원점으로 이동하여 사각형 중심을 맞춤

   glColor3fv(colors[horse.color]); // 색상 설정
   glBegin(GL_QUADS);
   glVertex2f(0, 0);                     // 사각형을 (0,0)에서 시작
   glVertex2f(horse.size, 0);
   glVertex2f(horse.size, horse.size);
   glVertex2f(0, horse.size);
   glEnd();

   glPopMatrix();
}


void display() {
   glClear(GL_COLOR_BUFFER_BIT);
   for (int i = 0; i < NUM_HORSES; i++) {
       drawHorse(horses[i]);
   }
   /*if (flag == 1) {
       Horse tmp;
       tmp.x =  0;
       tmp.y = 0;
       tmp.color = 0;
       tmp.speed = baseSpeed;
       tmp.size = 2000;
       drawHorse(tmp);
   }*/
   glutSwapBuffers();
}

void update(int value) {
   if (gameRunning) {

       int horse = rand() % NUM_HORSES;
       Ang += 3;
       horses[horse].size += pl;
       if (horses[0].x + movx >= WINDOW_WIDTH - horses[0].size || horses[0].x + movx <= 0) {
           movx *= -1;
       }

       // y 경계 체크
       if (horses[0].y + movy >= WINDOW_HEIGHT - horses[0].size || horses[0].y + movy <= 0) {
           movy *= -1;
       }
       horses[horse].x += movx;
       horses[horse].y += movy;



   }
   glutPostRedisplay();
   glutTimerFunc(100, update, 0);  // 0.1초마다 업데이트
}

void keyboard(unsigned char key, int x, int y) {
   switch (key) {
   case 'i':


       pl += 0.1;


       break;
   case 'm':
       pl -= 0.1;
       break;
   case 'g':
       gameRunning = true;
       break;
   }
}

void mouse(int button, int state, int x, int y) {
   if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && winner != -1) {
       if (x >= horses[winner].x && x <= horses[winner].x + HORSE_SIZE &&
           y >= WINDOW_HEIGHT - horses[winner].y - HORSE_SIZE && y <= WINDOW_HEIGHT - horses[winner].y) {
           char colorNames[][10] = { "Red", "Green", "Blue", "Yellow", "Magenta", "Cyan", "Orange" };
           printf("Winner: %s horse\n", colorNames[horses[winner].color]);
       }
   }
}

void reshape(int w, int h) {
   glViewport(0, 0, w, h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
   glMatrixMode(GL_MODELVIEW);
}

void changeHorseColor(int horseIndex) {
   horses[horseIndex].color = (horses[horseIndex].color + 1) % NUM_COLORS;
}

void speedUp() {
   for (int i = 0; i < NUM_HORSES; i++) {
       horses[i].speed *= 1.2;
   }
   baseSpeed *= 1.2;
}

void speedDown() {
   for (int i = 0; i < NUM_HORSES; i++) {
       horses[i].speed *= 0.8;
   }
   baseSpeed *= 0.8;
}

void MyMainMenu(int entryID)
{
   switch (entryID)
   {
   case 1:
       changeHorseColor(0);
       break;
   case 2:
       changeHorseColor(1);
       break;
   case 3:
       changeHorseColor(2);
       break;
   case 4: // 스피드 Up
       speedUp();
       break;
   case 5: // 스피드 Down
       speedDown();
       break;
   case 6:
       exit(0);
       break;
   }
   glutPostRedisplay();
}

int main(int argc, char** argv) {
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
   glutCreateWindow("Horse Race");

   GLint MyMainMenuID = glutCreateMenu(MyMainMenu);
   glutAddMenuEntry("Change Horse 1 Color", 1);
   glutAddMenuEntry("Change Horse 2 Color", 2);
   glutAddMenuEntry("Change Horse 3 Color", 3);
   glutAddMenuEntry("Speed Up", 4);
   glutAddMenuEntry("Speed Down", 5);
   glutAddMenuEntry("END", 6);
   glutAttachMenu(GLUT_RIGHT_BUTTON);

   glClearColor(1.0, 1.0, 1.0, 1.0);
   initHorses();
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutMouseFunc(mouse);
   glutTimerFunc(100, update, 0);
   srand(time(NULL));
   glutMainLoop();
   return 0;
}






//// 사각형 추가
//#include <stdlib.h>
//#include <GL/glut.h>
//#include <stdio.h>
//#include <stdbool.h>
//#include <time.h>
//#include <math.h>
//#define WINDOW_WIDTH 500
//#define WINDOW_HEIGHT 600
//#define HORSE_SIZE 10
//#define NUM_HORSES 2
//#define NUM_COLORS 7
//
//typedef struct {
//    float x;
//    float y;
//    int color;
//    float speed;
//    float size;
//    float movx;
//    float movy;
//    int angle;
//} Horse;
//
//Horse horses[NUM_HORSES];
//bool gameRunning = true;
//int winner = -1;
//float baseSpeed = 1.0;
//float pl = 0.1;
//int flag = 0;
//
//float colors[NUM_COLORS][3] = {
//    {1.0, 0.0, 0.0},  // 빨강
//    {0.0, 1.0, 0.0},  // 초록
//    {0.0, 0.0, 1.0},  // 파랑
//    {1.0, 1.0, 0.0},  // 노랑
//    {1.0, 0.0, 1.0},  // 마젠타
//    {0.0, 1.0, 1.0},  // 시안
//    {1.0, 0.5, 0.0}   // 주황
//};
//
//void initHorses() {
//    srand(time(NULL));
//    for (int i = 0; i < NUM_HORSES; i++) {
//        horses[i].x = i * 50;
//        horses[i].y = i * 50;
//        horses[i].color = i % NUM_COLORS;
//        horses[i].speed = baseSpeed;
//        horses[i].size = HORSE_SIZE;
//        horses[i].movx = (rand() % 5 + 3) * (rand() % 2 ? 1 : -1);
//        horses[i].movy = (rand() % 5 + 3) * (rand() % 2 ? 1 : -1);
//        horses[i].angle = 0;
//    }
//}
//
//void drawHorse(Horse horse) {
//    glPushMatrix();
//    glTranslatef(horse.x + horse.size / 2, horse.y + horse.size / 2, 0.0);
//    glRotatef(horse.angle, 0, 0, 1);
//    glTranslatef(-horse.size / 2, -horse.size / 2, 0.0);
//
//    glColor3fv(colors[horse.color]);
//    glBegin(GL_QUADS);
//    glVertex2f(0, 0);
//    glVertex2f(horse.size, 0);
//    glVertex2f(horse.size, horse.size);
//    glVertex2f(0, horse.size);
//    glEnd();
//
//    glPopMatrix();
//}
//
//void display() {
//    glClear(GL_COLOR_BUFFER_BIT);
//    for (int i = 0; i < NUM_HORSES; i++) {
//        drawHorse(horses[i]);
//    }
//    glutSwapBuffers();
//}
//
//void update(int value) {
//    if (gameRunning) {
//        for (int i = 0; i < NUM_HORSES; i++) {
//            horses[i].angle += (i + 1) * 2;
//            horses[i].size += pl;
//
//            if (horses[i].x + horses[i].movx >= WINDOW_WIDTH - horses[i].size ||
//                horses[i].x + horses[i].movx <= 0) {
//                horses[i].movx *= -1;
//            }
//
//            if (horses[i].y + horses[i].movy >= WINDOW_HEIGHT - horses[i].size ||
//                horses[i].y + horses[i].movy <= 0) {
//                horses[i].movy *= -1;
//            }
//
//            horses[i].x += horses[i].movx;
//            horses[i].y += horses[i].movy;
//        }
//    }
//    glutPostRedisplay();
//    glutTimerFunc(100, update, 0);
//}
//
//void keyboard(unsigned char key, int x, int y) {
//    switch (key) {
//    case 'i':
//        pl += 0.1;
//        break;
//    case 'm':
//        pl -= 0.1;
//        break;
//    case 'g':
//        gameRunning = true;
//        break;
//    case 'r':
//        initHorses();
//        break;
//    case 27:  // ESC 키
//        exit(0);
//        break;
//    }
//}
//
//void mouse(int button, int state, int x, int y) {
//    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
//        // 마우스 클릭 시 색상 변경
//        for (int i = 0; i < NUM_HORSES; i++) {
//            if (x >= horses[i].x && x <= horses[i].x + horses[i].size &&
//                WINDOW_HEIGHT - y >= horses[i].y && WINDOW_HEIGHT - y <= horses[i].y + horses[i].size) {
//                horses[i].color = (horses[i].color + 1) % NUM_COLORS;
//            }
//        }
//    }
//}
//
//void reshape(int w, int h) {
//    glViewport(0, 0, w, h);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
//    glMatrixMode(GL_MODELVIEW);
//}
//
//void changeHorseColor(int horseIndex) {
//    horses[horseIndex].color = (horses[horseIndex].color + 1) % NUM_COLORS;
//}
//
//void speedUp() {
//    for (int i = 0; i < NUM_HORSES; i++) {
//        horses[i].movx *= 1.2;
//        horses[i].movy *= 1.2;
//    }
//}
//
//void speedDown() {
//    for (int i = 0; i < NUM_HORSES; i++) {
//        horses[i].movx *= 0.8;
//        horses[i].movy *= 0.8;
//    }
//}
//
//void MyMainMenu(int entryID) {
//    switch (entryID) {
//    case 1:
//        changeHorseColor(0);
//        break;
//    case 2:
//        changeHorseColor(1);
//        break;
//    case 3:
//        speedUp();
//        break;
//    case 4:
//        speedDown();
//        break;
//    case 5:
//        exit(0);
//        break;
//    }
//    glutPostRedisplay();
//}
//
//int main(int argc, char** argv) {
//    glutInit(&argc, argv);
//    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
//    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
//    glutCreateWindow("Moving Squares");
//
//    GLint MyMainMenuID = glutCreateMenu(MyMainMenu);
//    glutAddMenuEntry("Change Square 1 Color", 1);
//    glutAddMenuEntry("Change Square 2 Color", 2);
//    glutAddMenuEntry("Speed Up", 3);
//    glutAddMenuEntry("Speed Down", 4);
//    glutAddMenuEntry("END", 5);
//    glutAttachMenu(GLUT_RIGHT_BUTTON);
//
//    glClearColor(1.0, 1.0, 1.0, 1.0);
//    initHorses();
//    glutDisplayFunc(display);
//    glutReshapeFunc(reshape);
//    glutKeyboardFunc(keyboard);
//    glutMouseFunc(mouse);
//    glutTimerFunc(100, update, 0);
//
//    glutMainLoop();
//    return 0;
//}