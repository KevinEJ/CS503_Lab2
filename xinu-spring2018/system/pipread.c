#include <xinu.h>

uint32 pipread(struct dentry *devptr, char* buf, uint32 len) {
    // LAB2: TODO
	//struct	pipe_t	*pipeptr ;		/* Pointer to ttytab entry	*/
	int32	nread;			/* Number of characters read	*/
	char	ch;			/* Next input character		*/
	//pipeptr = &pipe_tables[devptr->dvminor];

	if( len < 0 ) {
		return SYSERR;
	}else if( len == 0 ){
        return 0  ; 
    }

	nread = 0;
	while ( ( nread < len ) ) {
		ch = pipgetc(devptr);
		if( ch == SYSERR ) {  return SYSERR ; }
        *buf++ = ch;
		nread++;
	}
	return nread;
}
    
