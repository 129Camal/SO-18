#ifndef __READER__
#define __READER__


#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include "dynamicArray.h"
#include "command.h"
#include "utility.h"

D_ARRAY readInput(int file);


#endif