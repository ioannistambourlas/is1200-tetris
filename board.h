//grid/board header - Ioannis

#ifndef BOARD_H
#define BOARD_H

#define BOARD_COLS 10
#define BOARD_ROWS 20

void board_reset(void); // Board,score reset and first piece spawn at the top
char board_square(int col, int row); // If the cell is empty then it is 0 if now it is the number of the colour
int board_horizontal(int movehor); // Move one left or one right if succeded return 1
int board_rotate(void); //Rotates a piece
int board_vertical(void); //Move the piece one down chek if it landed clear any full rows, birng next piece


//Fuctions to transfer the state of the variables to the other modules
void board_current_piece(int *type, int *rotation, int*col, int *row); //Current piece properties
int board_next_piece(void); //next piece for the preview box
int board_score(void); //how many lines have been cleared
int board_game_over(void); //if 1 game over

#endif