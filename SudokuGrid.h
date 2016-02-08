#ifndef SUDOKUGRID_H
#define SUDOKUGRID_H

#include <array>
#include <bitset>
#include <string>

#define BLOCK_SIZE 3

using namespace std;

// Cell structure for the SudokuGrid cells.
struct Cell{
  bitset<9> pencils;
  int number;
  bool fixed;
  bool solved;
  // bool penciled; /* Maybe don't need. */
};
  
class SudokuGrid {
private:
  // private class instance vars go here
  array<array<Cell, 9>,9> grid;
  
public:
  // SudokuGrid solver.
  SudokuGrid(std::string s) {
    int r = 0;  // r = which row
    int c = 0;  // c = which column
    int k = 0;  // k = char index in string s
        
    for(r = 0; r < 9; r++){
      for(c = 0; c < 9; c++, k++){
        if(s.at(k) == '.'){
          grid[r][c].number = 0;
          grid[r][c].solved = false;
          grid[r][c].fixed = false;
        }
        else{
           // Convert char integers to int integers and save them in the grid.
           grid[r][c].number = (int)(s.at(k) - '0');
           grid[r][c].fixed = true;
           grid[r][c].solved = true;
        }
      }
    }
  }
 
  // Returns a specified cell's value.
  int number(int row, int col) const { 
    return grid[row][col].number;
  }
  // Sets a particular cell to a specified number.
  void setNumber(int row, int col, int number) {
    grid[row][col].number = number;
  }
  
  // Checks if a particular cell is fixed or not.
  bool isFixed(int row, int col) const {
    if(grid[row][col].fixed == true)
      return true;
    return false;
  }
  
  // Checks if a particular cell is solved or not.
  bool isSolved(int row, int col) const {
    if(grid[row][col].solved == 1)
      return true;
    return false;
  }
  
  // Sets a particular cell to solved.
  void setSolved(int row, int col) { 
    grid[row][col].solved = 1;
  }
  
  // Checks if a particular value is penciled in at a specific cell.
  bool isPencilSet(int row, int col, int n) const {
    if(grid[row][col].pencils[n-1] == 1)
      return true;
    return false;
  }
  
  // Checks if any pencil values are set in a specific cell.
  bool anyPencilsSet(int row, int col) const { 
    if(grid[row][col].pencils.any())
      return true;
    return false;
  }
  
  // Set a specified pencil value in a specific cell.
  void setPencil(int row, int col, int n) { 
    grid[row][col].pencils[n-1] = 1;
  }
  
  // Sets all pencils to true in a specified cell.
  void setAllPencils(int row, int col) { 
    grid[row][col].pencils.set();
  }
  
  // Clears a specified pencil value in a specified cell.
  void clearPencil(int row, int col, int n) {
    grid[row][col].pencils.reset(n-1);
  }
  
  // Clears all the pencils in a specific cell.
  void clearAllPencils(int row, int col) {
    grid[row][col].pencils.reset();
  }
  
  // Prints the SudokuGrid puzzle.
  void printGrid(){
    for(int r = 0; r < 9; r++){
      cout << "\n";
      for(int c = 0; c < 9; c++){
        if(grid[r][c].number == 0)
          cout << "." << " ";
        else
          cout << grid[r][c].number << " "; 
        if(c == 2 || c == 5)
          cout << "| ";
        
        if((r == 2 || r == 5) && c == 8){
          cout << "\n";
          for(int i = 0; i < 22; i++){
            if(i == 6 || i == 14)
              cout << "+";
            else
              cout << "-";
          }
        }
          
      }
    }
    cout << "\n";
  }
  
};

#endif // SUDOKUGRID_H