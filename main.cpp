#define DEBUG
#include <GL/glut.h>
#include <vector>

using namespace std;

// error reporting
#ifdef DEBUG
#include <iostream>
#define error(msg) cerr << __FILE__ << ":" << __LINE__ << " - Error -> "#msg << endl 
#else 
#define error(msg)
#endif

// information for one cell
struct Vec2d {int x; int y;};

vector<Vec2d> vleft, vright;
vector<Vec2d>* vturn = &vleft;

// Place a square 
void square(double x, double y, double width); 

// paint it all
void display();

// handle pause/unpause
bool pause = true;
void keyboardHandler(char key, int x, int y) {
  // swap pause-status on space
  if(key == ' ') pause = !pause; 
}

// place down or erase blocks WHEN PAUSED
void mouseHandler(int button, int state, int x, int y) {
  //TODO: handle erasing and adding in a way that still lets me add motion handler later
}


int main(int argc, char* argv[]) {
  // init

  // startup
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(GLUT_WINDOW_WIDTH, GLUT_WINDOW_HEIGHT);
  glutCreateWindow("conway");
  glutDisplayFunc(display);
  glutMainLoop();

  // free and exit
  return 0;
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  for(auto &elem : *vturn) square(elem.x, elem.y, 5);
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
