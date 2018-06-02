#include "utility.h"

char* mystrdup(char* str){
	if(str == NULL) return NULL;
	char *ret = malloc(strlen(str)+1);
	strcpy(ret,str);
	if(ret == NULL) return NULL;
	return ret;
}



char** token_input(char *input){
	char *token;
	char **ret= (char**) malloc(30*sizeof(char*));
	int i=0;
	token = strtok(input," ");
	while(token!=NULL){
		ret[i]=mystrdup(token);
		i++;
		token = strtok(NULL," ");
	}
	ret[i]=mystrdup(token);
	free(input);
	return ret;
} 

void free_argv(char** argv){
	int i=0;
	while (argv[i]){
		free(argv[i]);
		i++;
	}
	free(argv);
}

