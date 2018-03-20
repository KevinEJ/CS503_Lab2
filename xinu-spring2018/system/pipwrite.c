#include <xinu.h>

uint32 pipwrite(struct dentry *devptr, char* buf, uint32 len) {
    // LAB2: TODO
	//struct	pipe_t	*pipeptr ;		/* Pointer to ttytab entry	*/
	//pipeptr = &pipe_tables[devptr->dvminor];
    
    if (len < 0) {
		return SYSERR;
	} else if (len == 0){
		return 0 ;
	}
	
    /* Write count characters one at a time */

	for (; len > 0 ; len--) {
		devcall check = pipputc(devptr, *buf++);
	    if( check == SYSERR ){ return SYSERR ;  }
    }
	return len;
    
}
