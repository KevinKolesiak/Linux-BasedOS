#include "syscall.h"

/*
 * halt
 *   DESCRIPTION: 
 *   INPUTS:
 *   OUTPUTS: none
 *   RETURN VALUE: 
 *   SIDE EFFECTS: none
 */
int32_t halt (uint8_t status) {
    // uint32_t parent_id;

    // /*restore parent data*/
    // parent_id = pcb_array[curr_pid].par_id;
    // curr_pid = parent_id;

    

    // /*base pointer?*/
    // /*restore parent paging*/
    // //Set new page (first addr at 0x400)
    // kerntry.p_addr = pageHold << KENTRY_SHIFT;
    // kerntry.ps = 1;
    // kerntry.a = 0;
    // kerntry.pcd = 0;
    // kerntry.pwt = 0;
    // kerntry.us = 1;
    // kerntry.rw = 1;
    // kerntry.p = 1;
    // newEntry = combine_kir_entry(kerntry);
    // pagedir[USER_SPACE] = newEntry;
    // //flush tlb ???
    // flush_tlb();



    // /*close any relevant FDs*/
    // pcb_array[curr_pid].



    // /*Jump to execute return*/

    return -1;
}


/*
 * system_execute
 *   DESCRIPTION: 
 *   INPUTS:
 *   OUTPUTS: none
 *   RETURN VALUE: 
 *   SIDE EFFECTS: none
 */
int32_t
execute(const uint8_t *command) {
        
    uint8_t *cmdHold;
    uint8_t *cmdArgs;
    uint8_t *file;
    uint32_t i, j, newEntry, pageHold, basePointer;
    uint8_t *buf;
    dentry_t *dentry;
    pdir_entry_t kerntry;


    //parent base pointer
    basePointer = retrieveBasePointer();

    if(command == NULL) {
        return -1;
    }
    /*Parse Args*/
    cmdHold = command;
    //skip spaces
    for(i = 0; i < COMMAND_MAX; i++) {
        if(cmdHold == ' ') {
            cmdHold++;
        } else { 
            break;
        }
    } 
    file = cmdHold;
    //go to end of filename
    while(*cmdHold != ' ' || *cmdHold != '\n' || *cmdHold != '\0') {
        cmdHold++;
    }
    //set end of filename
    *cmdHold = '\0';
    //skip spaces (NOTE: maybe this goes to far? Maybe it will have infinite spaces? [when there are no args])
    for(i = 0; i < COMMAND_MAX; i++) {
        if(cmdHold == ' ') {
            cmdHold++;
        } else { 
            break;
        }
    } 

    cmdArgs = cmdHold;
    //go to end of args
    while(*cmdHold != ' ' || *cmdHold != '\n' || *cmdHold != '\0') {
        cmdHold++;
    }
    //set end of args
    *cmdHold = '\0';

    // args will be passed into get args to the program

    /*Executable Check*/
    //set dentry
    if(read_dentry_by_name(file, dentry) == -1)
        return -1;
    if(read_data(dentry->inode_num,0,buf,4) == -1) 
        return -1;
    if(buf != EXEC_VAL) 
        return -1;
    if(dentry->filetype != 2)
        return -1;

    /*set up program paging*/
    //Find first open process (0-5)
    for(i = 0; i < PROG_MAX; i++) {
        if(pcb_array[i].in_use == 0) {
            curr_pid = i;
            break;
        }
    }
    //FAILED TO RUN (could be another error return (-2))
    if(i == PROG_MAX)
        return -1;

    //pages in use
    pageHold = curr_pid;
    pageHold += PAGES_DEFAULT_USE;
    //Set new page (first addr at 0x400)
    kerntry.p_addr = pageHold << KENTRY_SHIFT;
    kerntry.ps = 1;
    kerntry.a = 0;
    kerntry.pcd = 0;
    kerntry.pwt = 0;
    kerntry.us = 1;
    kerntry.rw = 1;
    kerntry.p = 1;
    newEntry = combine_dir_entry(kerntry);
    pagedir[USER_SPACE] = newEntry;
    //flush tlb
    flush_tlb();

    /*load file into memory*/ /*aka User-level program loader*/
    //once have the page read_data
    
    // load from FS to program page (how to get process number)

    inode_t* file_inode = (inode_t*)(startinode + dentry->inode_num);

    read_data(dentry->inode_num, 0, (uint8_t*)PRGRM_IMG_START, file_inode->length);

    /*Create PCB*/

    /*tss*/
    //change esp0 to the value the stack pointer 
    tss.esp0 = pcb_array[curr_pid].stack_ptr;
    //change ss0
    tss.ss0 = KERNEL_DS; 

    
    /*context switch (IN x86)*/
    // create its own context switch stack 
    
    read_data(dentry->inode_num, 24, buf, 4); // buf holds entry point in program

    pcb_array[curr_pid].inst_ptr = *((uint32_t*)buf);


    // IRET 
    iret_context(*((uint32_t*)buf));

    return -1;
}



/*
 * read
 *   DESCRIPTION: 
 *   INPUTS:
 *   OUTPUTS: none
 *   RETURN VALUE: 
 *   SIDE EFFECTS: none
 */
int32_t read (int32_t fd, void* buf, int32_t nbytes) {
    return -1;
}

/*
 * write
 *   DESCRIPTION: 
 *   INPUTS:
 *   OUTPUTS: none
 *   RETURN VALUE: 
 *   SIDE EFFECTS: none
 */
int32_t write (int32_t fd, const void* buf, int32_t nbytes) {
    return -1;
}

/*
 * open
 *   DESCRIPTION: puts the file into the pcb's file array
 *   INPUTS: filename
 *   OUTPUTS: index in the file array, or -1 if fail
 *   RETURN VALUE: int
 *   SIDE EFFECTS: changes the fda of curpcb
 */
int32_t open (const uint8_t* filename) {
    // uint32_t type;
    // file_op_t fops;
    // //open_file will do most of the work because need dentry info
    // int fdindex = open_file(filename);

    // if(fdindex == -1){
    //     return -1;
    // }

    // //need to set the file operations depending on file type
    // pcb_t* curpcb = pcb_array[curr_pid];

    // type = curpcb->fda[fdindex].file_type;
    // switch(type){
    //     case 0: //if type 0, then rtc
    //         //fops = ??
    //     case 1: //if type 1, then boot block (dir)
    //         //fops
    //     case 2: //type 2 is normal files
    //         //fops
    //     default:
    //         printf("open fail, invalid file type");
    //         return -1;
    // }

    // //curpcb->fda[fdindex].file_op_ptr = fops;

    // return fdindex;
    return -1;
}

/*
 * close
 *   DESCRIPTION: 
 *   INPUTS:
 *   OUTPUTS: none
 *   RETURN VALUE: 
 *   SIDE EFFECTS: none
 */
int32_t close (int32_t fd) {
    // //check input valid
    // if(fd > 7 || fd < 2){
    //     printf("close fail, invalid fd");
    //     return -1;
    // }

    // //use the close operation from the file ops

    return -1;
}

/*
 * getargs
 *   DESCRIPTION: 
 *   INPUTS:
 *   OUTPUTS: none
 *   RETURN VALUE: 
 *   SIDE EFFECTS: none
 */
int32_t getargs (uint8_t* buf, int32_t nbytes) {
    return -1;
}

/*
 * vidmap
 *   DESCRIPTION: 
 *   INPUTS:
 *   OUTPUTS: none
 *   RETURN VALUE: 
 *   SIDE EFFECTS: none
 */
int32_t vidmap (uint8_t** screen_start) {
    return -1;
}

/*
 * set_handler
 *   DESCRIPTION: 
 *   INPUTS:
 *   OUTPUTS: none
 *   RETURN VALUE: 
 *   SIDE EFFECTS: none
 */
int32_t set_handler(int32_t signum, void* handler_address) {
    return -1;
}

/*
 * sigreturn
 *   DESCRIPTION: 
 *   INPUTS:
 *   OUTPUTS: none
 *   RETURN VALUE: 
 *   SIDE EFFECTS: none
 */
int32_t sigreturn (void) {
    return -1;
}



