#ifndef __D_ARRAY__
#define __D_ARRAY__

#include <stdio.h>
#include <string.h> 

#include "command.h"

typedef struct d_array * D_ARRAY;

D_ARRAY init_array(int size);

D_ARRAY array_insert(D_ARRAY conjunto, COMMAND c);

void free_array(D_ARRAY l);

int getPos(D_ARRAY l);

COMMAND* getArray(D_ARRAY l);

#endif