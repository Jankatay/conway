#pragma once

#include <set>
using namespace std;


// logical vector
struct Cell{
  Cell(int _x, int _y): x(_x), y(_y) {}
  int x; int y; 
}; 

// comparing Cells, first compare y axes then x for less-than relation. Compare both for equals.
bool operator<(const Cell& left, const Cell& right) { return (left.y < right.y) || (left.x < right.x); }
bool operator==(const Cell& left, const Cell& right) { return (left.x == right.x) && (left.y == right.y); }


// global variables
set<Cell> left{}, right{};
set<Cell>* currentTurn = &left; // current turn
set<Cell>* nextTurn = &right; // next turn



// count how many neighbors a cell has
// the cell must be in the neighborhood
int countNeighbors(const Cell cell, const set<Cell>& neighborhood) {
  int ret = 0; // init

  // look into all neighbors in the 3x3 grid with cell in center
  for(int x = cell.x-1; x < cell.x+1; x++) {
    for(int y = cell.y-1; y < cell.y+1; y++) {
      if(neighborhood.find(Cell{x, y}) != neighborhood.end()) ret++;
    }
  }

  // subtract one to offset current cell
  return ret-1;
}


// compute a single cell and all its neighbors
void computeCell(const Cell cell, const set<Cell>& src, set<Cell>& dst) {
  for(int x = cell.x-1; x < cell.x+1; x++) {
    for(int y = cell.y-1; y < cell.y+1; y++) {
      Cell tmp = {x, y};
      int neighbors = countNeighbors(tmp, src); // count neighbors
      if(neighbors < 2) continue; // Check underpopulation, cell doesn't survive to dst. 
      if(neighbors > 3) continue; // Check overpopulation.
      dst.insert(tmp); // all good!
    }
  } // endloop
}


// Compute all changes based on src, write them to dst. (dst is erased)
void computeCells(const set<Cell>& src, set<Cell>& dst) {
  dst.clear(); // init
  for(Cell elem : src) computeCell(elem, src, dst); // compute
}


// swap between two sets to handle updates efficiently
void nextCycle() { 
  computeCells(*currentTurn, *nextTurn); // calculate next values
  swap(currentTurn, nextTurn); // cycle turn and finish
}
