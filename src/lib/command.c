#include "command.h"

struct command{
	char* description;
	char* input;
	char* output;
	int isPipe;
	int nCommand;
};

COMMAND create_command(){
	COMMAND c = malloc(sizeof(struct command));
	
	c->description = NULL;
	c->input = NULL;
	c->output = NULL;
	c->isPipe = 0;
	c->nCommand = 1;

	return c;
}

char* getDescription(COMMAND c){
	char* s = mystrdup(c->description);
	return s;

}

char* getInput(COMMAND c){
	char *s = mystrdup(c->input);
	return s;

}

char* getOutput(COMMAND c){
	char* s = mystrdup(c->output);
	return s;
}

int getIsPipe(COMMAND c){
	return c->isPipe;
}

int getNCommands(COMMAND c){
	return c->nCommand;
}

void setOutput(COMMAND c, char* output){
	c->output = mystrdup(output);
}

void setInput(COMMAND c, char* input){
	c->input = mystrdup(input);
}

void setDescription(COMMAND c, char* description){
	c->description = mystrdup(description);	
}

void setIsPipe(COMMAND c, int i){
	c->isPipe = i;
}

void setnCommand(COMMAND c, int i){
	c->nCommand = i;
}

void freeCommand(COMMAND c){
	free(c);
}
