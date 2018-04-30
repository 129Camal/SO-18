#include "command.h"

struct command{
	char* description;
	char* input;
	char* output;
	int isPipe;
	int nCommand;
}

COMMAND create_command(){
	COMMAND c = malloc(sizeof(struct command));
	c->description = NULL;
	c->input = NULL;
	c->output = NULL;
	c->isPipe = 0;
	c->nCommand = 1;
}

char* getDescription(COMMAND c){

	char* s = strdup(c->description);
	return s;

}

char* getInput(COMMAND c){

	char* s = strdup(c->input);
	return s;

}

char* getOutput(COMMAND c){

	char* s = strdup(c->output);
	return s;

}

int getIsPipe(COMMAND c){

	return c->isPipe;


}

int getNCommands(COMMAND c){

	return c->nCommand;

}

void setOutput(COMMAND c, char* output){

	c->output = output;
	
}


