// Author: Adam Shaar
//
// Snapshot.h file for storing the information of each snapshot (saved move
// snapshot)

#ifndef SNAPSHOT_H
#define SNAPSHOT_H

#include "Grid.h"
#include "Movement.h"
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <vector>

using namespace std;

class Snapshot {
public:
  //  constructor to store the information passed in about the snpashot
  Snapshot(string gridLayout, vector<Piece> pieces, vector<Movement> moves,
           vector<vector<char>> grid) {
    this->gridLayout = gridLayout;
    this->pieces = pieces;
    this->moves = moves;
    this->grid = grid;
  }
  // function declarations
  vector<Movement> getMoves();
  vector<Piece> getPieces();
  vector<vector<char>> getGrid();
  string getGridString();

private:
  string gridLayout;
  vector<Movement> moves;
  vector<Piece> pieces;
  vector<vector<char>> grid;
};
// contains getters for information about the snapshot
vector<Movement> Snapshot::getMoves() { return moves; }
vector<Piece> Snapshot::getPieces() { return pieces; }
vector<vector<char>> Snapshot::getGrid() { return grid; }
string Snapshot::getGridString() { return gridLayout; }

#endif
