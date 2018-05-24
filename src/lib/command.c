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

void toString_command(char* print, COMMAND cmd){
	char *description = getDescription(cmd);
	int nC;
	if(description){
		strcpy(print,description);
		strcat(print,"\n");
		free(description);
	}
	strcat(print,"$");
	if (getIsPipe(cmd)){
		if((nC=getNCommands(cmd))>1){
			char ncommand[10];
			strcpy(ncommand,myitoa(nC));
			strcat(print,ncommand);
		}
		strcat(print,"|");
	}
	else strcat(print," ");
	
	char*input = getInput(cmd);
	strcat(print,input);
	strcat(print,"\n");
	strcat(print,">>>\n");
	free(input);
	char *output = getOutput(cmd);
	if(output){
		strcat(print,output);
		strcat(print,"\n");
		free(output);	
	}
	strcat(print,"<<<\n");
}
