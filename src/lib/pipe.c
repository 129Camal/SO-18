#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>

#include "pipe.h"

struct pipe {
	int pline[2];
};

PIPE create_pipe(){
	PIPE p = malloc(sizeof (struct pipe));
	if(pipe(p->pline)){
		perror("Error creating pipe");
		exit(-1);
	}
	return p;
}

int getpREnd(PIPE p){
	return p->pline[0];
}

int getpWEnd(PIPE p){
	return p->pline[1];
}

void closeRPipe(PIPE p){
	if(p)
	close(p->pline[0]);
}

void closeWPipe(PIPE p){
	if(p)
	close(p->pline[1]);
}









