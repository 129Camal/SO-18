#ifndef __PIPE__
#define __PIPE__

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct pipe * PIPE;

PIPE create_pipe();

int getpREnd(PIPE p);

int getpWEnd(PIPE p);

void closeRPipe(PIPE p);

void closeWPipe(PIPE p);

#endif
