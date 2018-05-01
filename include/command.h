#ifndef __COMMAND__
#define __COMMAND__

#include <stdio.h>
#include <string.h>

typedef struct command *COMMAND;

COMMAND create_command();

char* getDescription(COMMAND c);

char* getInput(COMMAND c);

char* getOutput(COMMAND c);

int getIsPipe(COMMAND c);

int getNCommands(COMMAND c);

void setOutput(COMMAND c, char* output);

void freeCommand(COMMAND c);

#endif