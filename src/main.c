#include "reader.h"
#include "pipe.h"
#include "execute.h"
#include <stdlib.h>

int main(int argc, char** argv){
	if (argc!=2){
		perror("You need 1 arguments! Missing path");
		exit(-1);
	}
	COMMAND* lc;
	int i,nC,flag = 0;
	D_ARRAY d = readInput(argv[1]);

	if (d){
		int count = getPos(d);
		lc = getArray(d);
		if(lc){
			for (i = 0;i < count ;i++){
				COMMAND c1 = lc[i];
				if (c1){
					if(getIsPipe(c1)){
						COMMAND c2 = lc[i-getNCommands(c1)];
						flag = execute_pipe(c2,c1);
					}
					else flag = execute_no_pipe(c1);
				}
				if (flag == -1){
					printf("Error executing command, file not overwritten!\n");
					_exit(-1);
				}
				
			}
			int file = open(argv[1],O_CREAT|O_TRUNC|O_RDWR,0644);
			if(file<0){
				perror("Error opening the file!");
				exit(-1);
			}
			for(i=0;i<count;i++){
				COMMAND cmd = lc[i];
				char  print[1024*3];
				char *description = getDescription(cmd);
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
				char*input = getInput(cmd);
				strcat(print," ");
				strcat(print,input);
				strcat(print,"\n");
				strcat(print,">>>\n");
				char *output = getOutput(cmd);
				if(output){
				strcat(print,output);
				strcat(print,"\n");
				free(output);	
				}
				strcat(print,"<<<\n");
				write(file,print,strlen(print));
				free(input);
			}
			close(file);
		}
	}

	free_array(d);


	return 0;
}