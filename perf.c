//performance analysis
//coauthored

#include "perf.h"
#include "render.h" //render game function
#include "board.h" // reset board function
#include "dtekv-lib.h" //printing


void perf_zero(void)
{
    //asm:assembly, csrw:control status register write, name of register, what to write to it
    asm volatile ("csrw mcycle, x0");   // ticks that passed
    asm volatile ("csrw minstret, x0"); // instructions finished
    asm volatile ("csrw mhpmcounter6, x0");  // In how many cycles the I cache stalled
    asm volatile ("csrw mhpmcounter7, x0");  // In how many cycles the D cache stalled
    asm volatile ("csrw mhpmcounter8, x0");  // In how many cycles the next instruction depended on the previous and did not have the result
    asm volatile ("csrw mhpmcounter9, x0");  // In how many cyclesthe ALU did a long computation like division
}

void perf_print(char * test_name)
{
    unsigned int cycles, instructions, icache_stalls, dcache_stalls, data_hazard_stalls, alu_stalls;
    //read from the csr register and %0 placeholder for the actual value which is saved(=) into a register(r) and later the compiler treates it as a variable(cycles)
    asm volatile ("csrr %0, mcycle"       : "=r"(cycles));
    asm volatile ("csrr %0, minstret"     : "=r"(instructions));
    asm volatile ("csrr %0, mhpmcounter6" : "=r"(icache_stalls));
    asm volatile ("csrr %0, mhpmcounter7" : "=r"(dcache_stalls));
    asm volatile ("csrr %0, mhpmcounter8" : "=r"(data_hazard_stalls));
    asm volatile ("csrr %0, mhpmcounter9" : "=r"(alu_stalls));
    
    //Print the test name
    print("\n");
    print(test_name);
    print("\n");
    // Print the number of cycles
    print("cycles: ");            
    print_dec(cycles);             
    print("\n");
    //Print the number of instructuins completed
    print("instructions: ");       
    print_dec(instructions);       
    print("\n");
    //Print I cache stalls
    print("I-cache stalls: ");     
    print_dec(icache_stalls);      
    print("\n");
    //Print D cache stalls
    print("D-cache stalls: ");     
    print_dec(dcache_stalls);      
    print("\n");
    //Print data hazard stalls
    print("data hazard stalls: "); 
    print_dec(data_hazard_stalls); 
    print("\n");
    //Print ALU stalls
    print("ALU stalls: ");         
    print_dec(alu_stalls);        
    print("\n");
}

//Actual testing
void perf_tests(void)
{
    for(int i = 0; i < 3; i++)
    {
        print("\nTest number =");
        print_dec(i+1);
        print("\n");

        //First test the render frame function
        perf_zero();
        render_frame();
        perf_print("RENDER FRAME");

       //Then test the render game function
        board_reset(); //reset the board to empty                
        perf_zero();
        render_game();
        perf_print("RENDER GAME");
    }
    print("\nTests done. TIME TO PLAY!\n");
}


