#ifndef __READER__
#define __READER__

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include "dynamicArray.h"
#include "command.h"

D_ARRAY readInput(char* s);


#endif