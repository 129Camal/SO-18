#ifndef __EXECUTE__
#define __EXECUTE__

#include "command.h"
#include "pipe.h"
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

int execute_no_pipe (COMMAND cmd);

int execute_pipe (COMMAND cmdR,COMMAND cmdW);

#endif
