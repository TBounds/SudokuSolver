#include <string>
#include <iostream>
#include <algorithm>
#include "SudokuGrid.h"

using namespace std;

// Counts the total number of a specific pencil value in a specified row.
int numPencilsInRow(SudokuGrid& grid, int row, int n){
  int count = 0;
  // Counts the number of a specific peniciled value in a specific row.
  for(int j = 0; j < 9; j++)
    if(grid.isPencilSet(row, j, n))
      count++;
    
  return count;   
}

// Counts the total number of a specific pencil value in a specified col.
int numPencilsInColumn(SudokuGrid& grid, int col, int n){
  int count = 0;
  // Counts the number of a specific peniciled value in a specific col.
  for(int i = 0; i < 9; i++)
    if(grid.isPencilSet(i, col, n))
      count++;
    
  return count;
}

// Counts the total number of a specific pencil value in a specified block.
int numPencilsInBlock(SudokuGrid& grid, int row, int col, int n){
  int rowStart = row - (row % BLOCK_SIZE);
  int colStart = col - (col % BLOCK_SIZE);
  int count = 0;
  
  // Counts the number of a specific peniciled value in a specific block.
  for(int i = rowStart; i < (rowStart+BLOCK_SIZE); i++)
    for(int j = colStart; j < (colStart+BLOCK_SIZE); j++)
      if(grid.isPencilSet(i, j, n))
        count++;
      
  return count;
}

// Finds the first cell, in row major order, that is empty. 
bool findUnassignedLocation(SudokuGrid& grid, int& row, int& col){
  for(row = 0; row < 9; row++)
    for(col = 0; col < 9; col++)
      if(grid.number(row,col) == 0)
        return true;
  return false;
}

// Checks for a conflicting number in the row, column, and block.
bool conflictingNumber(SudokuGrid& grid, int r, int c, int n){
  int rowStart = r - (r % BLOCK_SIZE);
  int colStart = c - (c % BLOCK_SIZE);
  
  // Check if there is a conflicting number in the column.
  for(int i = 0; i < 9; i++)
    if((grid.number(i, c) == n) && (i != r))
      return true;
    
  // Check if there is a conflicting number in the row
  for(int j = 0; j < 9; j++)
    if((grid.number(r, j) == n) && (j != c))
      return true;
    
  // Check if there is a conflicting number in the block.
  for(int i = rowStart; i < (rowStart+BLOCK_SIZE); i++)
    for(int j = colStart; j < (colStart+BLOCK_SIZE); j++)
      if(grid.number(i, j) == n && (i != r) && (j != c))
        return true;

  return false;
}

// Algo for penciling in values for a sudokugrid puzzle.  
void autoPencil(SudokuGrid& grid) {
  for (int r = 0; r < 9; r++)
    for (int c = 0; c < 9; c++)
      if (grid.number(r,c) == 0) {
        grid.setAllPencils(r,c);
        for (int n = 1; n <= 9; n++)
          if (conflictingNumber(grid,r,c,n))
            grid.clearPencil(r,c,n);
      }
}

// Algo for deducing cell values in a sudokugrid puzzle.
void deduce(SudokuGrid& grid) {
  bool changed;
  do { // repeat until no changes made
    autoPencil(grid);
    changed = false;
    for (int row = 0; row < 9; row++)
      for (int col = 0; col < 9; col++)
        for (int n = 1; n <= 9; n++)
          if (grid.isPencilSet(row, col, n) &&
              (numPencilsInRow(grid, row, n) == 1 ||
              numPencilsInColumn(grid, col, n) == 1 ||
              numPencilsInBlock(grid, row, col, n) == 1)) {
            grid.clearAllPencils(row, col);
            grid.setNumber(row,col,n);
            grid.setSolved(row,col);
            autoPencil(grid);
            changed = true;
            break;
          }
  } while(changed);
}

// Algo for solving a sudoku puzzle.
bool solveSudoku(SudokuGrid& grid) {
  int row, col;
  if (!findUnassignedLocation(grid, row, col))
    return true; // puzzle filled, solution found!
  
  for (int num = 1; num <= 9; num++)
    if (!conflictingNumber(grid, row, col, num)) {
      grid.setNumber(row, col, num); // try next number
      if (solveSudoku(grid))
        return true; // solved!
      grid.setNumber(row, col, 0); // not solved, clear number
    }
  return false; // not solved, back track
}
  
int main(int argc, char *argv[]) {
  string puzzle;
  cin >> puzzle;
  if (puzzle.length() != 9*9 ||
      !all_of(puzzle.begin(), puzzle.end(),
	      [](char ch) {
		return ch == '.' || ('1' <= ch && ch <= '9');
	      })) {
    cerr << "bogus puzzle!" << endl;
    exit(1);
  }

  // XXX
	SudokuGrid grid(puzzle);
  
  grid.printGrid();
  deduce(grid);
  grid.printGrid();
  solveSudoku(grid);
  grid.printGrid();
  
  return 0;
}