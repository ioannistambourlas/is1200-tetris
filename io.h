//Header file for I/O-Ioannis

#ifndef IO_H
#define IO_H

void io_timer_init(void); //labinit lab3
int io_switches(void); //get_sw lab3
int io_button(void);   //get_btn lab3
void io_set_display(int display_number, int value); //setdisplays lab3 sets one display
void io_set_number(int score);
int io_tick(void);


#endif