#define DEBUG
#include <GL/glut.h>
#include <set>

using namespace std;

// error reporting
#ifdef DEBUG
#include <iostream>
#define error(msg) cerr << __FILE__ << ":" << __LINE__ << " - Error -> "#msg << endl 
#else 
#define error(msg)
#endif

constexpr int CELL_WIDTH = 10;

// rounds `num` to "down" to nearest divisible by `num`
constexpr int floorNearest(int num, int target) { return num - (num % target); }

// information for one cell
struct Vec2d { int x; int y; };

// In array to matrix logic a Y would be max amount of rows. This comparison is inspired by that
// One Y is worth like infinite X
bool operator<(const Vec2d& left, const Vec2d& right) {
  if(left.y > right.y) return true;
  if(left.y < right.y) return false;
  return left.x > right.x;
}
// just check each field
bool operator==(const Vec2d& left, const Vec2d& right) { return (left.x == right.x) && (left.y == right.x); }

set<Vec2d> sleft, sright;
set<Vec2d>* sturn = &sleft;
struct {int lastX, lastY, lastButton;} minfo; // mouse info

// Place a square 
void square(double x, double y); 

// paint it all
void display();

// handle pause/unpause
bool pause = true;
void keyboardHandler(unsigned char key, int x, int y) {
  // swap pause-status on space
  if(key == ' ') pause = !pause; 
  error("Pause/Unpause");
}

// place down or erase blocks WHEN PAUSED
void mouseHandler(int button, int state, int x, int y) {
  // get and normalize the input
  x = floorNearest(x, CELL_WIDTH);
  y = floorNearest(y, CELL_WIDTH);

  // check necessity
  if((x == minfo.lastX) && (y == minfo.lastY) && (button == minfo.lastButton)) return;
  minfo.lastButton = button;
  if((button == GLUT_MIDDLE_BUTTON) || (state == GLUT_UP)) return;

  // right click for erase, left click for place
  Vec2d vec = {x, y};
  if(button == GLUT_RIGHT_BUTTON) sturn->insert(vec);
  else if(button == GLUT_LEFT_BUTTON) sturn->extract(vec);

  // update mouse info
  minfo.lastX = x;
  minfo.lastY = y;
  error("Mouse click");
}

void motionHandler(int x, int y) { 
  mouseHandler(minfo.lastButton, GLUT_DOWN, x, y);
  error("Mouse drag");
}

int main(int argc, char* argv[]) {
  // startup
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(GLUT_WINDOW_WIDTH, GLUT_WINDOW_HEIGHT);
  glutCreateWindow("conway");
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboardHandler);
  glutMouseFunc(mouseHandler);
  glutMotionFunc(motionHandler);
  glutMainLoop();

  // free and exit
  return 0;
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
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

