Author of Program: Adam Shaar

The Sliding Block Puzzles program begins by taking in user input from argv in main. This input is any one of the desired proj3x.data files and returns a board layout. The program then iterates through all possible valid moves, that have not yet been made, and tries to find the smallest set of moves to reach the end state (the Z piece touching the right edge of the board). In order to make this program, I split up my program into 5 seperate files.

1. SlidingBlock.cpp
  - this file contains the bulk of the output
  - contains BFS function that shows the algorithm used to find the solution
  - contains the dataStorage function which checks to see if a new piece on the board overlaps. If it does, the piece is ignored. If   
    the piece doesn't overlap, it is then added to the board
  - The main function sets up calls to the above functions

2. Grid.h
  - this file contains info about the grid, such as the number of columns, rows, board layout, and the current pieces
  - file also contains the functions to check the possible movements of each piece
    - canMoveUp
    - canMoveDown
    - canMoveRight
    - canMoveLeft
  - the canMoveFunctions are used so that we never attempt to make an invalid move. All moves that will be made by the board are     
    completely valid and prevents overlaps
  - the makeMove function takes the passed in move, and changes the board. The makeMove function returns a snapshot of the board so 
    that the BFS function in main doesn't get stuck in an inf loop.

3. Piece.h 
  - this file contains info about each piece, such as name, row, col, width, height, and the restrictions of movement
  - this file doesn't contain any specific problem solving functions, but just contains gettters and setts

4. Movement.h
  - this file contains info about each movement, such as direction, spaces, and the piece moved
  - in order to make the constructor work properly, I had to do a different format, but it's the same as the others
  - again, this file doesn't have any functiosn to help solve the puzzle, but contains items like getters and setters to access 
    Movement data

5. Snapshot.h
  - this file contains info about each possible move made, so that the same move isn't added to the BFS queue twice

