/* pipe.h: contains all the macros and definition for the pipe type in XINU */
#ifndef PIPE
#define PIPE

#define MAXPIPES 10
#define PIPE_SIZE 1024

#define EJ_Lab2 1

enum pipe_state_t {
	PIPE_FREE,
	PIPE_USED,
	PIPE_CONNECTED,
	PIPE_HALF_CONNECTED,
	PIPE_OTHER
};

struct pipe_t {
    /*pipe_t(pipid32 t){
        pipid = t ; 
        pipbuf = new char[PIPE_SIZE] ; 
        pip_head = pipbuf ; 
        pip_tail = pipbuf ; 
    }*/
	pipid32 pipid;			    // Pipe ID
	enum pipe_state_t state;	// Pipe state defined by the enum
    // LAB2: TODO: Fill the structure with the fields as required.
    pid32 creater_pid ;
    pid32 writer_pid ;
    pid32 reader_pid ;
    sid32 Sender_sema ; 
    sid32 Reader_sema ;
    char pipbuf[PIPE_SIZE] ;
    //char *pipbuf    ;
    char *pip_head  ; 
    char *pip_tail  ; 
};

extern struct pipe_t pipe_tables[MAXPIPES];	// Table for all pipes
#endif
