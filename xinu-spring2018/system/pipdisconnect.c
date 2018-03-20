#include <xinu.h>

status pipdisconnect(did32 devpipe) {
    // LAB2: TODO
	intmask 	mask;    	/* Interrupt mask		*/
	mask = disable();
    
    struct pipe_t* cur ; 
    cur = &pipe_tables[devpipe-PIPELINE0] ;
	
    if( currpid != cur->creater_pid &&
        currpid != cur->reader_pid &&
        currpid != cur->writer_pid){
        kprintf(" This process cannot delete this pipe. ( not the owner or reader or writer \n") ; 
        return SYSERR ; 
    }
    if( cur->state != PIPE_CONNECTED ){
        //kprintf(" This pipe cannot be disconnect. ( not connected\n") ; 
        return SYSERR ; 
    }
    cur -> state = PIPE_USED ;
    
    if( currpid == cur->writer_pid){
        while( semcount( cur->Reader_sema) != -1 ) ;
    }
    

    //proctab[cur->reader_pid].prdesc[0] = stdinput ;  
    //proctab[cur->writer_pid].prdesc[1] = stdoutput ;  
    
    cur->pip_head = cur->pipbuf ;   
    cur->pip_tail = cur->pipbuf ;   
  
    semreset( cur->Reader_sema , 0           ) ; 
    semreset( cur->Sender_sema , PIPE_SIZE   ) ; 

    restore(mask);
    return OK;
}
