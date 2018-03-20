#include <xinu.h>

status pipconnect(did32 devpipe , pid32 writer, pid32 reader) {
    // LAB2: TODO
	intmask 	mask;    	/* Interrupt mask		*/
	mask = disable();
    // 1. Check input validation  
	if ( devpipe > PIPELINE9 || devpipe < PIPELINE0 ){
        kprintf("this pipe can not be connected because the did is wrong \n ") ; 
        restore(mask);
        return SYSERR ; 
    }
    if ( writer == reader ) {
        kprintf("this pipe can not be connected because writer == reader \n ") ; 
        restore(mask);
        return SYSERR ; 
    }
    if( pipe_tables[devpipe-PIPELINE0].state != PIPE_USED){
        kprintf("this pipe can not be connected because its state is not USED \n ") ; 
        restore(mask);
        return SYSERR ; 
    }
    // 2. Set variables 
    kprintf(" Connecting Writer [ %d ]  and  Reader [ %d ] \n" , writer, reader ) ; 
    pipe_tables[devpipe-PIPELINE0].state      = PIPE_CONNECTED ; 
    pipe_tables[devpipe-PIPELINE0].writer_pid = writer ; 
    pipe_tables[devpipe-PIPELINE0].reader_pid = reader ; 
    
    proctab[writer].prdesc[1] = devpipe ;
    proctab[reader].prdesc[0] = devpipe ; 
    restore(mask);
    return OK;
}
