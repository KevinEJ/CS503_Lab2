#include <xinu.h>
extern 

devcall pipputc(struct dentry *devptr, char ch) {
    // LAB2: TODO
	struct	pipe_t	*pipeptr;		/* Pointer to tty control block	*/
	pipeptr = &pipe_tables[devptr->dvminor];

    if( currpid != pipeptr->writer_pid )
        return SYSERR ; 
    if( pipeptr->state != PIPE_CONNECTED )
        return SYSERR ; 

	wait(pipeptr->Sender_sema);		/* Wait	for space in queue */
	*pipeptr->pip_tail++ = ch;

	if (pipeptr->pip_tail >= &pipeptr->pipbuf[PIPE_SIZE]) {
		pipeptr->pip_tail = pipeptr->pipbuf;
	}
    signal(pipeptr->Reader_sema);

    return OK;
}

