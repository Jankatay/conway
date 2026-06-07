#pragma once 
#include <GL/freeglut.h>
#include "logical.hpp"

// global status values
bool pause = false;
static int cellWidth = 50;
static int cellHeight = 50;
static int lastButton = 0;
static int lastState = 0;

#include <iostream>
using namespace std;


// convert screen notation to graph
// will change x, y
void screenToGraph(int& x, int& y) {
  // make the offset from origin instead of corner
  x -= glutGet(GLUT_WINDOW_WIDTH)/2; 
  y -= glutGet(GLUT_WINDOW_HEIGHT)/2; 
  y = -y; // flip y axis
  // negatives are special
  x = x/cellWidth - ((x < 0)? 1 : 0); 
  y = y/cellWidth - ((y < 0)? 1 : 0);
}

// add/erase cells from graph based on input
void updateCells(int x, int y, int button) {
  // calculate
  screenToGraph(x, y);
  // update cells
  if(button == GLUT_LEFT_BUTTON) currentTurn->emplace(x, y);
  else if(button == GLUT_RIGHT_BUTTON) currentTurn->erase(Cell{x, y});
  else return; // no drawing necessary
  glutPostRedisplay(); // changes
}


// swap pause status on press
void keyboard(unsigned char key, int x, int y) { 
  if(key == ' ') {
    pause = !pause; 
    cerr << "pause" << endl;
  }
}


// let user put up and delete stuff
//TODO: right bottom sometimes feels off
void mouse(int button, int state, int x, int y) {
  // init status
  lastButton = button;
  lastState = state;

  // skip if nothing important
  updateCells(x, y, button);
}


// dragging mouse movement
void motion(int x, int y) { if(lastState == GLUT_DOWN) updateCells(x, y, lastButton); }


// draw a single square based on logical address
void drawCell(Cell cell) {
  // convert logical to physical
  int phyX = cell.x * cellWidth;
  int phyY = cell.y * cellHeight;
  cerr << cellWidth << endl;
  
  // draw as polygon
  glBegin(GL_POLYGON);
  glVertex2i(phyX, phyY);
  glVertex2i(phyX+cellWidth, phyY);
  glVertex2i(phyX+cellWidth, phyY+cellHeight);
  glVertex2i(phyX, phyY+cellHeight);
  glEnd();
}


// a simple timer
// val is ignored
void timer(int _) {
  if(pause) return; // check
  cerr << "recalculating" << endl;
  // recalculate and redraw
  nextCycle();
  glutPostRedisplay();
  glutTimerFunc(1000, timer, 0);
}


// handle drawing
void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  cellWidth = glutGet(GLUT_WINDOW_WIDTH)/8;
  cellHeight = glutGet(GLUT_WINDOW_HEIGHT)/8; // TODO: make it dynamically adjust based on how many cells user wants displayed
  glColor3f(0.796, 0.651, 0.969);
  for(Cell cell : *currentTurn) drawCell(cell);
  glFlush();
}
