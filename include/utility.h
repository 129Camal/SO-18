#ifndef __UTILITY__
#define __UTILITY__
#define MAXSIZE 1024

#include <stdlib.h>
#include <string.h> 
#include <stdio.h>

char* mystrdup(char* str);

char** token_input(char *input);

void free_argv(char** argv);


#endif
