//coauthored

//inclue  the header files so we have access everywhere we need
#include"io.h"//timer,sweitches,button,displays
#include"board.h"//game rules
#include"render.h"//drawing
#include "perf.h"

#define FALL_TICKS 50 //piece falls every 50 ticks,50x10ms=0.5 sec
#define SW_RIGHT 0x1//bit0=sw0
#define SW_LEFT 0x2//bit1=sw1

void handle_interrupt(unsigned cause){}//for boot.s,for the build to not fail,even though empty


void create_new_game(void){

    board_reset();//all 200 cells 0,score 0,gameover 0
    render_frame();//draws black screen adn grey frames
    render_game();//draws the falling piece and ,next piece,no landed pieces draw now
    io_set_number(0);//all displays show 0


}


int main(void){
    
    perf_tests(); //Run the tests

    io_timer_init();//start the 10ms timer
    create_new_game();//starts the first game

    int prev_switches=io_switches();//save the state of the switches and button ,so we know when the state changes
    int prev_button=io_button();
    int ticks=0;

    while(1)//game loop ,runs every 10ms(one tick)
    {   
        if(io_tick()==0)
            continue;//skip the rest of the while go at the top->10ms have not passed ,do nothing

        int switches=io_switches();//get the values of switcehs and buttons
        int button=io_button();

        if(board_game_over()==1)//game over?
        {
            if(button==1&&prev_button==0){//does the button state change from 0 to 1
                create_new_game();
                ticks=0;//reset num of ticks
            }
        }
        else//game not over
        {
            int changed=0;//becomes 1 if anything moved so we know to redraw

            if((switches & SW_LEFT) != (prev_switches & SW_LEFT))//if sw1 changed state,move left
            {

                if(board_horizontal(-1)==1)//if it can move 1 left ,board horizntoal moves it
                    changed=1;

            }

            if((switches & SW_RIGHT) != (prev_switches & SW_RIGHT))//if sw0 changed state,move RIGHT
            {

                if(board_horizontal(1)==1)//if it can move 1 RIGHT ,board horizntoal moves it
                    changed=1;

            }

            if(button==1&&prev_button==0){
                if(board_rotate()==1)
                    changed=1;


            }

            ticks++;
            if(ticks==FALL_TICKS){
                ticks=0;
                board_vertical();//move down,or land

                changed=1;

        

            }
            //redraw
            if(changed==1){

                render_game();//redraws the board and next box
                io_set_number(board_score());//fetches the score and prints it,even if the score didnt change,but something else
            }

    

        }
    prev_switches=switches;
    prev_button=button;

    }



























}
