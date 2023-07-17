//  Author: Adam Shaar

//  Grid.h file to store the pieces and other board info for the Sliding Block
//  Puzzle

#ifndef GRID_H
#define GRID_H

#include "Movement.h"
#include "Piece.h"
#include "Snapshot.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Grid {
public:
  //  constructor of the grid class to save the number of rows, cols, the
  //  current layout of the grid, and all of its pieces
  Grid(int num_rows, int num_cols, vector<vector<char>> grid,
       vector<Piece> &pieces) {
    this->num_rows = num_rows;
    this->num_cols = num_cols;
    this->pieces = pieces;
    this->grid = grid;
  }
  //  some function declarations
  int getNumCols();
  int getNumRows();
  string getGridString();
  vector<Piece> getPieces();
  vector<vector<char>> getGrid();
  vector<Movement> allPossibleCurrentMoves(Snapshot snap);
  void canMoveUp(Piece piece, vector<Movement> &moves);
  void canMoveDown(Piece piece, vector<Movement> &moves);
  void canMoveRight(Piece piece, vector<Movement> &moves);
  void canMoveLeft(Piece piece, vector<Movement> &moves);
  Snapshot makeMove(Movement &move, vector<Piece> &new_pieces,
                    vector<vector<char>> &grid, vector<Movement> &curr_moves);

private:
  int num_rows;
  int num_cols;
  vector<Piece> pieces;
  vector<vector<char>> grid;
};
//  some getters and setters for the private data
vector<vector<char>> Grid::getGrid() { return grid; }
vector<Piece> Grid::getPieces() { return pieces; }
int Grid::getNumCols() { return num_cols; }
int Grid::getNumRows() { return num_rows; }
//  converts the layout of the board to a string
string Grid::getGridString() {
  string newGridLayout = "";
  for (auto &row : grid) {
    for (auto &cell : row) {
      newGridLayout += cell;
    }
  }
  return newGridLayout;
}
//  function tests to see of a piece can move up
void Grid::canMoveUp(Piece piece, vector<Movement> &moves) {
  for (int i = 1; i < piece.getRow() + 1; i++) {
    bool collision = false;
    for (int row = 0; row < piece.getHeight(); row++) {
      for (int col = 0; col < piece.getWidth(); col++) {
        //  tests to see if the above peices contain are empty or also apart of
        //  that peice
        if (grid[piece.getRow() - i + row][piece.getCol() + col] != '.' &&
            grid[piece.getRow() - i + row][piece.getCol() + col] !=
                piece.getName()) {
          //  if collison if found, breaks out of the nested loops
          collision = true;
          break;
        }
      }
      if (collision)
        break;
    }
    if (!collision) {
      //  saves the move to the movement vector
      moves.push_back(Movement("up", i, piece));
    } else {
      break;
    }
  }
}
//  function tests to see of a piece can move down
void Grid::canMoveDown(Piece piece, vector<Movement> &moves) {
  for (int i = 1; i < num_rows - piece.getRow() - piece.getHeight() + 1; i++) {
    bool collision = false;
    for (int row = 0; row < piece.getHeight(); row++) {
      for (int col = 0; col < piece.getWidth(); col++) {
        //  tests to see if the below peices contain are empty or also apart of
        //  that peice
        if (grid[piece.getRow() + piece.getHeight() - 1 + i]
                [piece.getCol() + col] != '.' &&
            grid[piece.getRow() + piece.getHeight() - 1 + i]
                [piece.getCol() + col] != piece.getName()) {
          //  if collison if found, breaks out of the nested loops
          collision = true;
          break;
        }
      }
      if (collision)
        break;
    }
    if (!collision) {
      //  saves the move to the movement vector
      moves.push_back(Movement("down", i, piece));
    } else {
      break;
    }
  }
}
//  function tests to see of a piece can move right
void Grid::canMoveRight(Piece piece, vector<Movement> &moves) {
  for (int i = 1; i < num_cols - piece.getCol() - piece.getWidth() + 1; i++) {
    bool collision = false;
    for (int row = 0; row < piece.getHeight(); row++) {
      for (int col = 0; col < piece.getWidth(); col++) {
        //  tests to see if the right peices contain are empty or also apart of
        //  that peice
        if (grid[piece.getRow() + row]
                [piece.getCol() + piece.getWidth() - 1 + i] != '.' &&
            grid[piece.getRow() + row][piece.getCol() + piece.getWidth() - 1 +
                                       i] != piece.getName()) {
          //  if collison if found, breaks out of the nested loops
          collision = true;
          break;
        }
      }
      if (collision)
        break;
    }
    if (!collision) {
      //  saves the move to the movement vector
      moves.push_back(Movement("right", i, piece));
    } else {
      break;
    }
  }
}
//  function tests to see of a piece can move left
void Grid::canMoveLeft(Piece piece, vector<Movement> &moves) {
  for (int i = 1; i < piece.getCol() + 1; i++) {
    bool collision = false;
    for (int row = 0; row < piece.getHeight(); row++) {
      for (int col = 0; col < piece.getWidth(); col++) {
        //  tests to see if the left peices contain are empty or also apart of
        //  that peice
        if (grid[piece.getRow() + row][piece.getCol() - i + col] != '.' &&
            grid[piece.getRow() + row][piece.getCol() - i + col] !=
                piece.getName()) {
          //  if collison if found, breaks out of the nested loops
          collision = true;
          break;
        }
      }
      if (collision)
        break;
    }
    if (!collision) {
      //  saves the move to the movement vector
      moves.push_back(Movement("left", i, piece));
    } else {
      break;
    }
  }
}

// function to find all the possible current moves for each piece on the board
vector<Movement> Grid::allPossibleCurrentMoves(Snapshot snap) {
  vector<Movement> moves;
  for (auto &piece : snap.getPieces()) {
    // checking to see if we can even move the piece
    if (piece.getMovementType() != 'n') {
      // checking for vertical movement;
      if (piece.getMovementType() == 'v') {
        canMoveUp(piece, moves);
        canMoveDown(piece, moves);
      } else if (piece.getMovementType() == 'h') {
        canMoveLeft(piece, moves);
        canMoveRight(piece, moves);
      } else {
        canMoveUp(piece, moves);
        canMoveDown(piece, moves);
        canMoveLeft(piece, moves);
        canMoveRight(piece, moves);
      }
    }
  }
  return moves;
}
//  takes the current valid moves vectors and trys to make the best move
Snapshot Grid::makeMove(Movement &move, vector<Piece> &new_pieces,
                        vector<vector<char>> &grid,
                        vector<Movement> &curr_moves) {
  Piece piece = move.getPiece();
  int row = piece.getRow();
  int col = piece.getCol();
  int width = piece.getWidth();
  int height = piece.getHeight();
  char name = piece.getName();
  string direction = move.getDirection();
  int steps = move.getSpaces();
  curr_moves.push_back(move);
  // Remove the piece from its original position
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      grid[row + i][col + j] = '.';
    }
  }
  // Update the piece's position based on the move direction
  if (direction == "up") {
    row -= steps;
  } else if (direction == "down") {
    row += steps;
  } else if (direction == "left") {
    col -= steps;
  } else if (direction == "right") {
    col += steps;
  }

  // Place the piece in its new position
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      grid[row + i][col + j] = name;
    }
  }

  // Update the piece's row and col in the pieces vector
  for (auto &p : new_pieces) {
    if (p.getName() == name) {
      p.setRow(row);
      p.setCol(col);
      break;
    }
  }
  string newGridLayout = "";
  for (auto &row : grid) {
    for (auto &cell : row) {
      newGridLayout += cell;
    }
  }
  //  returns the new snapshot 
  Snapshot new_snap(newGridLayout, new_pieces, curr_moves, grid);
  return new_snap;
}

#endif