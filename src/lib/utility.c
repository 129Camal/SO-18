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
		ret[i]=token;
		i++;	
		token = strtok(NULL," ");
	}
	ret[i]=token;
	return ret;
} 

char* myitoa(int i){
	char* n = malloc(10);
	sprintf(n,"%d",i);
	return n;
}

