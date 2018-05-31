#ifndef __EXECUTE__
#define __EXECUTE__


#include "command.h"
#include "utility.h"
#include "pipe.h"
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

int execute_one_command (COMMAND cmd);

int execute_two_commands (COMMAND cmdR,COMMAND cmdW);

#endif
