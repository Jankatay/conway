#include <iostream>
#include <GL/glut.h>

void display();
int main(int argc, char* argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(GLUT_WINDOW_WIDTH, GLUT_WINDOW_HEIGHT);
  glutCreateWindow("conway");
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}

void square(double x, double y, double w);
void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  square(0.3, 0.3, 0.4);
  glFlush();
}

void square(double x, double y, double w) {
  glBegin(GL_QUADS);
  glColor3d(1, 0, 0);
  glVertex2d(x, y);
  glVertex2d(x+w, y);
  glVertex2d(x+w, y+w);
  glVertex2d(x, y+w);
  glEnd();
}
