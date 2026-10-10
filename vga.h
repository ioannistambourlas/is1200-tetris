//Header file for VGA-ANTREAS

//include guard,if vga_h not defined define now.to prevent compiler from doing it more than once
#ifndef VGA_H
#define VGA_H

//resolution,from reg 0x4000108
#define SCREEN_W 320
#define SCREEN_H 240

//colours,rrrgggbb

#define BLACK   0x00//all zeros
#define WHITE   0xFF//all ones
#define GREY    0x92//10010010

//headers of functions in vga.c so the funcitons are visible to other files aswell,with #include
void vga_rect(int startingx,int startingy,int width,int height,unsigned char colour);//colours is unsigned char,because in c is 8 bits and numbers from 0-255 not like signed,we would miss some colours,and int is 4 bytes       
void vga_clear(unsigned char colour);

#endif//ends the initial if