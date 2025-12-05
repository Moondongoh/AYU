#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 600
#define HORSE_SIZE 2
#define NUM_HORSES 2
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
       horses[i].x = rand() % WINDOW_WIDTH;
       horses[i].y = rand() % WINDOW_HEIGHT;
       horses[i].color = (i % NUM_COLORS) + 1;
       horses[i].speed = baseSpeed;
       horses[i].size = 2;
   }
}

void drawHorse(Horse horse) {
   glColor3fv(colors[horse.color]);
   glBegin(GL_QUADS);
   glVertex2f(horse.x, horse.y);
   glVertex2f(horse.x + horse.size, horse.y);
   glVertex2f(horse.x + horse.size, horse.y + horse.size);
   glVertex2f(horse.x, horse.y + horse.size);
   glEnd();
}

void display() {
   glClear(GL_COLOR_BUFFER_BIT);
   for (int i = 0; i < NUM_HORSES; i++) {
       drawHorse(horses[i]);
   }
   if (flag == 1) {
       Horse tmp;
       tmp.x = 0;
       tmp.y = 0;
       tmp.color = 0;
       tmp.speed = baseSpeed;
       tmp.size = 2000;
       drawHorse(tmp);
   }
   glutSwapBuffers();
}

void update(int value) {
   if (gameRunning) {

       int horse = rand() % NUM_HORSES;
       horses[horse].size += pl;
       float dx = horses[0].x - horses[1].x;
       float dy = horses[0].y - horses[1].y;
       float distance = sqrt(dx * dx + dy * dy);
       if (distance < (horses[0].size + horses[1].size) / 2) {
           flag = 1;
           gameRunning = false;
       }

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