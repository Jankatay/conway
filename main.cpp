#include "controls.hpp"
#include <iostream>
using namespace std;

// handle drawing
void display();


int main(int argc, char* argv[]) {
  // init
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(400, 400);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("conway");
  glutDisplayFunc(display);

  // setup 
  glClearColor(0.118, 0.118, 0.180, 0.0);
  glutKeyboardFunc(keyboard);
  glutMouseFunc(mouse);
  glutMotionFunc(motion);
  glutTimerFunc(1000, timer, 0);

  // run and exit
  glutMainLoop();
  return 0;
}
