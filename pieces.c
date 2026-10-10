// Check if a squre of the piece is full, check if the piece fits, holds the shapes and rotations


#include "pieces.h"
#include "board.h"

int SHAPES[NUM_PIECES][4] = {//rotation is clockwise
    {0x0F00, 0x2222, 0x00F0, 0x4444},   //  I
    {0x44C0, 0x8E00, 0x6440, 0x0E20},   //  J
    {0x4460, 0x0E80, 0xC440, 0x2E00},   //  L
    {0xCC00, 0xCC00, 0xCC00, 0xCC00},   //  O (same in all rotations)
    {0x06C0, 0x8C40, 0x6C00, 0x4620},   //  S
    {0x0E40, 0x4C40, 0x4E00, 0x4640},   //  T
    {0x0C60, 0x4C80, 0xC600, 0x2640},   //  Z
};


int piece_block(int type,int rotation,int square){

    return(SHAPES[type][rotation]>>(15-square))&1;//top left position is 0,tbottom right is 15,we want the square=square,->we have to shift 15-square bits to the right so the bits we want is taken with a bitwise and with 1

}



int piece_fits(int type,int rotation,int tetriscol,int tetrisrow){

    for(int square=0;square<16;square++){
        if(piece_block(type,rotation,square)==0)//square empty skip this iteration of the loop and go to the next one
            continue;


        //calculate where square will land in real board
        int col=tetriscol+ square%4;//%4 column inside the box
        int row=tetrisrow+ square/4;// /4 row inside the box
    
        if (col<0||col>=BOARD_COLS)//check if went too left or too right
            return 0;

        if(row>=BOARD_ROWS)//through the floor,row 0 is at the top
            return 0;
        if(row>=0&&board_square(col,row)!=0)//of cell full
            return 0 ;



    }
    return 1;


}
