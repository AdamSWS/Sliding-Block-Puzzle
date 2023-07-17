// Author: Adam Shaar
//
// slidingBlock.cpp file uses BFS to solve the puzzle board

#include "Grid.h"
#include "Movement.h"
#include "Piece.h"
#include "Snapshot.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void bfs(Grid &starting_grid, vector<Movement> &min_steps) {
  queue<Snapshot> to_visit;
  set<string> visited;
  int steps = 0;

  to_visit.push(Snapshot(starting_grid.getGridString(),
                         starting_grid.getPieces(), {},
                         starting_grid.getGrid()));
  visited.insert(starting_grid.getGridString());
  while (!to_visit.empty()) {
    int level_size = to_visit.size();

    for (int i = 0; i < level_size; ++i) {
      Snapshot current_snap = to_visit.front();
      to_visit.pop();
      // visited.erase(current_snap.getGridString());
      bool goal_reached = false;
      for (Piece &piece : current_snap.getPieces()) {
        if (piece.getName() == 'Z') {
          if (piece.getCol() + piece.getWidth() == starting_grid.getNumCols()) {
            goal_reached = true;
          }
          break;
        }
      }

      if (goal_reached) {
        min_steps = current_snap.getMoves();
        return;
      }

      // Generate new moves and push them onto the queue
      vector<Piece> currPieces = current_snap.getPieces();
      Grid currGrid(starting_grid.getNumRows(), starting_grid.getNumCols(),
                    current_snap.getGrid(), currPieces);
      vector<Movement> possible_moves =
          currGrid.allPossibleCurrentMoves(current_snap);
      for (Movement &move : possible_moves) {
        vector<Piece> new_pieces = current_snap.getPieces();
        vector<vector<char>> new_grid = current_snap.getGrid();
        vector<Movement> new_moves = current_snap.getMoves();
        Snapshot new_snap =
            starting_grid.makeMove(move, new_pieces, new_grid, new_moves);
        string new_grid_str = new_snap.getGridString();

        if (visited.find(new_grid_str) == visited.end()) {
          to_visit.push(new_snap);
          visited.insert(new_grid_str);
        }
      }
    }

    ++steps;
  }

  return;
}

bool dataStorage(vector<vector<char>> &grid, int width, int height, int row,
                 int col, char &pieceName) {
  // First check if all the pieces being added don't overlap
  for (int i = row - 1; i < row + height - 1; i++) {
    for (int j = col - 1; j < col + width - 1; j++) {
      if (grid[i][j] != '.') {
        cout << "Warning: Piece with starting position of " << i + 1 << ","
             << j + 1 << " overlaps with another piece" << endl;
        return false;
      }
    }
  }

  // If no overlap, add the pieces
  for (int i = row - 1; i < row + height - 1; i++) {
    for (int j = col - 1; j < col + width - 1; j++) {
      grid[i][j] = pieceName;
    }
  }

  return true;
}

vector<char> fullCharSet() {
  vector<char> characters;
  characters.push_back('Z');

  for (char c = '1'; c <= '9'; ++c) {
    characters.push_back(c);
  }

  for (char c = 'a'; c <= 'z'; ++c) {
    characters.push_back(c);
  }

  for (char c = 'A'; c <= 'Y'; ++c) {
    characters.push_back(c);
  }
  return characters;
}

int main(int argc, char **argv) {
  cout << "Welcome to Sliding Block Puzzle\n";

  if (argc != 2) { // argc should be 2 for correct execution
    // We print argv[0] assuming it is the program name
    cout << "usage: " << argv[0] << " <filename>\n";
    exit(0);
  }

  // We assume argv[1] is a filename to open
  ifstream the_file(argv[1]);
  string line;
  // Always check to see if file opening succeeded
  if (!the_file.is_open()) {
    cout << "Could not open file: " << argv[1] << "\n";
    exit(0);
  }

  cout << "Using data from puzzle: " << argv[1] << endl;
  int rows, cols;
  the_file >> rows >> cols;
  the_file.ignore();
  if (rows <= 0 || cols <= 0) {
    if (rows <= 0) {
      cout << "Error: Number of rows must be greater than zero" << endl;
    }
    if (cols <= 0) {
      cout << "Error: Number of columns must be greater than zero" << endl;
    }
    return 1;
  }

  // read in input file and set up initial puzzle configuration
  vector<Piece> pieces;
  bool isFirstPiece = true;
  bool changeCharBack = false;
  vector<vector<char>> grid(rows, vector<char>(cols, '.'));
  vector<char> charset = fullCharSet();
  int i = 0;
  // while loop reads in the info from the file and creates Piece classes
  while (getline(the_file, line)) {
    bool shouldUpdatePieceName = true;
    if (i > charset.size()) {
      cout << "Error: Reached the limit of 61 pieces" << endl;
      cout << "Continuing output with first valid 61 pieces" << endl;
      break;
    }
    istringstream iss(line);
    int row, col, width, height;
    char movementType;
    iss >> row >> col >> width >> height >> movementType;
    if (row + height - 1 > rows || col + width - 1 > cols) {
      cout << "Warning: Piece with starting position of " << row << "," << col
           << " falls outside of grid" << endl;
      continue;
    }
    if (movementType != 'h' && movementType != 'v' && movementType != 'b' &&
        movementType != 'n') {
      cout << "Warning: Piece with starting position of " << row << "," << col
           << " has invalid movement" << endl;
      continue;
    }
    if (dataStorage(grid, width, height, row, col, charset[i])) {
      Piece newPiece(charset[i], row - 1, col - 1, width, height, movementType);
      pieces.push_back(newPiece);
      i++;
    }
  }

  Grid slidingPuzzle(rows, cols, grid, pieces);
  //  print out initial puzzle configuration
  for (int i = -1; i <= rows; i++) {
    for (int j = -1; j <= cols; j++) {
      if (i == -1 || i == rows || j == -1 || j == cols) {
        cout << "*";
      } else {
        cout << grid[i][j];
      }
    }
    cout << endl;
  }
  vector<Movement> min_steps;
  bfs(slidingPuzzle, min_steps);
  if (min_steps.empty()) {
    cout << "The puzzle has no solution" << endl;
  } else {
    cout << "This puzzle is solvable in " << min_steps.size() << " steps"
         << endl;
    int i = 1;
    for (auto a : min_steps) {
      cout << i++ << ". Piece " << a.getPiece().getName() << " moves "
           << a.getSpaces() << " space(s) " << a.getDirection() << endl;
    }
  }

  return 0;
}
