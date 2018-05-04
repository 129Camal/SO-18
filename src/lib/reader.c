#include "reader.h"
#define MAXSIZE 1024

static ssize_t readln (int file, char* buf, size_t nbyte);
static int processDollarLine(char* s, COMMAND c);

D_ARRAY readInput(char* path){

	int file, read = 1, aux;
	char buffer[MAXSIZE];
	char input[MAXSIZE];
	char description[MAXSIZE];

	D_ARRAY darray = init_array(100);

	file = open(path, O_RDONLY, 0644);

	if( file < 0 ){
		perror("Invalid Path");
	}

	while(read>0){
		
		read = readln(file, buffer, 1024);
		
		if(buffer[0] == '$'){
			COMMAND c = create_command();
			aux = processDollarLine(buffer, c);
			strcpy(input, buffer+aux);
			setDescription(c,description);
			setInput(c,input);
			array_insert(darray, c);
		
		} else {
			strncpy(description, buffer,read);
		}
		memset(&buffer[0],'\0',sizeof(buffer));

	}
	close(file);
	return darray;
}



	ssize_t readln(int file, char* buf, size_t nbyte){
	int n=0 , r;
	char* p = buf;

	while ((r = read(file, p+n, 1)) > 0 && n < nbyte){
		if (p[n] == '\n'){

			buf[n] = '\0';
			return n+1;
		}
		
		n++;
	}
	return n;
}


static int processDollarLine(char* s, COMMAND c){
	int i,j=0;
	char nC[10];
	
	for(i = 0; i < strlen(s); i++){
		if(s[i] == '|'){
			setIsPipe(c, 1);
			if(j>0)	setnCommand(c, atoi(nC));
			while(s[i] != ' ') i++;
			i++;
			break;
		}
		else{
			if(s[i] != '$'){
			nC[j]=s[i];
			j++;
			}

			if(s[i] == ' '){
			i++;
			break;
			}
		}
	}
	return i;
}

