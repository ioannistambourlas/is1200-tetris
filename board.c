// move pieces left right, spawn the next piece,clear lines, rotation, randomize pieaces,locks piece on the board, make the falling piece fall, keep score, detect game over,reset board, gives relevant info to other modules
//Authored: Ioannis
#include "board.h"
#include "pieces.h"

unsigned char grid[BOARD_ROWS][BOARD_COLS];

int create_random_piece(void);
void spawn(void);
void lock_piece(void); //lands the piece
void clear_lines(void); 




//Creating the random piece
unsigned int rand = 1; //unsigned just to be safe we do not lose any values
int create_random_piece(void)
{
    rand = rand * 1103515245 + 12345; // recreate of the random function from C
    return rand % 7; // number of tetris pieces so we get a number from 0 to 6
}

//Current piece
int cur_piece_type, cur_piece_rot , cur_piece_col , cur_piece_row;// all current piece variables, col,row the start of the 4x4 box
int next_piece_type; //Type of the next piece to preview it in the prieveiw bo
int game_over; // If 1 gameover 

//Called when a new piece must appear
void spawn(void)
{
    cur_piece_type = next_piece_type;
    next_piece_type = create_random_piece();
    //Spawn the new piece in the middle of the first row wihth no rotation
    cur_piece_rot = 0;
    cur_piece_col = 3;  //the sqare of a piece is 4x4 so the middle is basically 3 form 0 to 9
    cur_piece_row = 0; //top row 0 
    //Check if a new block can spawn
    if(piece_fits(cur_piece_type, cur_piece_rot, cur_piece_col, cur_piece_row) == 0)
        game_over = 1;
}

//Resets score board and assignes and spawns the first piece

int cleared_lines; //score counter
void board_reset(void)
{
    
    for(int tetris_rows = 0; tetris_rows < BOARD_ROWS; tetris_rows ++)
        for(int tetris_cols = 0; tetris_cols < BOARD_COLS; tetris_cols++)
            grid[tetris_rows][tetris_cols] = 0; //black
    
    cleared_lines = 0;
    game_over = 0;
    next_piece_type = create_random_piece();  //spawn needs a iece to take
    spawn(); //set next piece to current and check if it is allowd to spawn  
}

//Move a falling piece left to right
//If it can move move it and return 1 so main knows it was moved and if not retrn 0 so main knows it was not moved
int board_horizontal(int movehor)
{
    if(game_over == 1)
        return 0;

    //Checks if when the piece is moved it fits(col+movehor)
    if(piece_fits(cur_piece_type, cur_piece_rot, cur_piece_col + movehor, cur_piece_row) == 1)
    {
        cur_piece_col += movehor; //moves the piece
        return 1; //gives the flag to main tha the piece can and was moved
    }
    return 0; //piece couldnt be moved
}

//Rotation of a piece
int board_rotate(void)
{
    if(game_over == 1)
        return 0;

    //Moves to the next rotation and wraps around
    int new_rot = (cur_piece_rot + 1) % 4;
    //Calls piecefits with the new rot and checks if it can fit.
    if(piece_fits(cur_piece_type, new_rot, cur_piece_col , cur_piece_row) == 1)
    {
        cur_piece_rot = new_rot; //save the ne rotation since it is possible
        return 1; //could ans has been rotated
    }
    
    return 0; //cannot rotate
}

//Moves the piece vertically, lands it if needed, locks the squares,clears full rows,bring next piece
int board_vertical(void)
{
    if(game_over == 1)
        return 0;
    
    //Checks if the piece fits one row below it
    if(piece_fits(cur_piece_type, cur_piece_rot, cur_piece_col, cur_piece_row + 1) == 1)
    {
        cur_piece_row += 1; //Moves it one below
        return 0; //piece has not landed yet
    }
    lock_piece(); //the piece becomes part of the grid 
    clear_lines();//clears full lines and moves everything else accordigly
    spawn(); //next piece spawn
    return 1;
}

//Make the landing piece from a piece to just filled squares in the board
void lock_piece(void)
{
    for(int square = 0; square < 16; square++)
    {
        //check if each square is empty or full if empty skip and go to the next
        if(piece_block(cur_piece_type, cur_piece_rot, square) == 0)
            continue;
        int col = cur_piece_col + square % 4; //get the actual column in the board of the square we are checking
        int row = cur_piece_row + square / 4; //get the actual row in the board of the square we are checking
        grid[row][col] = 1; //1 = white, 0 = empty
}
}
// Check all rows from bottom to the top if one is full clear it and everything above it goes one down and the cleared lines are incrmented
void clear_lines(void)
{
     int full; 
    for(int tetris_rows = BOARD_ROWS - 1; tetris_rows >= 0; tetris_rows--)
    {
       full = 1; // assume row is full
       for(int tetris_cols = 0; tetris_cols < BOARD_COLS; tetris_cols++)
       {
            if(grid[tetris_rows][tetris_cols] == 0)
            {
            full = 0;//if 1 square is found that is 0 the row is not full so full = 0
            break; // no need to check every other square
            }
        }
        if(full == 0)
            continue;
        for(int r = tetris_rows; r > 0; r--)
            for(int cols = 0; cols < BOARD_COLS; cols++)
                grid[r][cols] = grid[r - 1][cols];
        
        //So the problem is that the top row always gets copied below so there are 2 the same, so just clear the top row
        //This will be visible only if the top row is filled with something
        for(int cols = 0; cols < BOARD_COLS; cols++)
            grid[0][cols] = 0;

        cleared_lines++; //increments score
        tetris_rows++; //checks the same row because when a line breaks it can be again full
    }
}

//The functions that all the other modules see
//We need then to transport variables and their values to other modules

//The state of a specific square in the grid

char board_square(int col, int row)
{
    return grid[row][col];
}

//Give the current piece properties through pointers as c cannot return 4 values at once
//This function is used from render to draw the current piece that is falling
void board_current_piece(int *type, int *rotation, int *col, int *row)
{
    *type = cur_piece_type;
    *rotation = cur_piece_rot;
    *col = cur_piece_col;
    *row = cur_piece_row;
}

//Gives the next piece to render
int board_next_piece(void)
{
    return next_piece_type; //for the preview box
}

//Fetches the current score
int board_score(void)
{
    return cleared_lines; //rows cleared so far so the score
}

//Fethes if the game is over
int board_game_over(void)
{
    return game_over; //game over
}



