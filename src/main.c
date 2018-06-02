#include "reader.h"
#include "execute.h"
#include <stdlib.h>

int main(int argc, char** argv){
	if (argc<2){
		perror("You need at least 1 more argument! Missing file/s");
		_exit(-1);
	}
	for(int nFiles = 1; nFiles < argc;nFiles ++){

	COMMAND* lc;
	int i,file,flag = 0;
	D_ARRAY d;

	file = open(argv[nFiles],O_RDONLY);
	
	if (file)
	 d = readInput(file);
	else{
		perror("Error opening file for reading!");
		_exit(-1);	
	}
	close (file);



	if (d){
		int count = getPos(d);
		lc = getArray(d);
		if(lc){
			for (i = 0;i < count ;i++){
				COMMAND c1 = lc[i];
				if (c1){
					if(getIsPipe(c1)){
						COMMAND c2 = lc[i-getNCommands(c1)];
						flag = execute_two_commands(c2,c1);
					}
					else flag = execute_one_command(c1);
				}
				if (flag == -1){
					printf("File not overwritten!\n");
					_exit(-1);
				}
				
			}


			file = open(argv[nFiles],O_TRUNC|O_WRONLY);
			if(file<0){
				perror("Error opening the file, for writing!");
				_exit(-1);
			}
			char print[1024*4];
			for(i=0;i<count;i++){
				COMMAND cmd = lc[i];
				toString_command(print,cmd);
				write(file,&print,strlen(print));
			}
			close(file);
		}
	}

	free_array(d);
	}


	return 0;
}

