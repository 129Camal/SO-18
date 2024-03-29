#ifndef __COMMAND__
#define __COMMAND__

#include "utility.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct command *COMMAND;



COMMAND create_command();

char* getDescription(COMMAND c);

char* getInput(COMMAND c);

char* getOutput(COMMAND c);

int getIsPipe(COMMAND c);

int getNCommands(COMMAND c);

void setOutput(COMMAND c, char* output);

void freeCommand(COMMAND c);

void setIsPipe(COMMAND c, int i);

void setnCommand(COMMAND c, int i);

void setInput(COMMAND c, char* input);

void setDescription(COMMAND c, char* description);

void toString_command(char* print, COMMAND cmd);

#endif