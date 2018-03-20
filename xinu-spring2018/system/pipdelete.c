#include <xinu.h>

status pipdelete(did32 devpipe) {
    // LAB2: TODO
	intmask 	mask;    	/* Interrupt mask		*/
	mask = disable();
	// 1. check if the caller is valid
    struct pipe_t* cur ; 
    cur = &pipe_tables[devpipe-PIPELINE0] ;
    
    //kprintf(" Cur proc [ %d ] wants to delete the pipe[%d]. \n" , currpid , devpipe-PIPELINE0) ; 

    if( currpid != cur->creater_pid &&
        currpid != cur->reader_pid &&
        currpid != cur->writer_pid){
        kprintf(" This process cannot delete this pipe. ( not the owner or reader or writer \n") ; 
        restore(mask);
        return SYSERR ; 
    }

    pipdisconnect(devpipe) ; 

    cur->state = PIPE_FREE ;   
    semdelete( cur ->Reader_sema);
    semdelete( cur ->Sender_sema);

    restore(mask);
    return OK;
}
