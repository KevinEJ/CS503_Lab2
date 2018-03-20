#include <xinu.h>

status pipdisconnect(did32 devpipe) {
    // LAB2: TODO
	intmask 	mask;    	/* Interrupt mask		*/
    struct pipe_t* cur ; 
    
    //kprintf(" Cur proc [ %d ] wants to disconnect the pipe[%d]. \n" , currpid , devpipe-PIPELINE0) ; 
     
    cur = &pipe_tables[devpipe-PIPELINE0] ;
	
    if( currpid != cur->creater_pid &&
        currpid != cur->reader_pid &&
        currpid != cur->writer_pid){
        kprintf(" This process cannot disconnect this pipe. ( not the owner or reader or writer \n") ; 
        return SYSERR ; 
    }
    if( cur->state != PIPE_CONNECTED ){
        //kprintf(" This pipe cannot be disconnect. ( not connected\n") ; 
        return SYSERR ; 
    }

    //wait until disconnection is valid 
    
    if( currpid == cur->writer_pid){
        //while( semcount( cur->Reader_sema) != -1 || semcount(cur->Reader_sema) != 0 ){ 
        int32 count = semcount( cur->Reader_sema ) ; 
        while( count != -1 ){
            if( count == 0 && cur->pip_head == cur->pip_tail )
                break ; 
            count = semcount( cur->Reader_sema ) ; 
        }
    }
	mask = disable();
    cur -> state = PIPE_USED ;
    //proctab[cur->reader_pid].prdesc[0] = stdinput ;  
    //proctab[cur->writer_pid].prdesc[1] = stdoutput ;  
    cur->pip_head = cur->pip_tail ;     
    semreset( cur->Reader_sema , 0           ) ; 
    semreset( cur->Sender_sema , PIPE_SIZE   ) ; 

    restore(mask);
    return OK;
}
