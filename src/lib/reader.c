#include "reader.h"

static ssize_t readln (int file, char* buf, size_t nbyte);
static int processDollarLine(char* s, COMMAND c);

D_ARRAY readInput(int file){

	int read = 1, aux;
	char buffer[MAXSIZE];
	char input[MAXSIZE];
	char description[MAXSIZE];

	D_ARRAY darray = init_array(100);

	while(read>0){
		
		read = readln(file,buffer, MAXSIZE);
		
		if(buffer[0] == '$'){
			COMMAND c = create_command();
			aux = processDollarLine(buffer, c);
			strcpy(input, buffer+aux);
			setDescription(c,description);
			description[0]='\0';
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
	int i,flag = 0;
	char *nC,*aux;
    aux = mystrdup(s);

	for(i = 0; i < strlen(s); i++){
		if(s[i] == '|'){
			setIsPipe(c, 1);
			if(flag)	
				setnCommand(c, atoi(nC));
			if(s[i+1] != ' ')
				break;
		}
		else{
			if(strchr("$| ",s[i]) == NULL){
				nC = strtok(aux+i,"|");
				flag++;
			}

		if(s[i] == ' '){
			break;
			}
		}
	}

	free(aux);
	return i+1;
}



