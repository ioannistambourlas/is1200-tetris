//functions of render-ANTREAS
//renders the frames on the screen and renders the whole game on the screen
#include"render.h"
#include"vga.h"
#include"pieces.h"
#include"board.h"

#define CELL 10//the board is made up of 10x20 cells,each cell is 10x10 pixels,we got htat from screen height =240 and rows=20->max height of cells could be 12 pixels,for ease of use ,for a some clear space on the left and on the right we put 10
#define BOARD_STARTING_X 110//screen width=320,cols=10,width of cells=10,320-10x10=220->starts at 110 ,100 taken by the board,110 to reach the other end
#define BOARD_STARTING_Y 20//same idea
#define NEXT_PIECE_BOX_X 230//110+100+20,figured by trial and error
#define NEXT_PIECE_BOX_Y 30//trial and error 

void draw_cell(int starting_x,int starting_y,int col,int row,unsigned char colour){//local funciton that is used in render game,starting x,y are erither,110,20 or 230,30 ,showing board or next piece box

    /*col*CELL is done to find where the block starts in pixels */
    vga_rect(starting_x+col*CELL,starting_y+row*CELL,CELL-1,CELL-1,colour);//cell-1 is the widdth and height,we leave 1 pixel unpainted so we can differentiate the blocks

}

void render_frame(void){
    vga_clear(BLACK);//make the whole screen black

    //vga_rect is creating a filled coloured rectangle,thus we have to do a bit bigger gray rectangle ,with a smaller black inside it so it looks like a frame
    //board

    vga_rect(BOARD_STARTING_X-3,BOARD_STARTING_Y-3,BOARD_COLS*CELL+6,BOARD_ROWS*CELL+6,GREY);//bigger grey
    vga_rect(BOARD_STARTING_X-1,BOARD_STARTING_Y-1,BOARD_COLS*CELL+2,BOARD_ROWS*CELL+2,BLACK);//smaller black
    
    //results in a 2 pixel wide border

    vga_rect(NEXT_PIECE_BOX_X-3,NEXT_PIECE_BOX_Y-3,4*CELL+6,4*CELL+6,GREY);//same idea for next piece box
    vga_rect(NEXT_PIECE_BOX_X-1,NEXT_PIECE_BOX_Y-1,4*CELL+2,4*CELL+2,BLACK);



}

void render_game(void){//redraws the board and the next box

    //ask board about the falling piece and if the game is over.
    int type,rotation,piece_col,piece_row;
    board_current_piece(&type,&rotation,&piece_col,&piece_row);//piece col and row are the where the top left corener of the 4x4 box is of each tetrominoe
    int is_game_over=board_game_over();

    //the board
    for(int tetris_row=0;tetris_row<BOARD_ROWS;tetris_row++){
        for(int tetris_col=0;tetris_col<BOARD_COLS;tetris_col++){

            unsigned char colour=BLACK;
            if(board_square(tetris_col,tetris_row)==1)//1 = a landed block (board_square only knows about landed blocks(those saved into grid))
                 colour=WHITE;
            
            //is the falling piece in this cell ,i.e am I in the in any of the squares of the 4x4 box of the falling piece?
            int box_col=tetris_col-piece_col;//calculate a col value for the box
            int box_row=tetris_row-piece_row;

            //now check if the current cell is isnide the box
            if(is_game_over==0&&box_col>=0&&box_col<4&&box_row>=0&&box_row<4){//inside the box,so the calculation row*4+boxcol,calculates teh correct square from 0-15 ,so we get reliable results
                if(piece_block(type,rotation,box_row*4+box_col)==1)//==1 means cell filled
                    colour=WHITE;//falling piece here,drawn white

            }

            //gamover check
            if(is_game_over==1&&colour!=0)//IF gameover,make all teh colored squares  grey
                colour=GREY;//every piece that wasnt black,i.e it was drawn becomes gray


            draw_cell(BOARD_STARTING_X,BOARD_STARTING_Y,tetris_col,tetris_row,colour);//call the local functin once in the end to fill the cell

        }



    }

    //the next piece box
    int next_piece_type=board_next_piece();
    for(int square=0;square<16;square++){//for each of the 16 squares of the new pieces' 4x4 box
        unsigned char colour=BLACK;//intialiaze the colour

        if(piece_block(next_piece_type,0,square)==1){//if square filled
            colour=WHITE;//fille the square white
            
        }

        draw_cell(NEXT_PIECE_BOX_X,NEXT_PIECE_BOX_Y,square%4,square/4,colour);




    }





}