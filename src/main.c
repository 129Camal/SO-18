#include "reader.h"
#include "pipe.h"
#include "execute.h"
#include <stdlib.h>

int main(int argc, char** argv){
	if (argc!=3){
		perror("You need 2 arguments! Missing path's");
		exit(-1);
	}
	COMMAND* lc;
	int i,nC;
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
						execute_pipe(c2,c1);
					}
					else execute_no_pipe(c1);
				}
				
			}
			int file = open(argv[2],O_CREAT|O_TRUNC|O_RDWR,0644);
			if(file<0){
				perror("Error opening the file!");
				exit(-1);
			}
			for(i=0;i<count;i++){
				COMMAND cmd = lc[i];
				char  print[1024];
				if(getDescription(cmd)){
				strcpy(print,getDescription(cmd));
				strcat(print,"\n");	
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
				if(getInput(cmd))
				strcat(print,getInput(cmd));
				strcat(print,"\n");
				strcat(print,">>>\n");
				if(getOutput(cmd))
				strcat(print,getOutput(cmd));
				strcat(print,"\n");
				strcat(print,"<<<\n");
				write(file,print,strlen(print));

			}
			close(file);
		}
	}

	free_array(d);


	return 0;
}