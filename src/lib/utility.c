#include "utility.h"

char* mystrdup(char* str){
	if(str == NULL) return NULL;
	char *ret = malloc(strlen(str)+1);
	strcpy(ret,str);
	if(ret == NULL) return NULL;
	return ret;
}
