/* thread.c - Struct and helper functions for individual threads
 * 
 */

#include "terminal.h"
#include "pit.h"

/*
 * switch_thread
 *   DESCRIPTION: switches process context from one thread to another
 *   INPUTS: 
 *   OUTPUTS: none 
 *   RETURN VALUE: none
 *   SIDE EFFECTS: Context switch so that current process being executed switches 
 */
void switch_thread() {
    
    // uint32_t pid = terminal[curr_thread].t_pid;

    // // spawn shell if pcb is not in use
    // if (pcb_array[pid].in_use == 0){


    //     send_eoi(PIT_IRQ);

    //     uint8_t shellcmd[6] = "shell\0";
    //     execute(shellcmd);

    // }


    // // Context Switch


    // // Store contents from TSS to enable restoration of Process state for the next time slice

    // // saving esp, ebp of finishing process
    // asm volatile(
    //              "movl %%esp, %0;" 
    //              "movl %%ebp, %1;" 
    //              :
    //              :"r"(pcb_array[curr_pid].stack_ptr), "r"(pcb_array[curr_pid].base_ptr)
    //              :
    //              );   

    

    // // update thread to the new one
    // curr_thread = (curr_thread+1)%3;
    // curr_pid = terminal[curr_thread].t_pid;

    // // Switch ESP/EBP to next process’ kernel stack


    // asm volatile(
    //         "movl %0, %%esp;" 
    //         "movl %1, %%ebp;" 
    //         :
    //         :"r"(pcb_array[curr_pid].stack_ptr), "r"(pcb_array[curr_pid].base_ptr)
    //         :
    //         );

    // // Paging:
    // // change virtual program image to point to next program in physical mem
    // // redirect the program image
    



    // // Restore next process’ TSS

    // // tss
    // // Restore TSS contents relevant to Process and store in pcb

    // tss.esp0 = (uint32_t)pcb_array[curr_pid].stack_ptr;
    // tss.ss0  = KERNEL_DS;

    

    // // Flush TLB on process switch





}
