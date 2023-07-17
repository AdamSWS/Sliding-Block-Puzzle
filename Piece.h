// Author: Adam Shaar
//
// Piece.h file for storing the information of each piece in the Sliding Block
// Puzzle

#ifndef PIECE_H
#define PIECE_H

class Piece {
public:
  //  constructor to store the information passed in about the peice
  Piece(char name, int row, int col, int width, int height, char movementType) {
    this->name = name;
    this->row = row;
    this->col = col;
    this->width = width;
    this->height = height;
    this->movementType = movementType;
  }
  //  function declarations
  char getName() const;
  void setName(char c);
  int getRow() const;
  void setRow(int r);
  int getCol() const;
  void setCol(int c);
  int getWidth() const;
  int getHeight() const;
  char getMovementType() const;

private:
  char name;
  int row;
  int col;
  int width;
  int height;
  char movementType;
};
  //  some getters and setters for the data members
  char Piece::getName() const { return name; }
  void Piece::setName(char c) { name = c; }
  int Piece::getRow() const { return row; }
  void Piece::setRow(int r) { row = r; }
  int Piece::getCol() const { return col; }
  void Piece::setCol(int c) { col = c; }
  int Piece::getWidth() const { return width; }
  int Piece::getHeight() const { return height; }
  char Piece::getMovementType() const { return movementType; }

#endif
