#include <gl/glut.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <math.h>
#include <time.h>
#include <stdio.h>

float a = .0;
float b = .0;
float c = .0;
void DrawPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void DDA(int x1, int y1, int x2, int y2, int n) {
    for (int i = 0; i < n; i++) {

        int y11 = y1 - i;
        int y22 = y2 - i;

        float y, m;
        int dx, dy;
        dx = x2 - x1;
        dy = y22 - y11;
        m = (float)dy / dx;
        for (int x = x1; x <= x2; x++) {
            y = m * (x - x1) + y11;
            DrawPixel(x, round(y));
            glFlush();
        }
    }
}

void Normal(int x1, int y1, int x2, int y2, int n) {
    for (int i = 0; i < n; i++) {
        int y11 = y1 - i;
        int y22 = y2 - i;
        clock_t start, end;
        float m, y;
        int dx, dy;
        dx = x2 - x1;
        dy = y22 - y11;
        m = (float)dy / dx;
        y = y11;
        for (int x = x1; x <= x2; x++) {
            DrawPixel(x, round(y));
            y += m;
            glFlush();
        }
    }
}

void Bresenham(int x1, int y1, int x2, int y2, int n) {
    for (int i = 0; i < n; i++) {
        int y11 = y1 - i;  // 선의 y1 좌표를 변경
        int y22 = y2 - i;  // 선의 y2 좌표를 변경
        int dx, dy, incrE, incrNE, D, x, y;

        dx = x2 - x1;
        dy = y22 - y11;

        int stepY = (dy > 0) ? 1 : -1;
        dy = abs(dy);

        D = 2 * dy - dx;
        incrE = 2 * dy;
        incrNE = 2 * dy - 2 * dx;

        x = x1;
        y = y11;

        DrawPixel(x, y);
        while (x < x2) {
            if (D <= 0) {
                D += incrE;
                x++;
            }
            else {
                D += incrNE;
                x++;
                y += stepY;  // y가 증가 또는 감소
            }
            DrawPixel(x, y);
            glFlush();
        }
    }
}

void MyDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    clock_t start, end;

    glColor3f(0, 0, 0);

    start = clock();
    DDA(0, 420, 640, 200, 20);
    glFinish();
    end = clock();

    a = (double)(end - start) / CLOCKS_PER_SEC;
    printf("(BLACK)DDA 실행 시간: %f 초\n", a);

    glColor3f(1, 0, 0);

    start = clock();
    Normal(0, 420, 640, 200, 20);
    glFinish();
    end = clock();

    b = (double)(end - start) / CLOCKS_PER_SEC;
    printf("(RED)Normal_LINE 실행 시간: %f 초\n", b);

    glColor3f(0, 1, 0);

    start = clock();
    Bresenham(0, 420, 640, 200, 20);
    glFinish();
    end = clock();

    c = (double)(end - start) / CLOCKS_PER_SEC;

    printf("(GREEN)Bresenham 실행 시간: %f 초\n", c);

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH); // 더블 버퍼링 활성화
    glutInitWindowSize(640, 420);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("OpenGL Line Drawing");

    glClearColor(1.0, 1.0, 1.0, 1.0);

    // 뷰포트와 투영 설정
    glViewport(0, 0, 500, 500);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 500, 0, 500, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glutDisplayFunc(MyDisplay);
    glutMainLoop();
    return 0;
}
