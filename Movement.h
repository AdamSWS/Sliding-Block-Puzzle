//  Author: Adam Shaar

//  Movement.h file to store the information about each valid movement

#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "Piece.h"
#include <iostream>
#include <string>

using namespace std;

class Movement {
public:
  //  constructor in different format due to movedPiece needing to be
  //  initialized
  Movement(string direction, int spaces, Piece movedPiece)
      : direction(direction), spaces(spaces), movedPiece(movedPiece) {}
  //  function declarations
  string getDirection();
  int getSpaces();
  Piece getPiece();

private:
  string direction;
  int spaces;
  Piece movedPiece;
};
//  some getters for the data members
string Movement::getDirection() { return direction; }
int Movement::getSpaces() { return spaces; }
Piece Movement::getPiece() { return movedPiece; }

#endif
