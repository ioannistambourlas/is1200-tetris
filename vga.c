//functions of of vga-ANTREAS
//handles the vga connection and vga printing

#include "vga.h"//has access in everything in vga.h

static volatile unsigned char *const screen=(volatile unsigned char *)0x08000000;//static-only visible in vga.c,volatile -never skip a write,unsigned char-pointer to 1 byte,*const-pointer never changes

void vga_rect(int startingx,int startingy, int width, int height, unsigned char colour){

    //screen fixes of going over the edge.


    if(startingx<0){    //if print wants to be to the left of the screen(=previous row) start it from zero and reduce the width,so oyu dont fuck up things on the right
            
        width+=startingx;
        startingx=0;
    }

    if(startingy<0){    
            
        height+=startingy;
        startingy=0;
    }


    if(startingx+width>SCREEN_W){//for right edge
        width=SCREEN_W-startingx;

    }

    if(startingy+height>SCREEN_H){//for bottom edge
        height=SCREEN_H-startingy;

    }

  

    //actual filling

    //fill all the x in the same y ,then move to the next y
    for(int y=startingy;y<startingy+height;y++){
        for(int x=startingx;x<startingx+width;x++){
            screen[y*SCREEN_W + x]=colour;//vga uses consecutive mode,meaning:memory is just a long line of bytes(with no gaps like x-y mode),thus to reach a specific pixel,you have to "skip" y rows and then move x pixels to the right
        }

    }
}

void vga_clear(unsigned char colour){//just start at the top left corener and treat the whole screen as a rectangle
    vga_rect(0,0,SCREEN_W,SCREEN_H,colour);
}














