#include <xinu.h>

status pipdisconnect(did32 devpipe) {
    // LAB2: TODO
	//intmask 	mask;    	/* Interrupt mask		*/
    struct pipe_t* cur ; 
    
    //kprintf(" Cur proc [ %d ] wants to disconnect the pipe[%d]. \n" , currpid , devpipe-PIPELINE0) ; 
     
    cur = &pipe_tables[devpipe-PIPELINE0] ;
	
    if( currpid != cur->creater_pid &&
        currpid != cur->reader_pid &&
        currpid != cur->writer_pid){
        kprintf(" This process cannot disconnect this pipe. ( not the owner or reader or writer \n") ; 
        return SYSERR ; 
    }
    if( cur->state != PIPE_CONNECTED && cur->state != PIPE_HALF_CONNECTED){
        //kprintf(" This pipe cannot be disconnect. ( not connected\n") ; 
        return SYSERR ; 
    }

    //1. Check who calls disconnet();
    if( currpid == cur->creater_pid ){
        kprintf("[DISCONNECT] Creater disconnect \n") ; 
        // not sure what to do.
        // Fully disconnect 
    }else if( currpid == cur->writer_pid ){
        // Set pipe_state to HALF_CONNECT 
        // if( buf is already empty -> fully disconnet )
        if( cur->pip_head == cur -> pip_tail ){
            kprintf("[DISCONNECT] Writer[%d] fully disconnect \n" , currpid ) ; 
            cur->state = PIPE_USED ; 
            // Delete the pipe.
            pipdelete(devpipe) ;             
        }else{
            kprintf("[DISCONNECT] Writer[%d] hald disconnect \n" , currpid ) ; 
            cur->state = PIPE_HALF_CONNECTED ; 
            // Then disconnect the reader from the pipe.
        }
    }else if( currpid == cur->reader_pid ){
        kprintf("[DISCONNECT] Reader[%d] disconnect \n" , currpid) ; 
        // Don't care about the reader 
        // Disconnect everything
        cur->state = PIPE_USED ; 
        // Delete the pipe.
        pipdelete(devpipe) ; 
    }else{
        kprintf("[DISCONNET] ERROR !!!\n"); 
    }
    
    
	//mask = disable();
    //cur -> state = PIPE_USED ;
    //proctab[cur->reader_pid].prdesc[0] = stdinput ;  
    //proctab[cur->writer_pid].prdesc[1] = stdoutput ;  
    //cur->pip_head = cur->pip_tail ;     
    //semreset( cur->Reader_sema , 0           ) ; 
    //semreset( cur->Sender_sema , PIPE_SIZE   ) ; 

    //restore(mask);
    return OK;
}
