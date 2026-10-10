//this is the header file of render,which  is the module that draws the game on the screen-ANTREAS

#ifndef RENDER_H
#define RENDER_H


void render_frame(void);//its called once per game to clear the screen, render the gray surrounding boxes for the board and enxt box

void render_game(void);//everytime something changes this is called,drawing all board cells with the falling piece on top,and the next piece in the next box,also in the game over ,existing blocks are drawn dark gray

#endif