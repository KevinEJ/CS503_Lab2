#include <xinu.h>

devcall pipgetc(struct dentry *devptr) {
    // LAB2: TODO
	char	ch;			/* Character to return		*/
	struct	pipe_t	*pipeptr ;		/* Pointer to ttytab entry	*/
	pipeptr = &pipe_tables[devptr->dvminor];
    
    if( currpid != pipeptr->reader_pid )
        return SYSERR ; 
    if( pipeptr->state != PIPE_CONNECTED )
        return SYSERR ; 

    wait(pipeptr->Reader_sema);
	ch = *pipeptr->pip_head++;
	
    if (pipeptr->pip_head >= &pipeptr->pipbuf[PIPE_SIZE]) {
		pipeptr->pip_head = pipeptr->pipbuf;
	}
    signal(pipeptr->Sender_sema) ;
    
	return (devcall)ch;
}

