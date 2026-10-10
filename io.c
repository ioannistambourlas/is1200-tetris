//functions of io - Ioannis
/*Code used from lab3-
void io_timer_init(void);
int io_switches(void);
int io_button(void);
void io_set_display(int display_number, int value); 
int io_tick(void); polling
*/
//Handles of the the i/o stuff
#include"io.h"


volatile int * STATUS=(volatile int*)0x04000020;
volatile int * CONTROL=(volatile int*)0x04000024;
volatile int * PERIODL=(volatile int*)0x04000028;
volatile int * PERIODH=(volatile int*)0x0400002C;
void io_timer_init(void)
{
    //Period value is 300000-1=299999=0x000493DF
    (*PERIODL)=0X93DF;//Lower 16 bits 
    (*PERIODH)=0X0004;//Upper 16 bits
    (*CONTROL)=0X6;//bit2(start bit) and bit1(cont)=restsat automatically bit0(interrupsts=0)
}

volatile int*SWITCHES =(volatile int*)0x04000010; // address of switches in memory
int io_switches(void)
{   
  return((*SWITCHES)&0x3FF);//0x3ff is the last 10 bits 1 so we maks the bits that the switches
}

volatile int*KEY1 =(volatile int*)0x040000d0; //memory address of Key1

int io_button(void)
{
    return((*KEY1)&0x1); //gets the first bit so key1 which is 1(pressed) or 0(upressed)
}

volatile int*DISPLAY=(volatile int*)0x04000050;

void io_set_display(int display_number, int value)
{
    volatile int *display =DISPLAY+display_number*4;//int moves 4 bytes each +

  switch (value) {
   
  
    case 0:
            (*display)=0X40;
            break;
    case 1:
            (*display)=0X79;
            break;
    case 2:
            (*display)=0X24;
            break;
    case 3:
            (*display)=0X30;
            break;
    case 4:
            (*display)=0X19;
            break;
    case 5:
            (*display)=0X12;
            break;
    case 6:
            (*display)=0X02;
            break;
    case 7:
            (*display)=0X78;
            break;
    case 8:
            (*display)=0X00;
            break;

    case 9:
            (*display)=0X18;
            break;
    case 10:
        (*display)=0xFF;
    }
}

void io_set_number(int score)
{
    for(int i = 0; i < 6; i++)
    {
        io_set_display(i, score % 10); //takes the last digit of the number and prints on the coorsiponding display
        score = score / 10; //chops the last digit f.e 1250/10 = 125 so the next iteration will take the 5 as last digit
    }
}
int io_tick(void)
{
    if((* STATUS) & 0x1) // Bit wise AND  to get bit 0 which is the timeout flag
    {
        //goes in the if only when TO is 1 which means we counted from 299999 to 0
        (*STATUS) = 0; //reset the flag to be able to detect it again
        return 1; //the flag was raised so 10 ms passed
    }
    return 0; // flag not raised
}




