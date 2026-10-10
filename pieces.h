//pieces header-ANTREAS
//shapes,collisions check

#ifndef PIECES_H//same procedure as other headers
#define PIECES_H

#define NUM_PIECES 7//I,J,L,O,S,T,Z

int piece_block(int type,int rotation,int square);//is square ,(out of 0-15) of a 4x4 box filled?in that rotation


int piece_fits(int type,int rotation,int tetriscol,int tetrisrow);//does this piece fit at this row and column?

#endif

