#include <xinu.h>

#if EJ_Lab2
did32 pipcreate() {
    // LAB2: TODO
	intmask 	mask;    	/* Interrupt mask		*/
	mask = disable();
    // 1. Check Pipe Table
    // 2. Select a free pipe 
    did32 devpipe  = -1 ;
    struct pipe_t* cur ;
    int i ; 
    //kprintf(" Pipe is creating \n") ; 
    for( i = 0 ; i < MAXPIPES ; i ++ ){
        if( pipe_tables[i].state == PIPE_FREE ){
            cur = &pipe_tables[i] ; 
            cur->state = PIPE_USED ; 
            cur->creater_pid = currpid ;  
            cur->pip_head = cur->pipbuf ; 
            cur->pip_tail = cur->pip_head ;

            devpipe = PIPELINE0 + i ; 
            break ; 
        }
    }
    kprintf(" Pipe is bound to device %d \n" , i ) ; 

    if( devpipe == -1 ){
        kprintf(" Pipes are all busy \n") ; 
        restore(mask);
        return SYSERR ; 
    }

    // 3. create Semephore 
    cur->Sender_sema = semcreate(PIPE_SIZE) ; 
    cur->Reader_sema = semcreate(0) ; 
    
    restore(mask);
    return devpipe;
}
#endif
