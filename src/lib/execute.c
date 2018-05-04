#include "execute.h"


int execute_no_pipe (COMMAND cmd){
	PIPE pipe = create_pipe();
	char** argv = token_input(getInput(cmd));
	char buff[1024];
	char output[1024];
	int pid,r=1,es;

	pid = fork();
	if(pid == 0){
		closeRPipe(pipe);
		dup2(getpWEnd(pipe),1);
		closeWPipe(pipe);
		execvp(argv[0],argv);
		perror("Failed to execute command!");
		exit(-1);
	}
	else{
		closeWPipe(pipe);
		int status=0;
		wait(&status);
		if(WIFEXITED(status)){
			 es=WEXITSTATUS(status);
		}
		else {			
			perror("Failed to execute command!File not overwrited.");
			exit(-1);
		}
		if (es == 0){
			memset(&buff[0],'\0',sizeof (buff));
			r=read(getpREnd(pipe),buff,1024);
			if(r){
				strcpy(output,buff);
				output[r-1]='\0';
				setOutput(cmd,output);
			}
		}
		closeRPipe(pipe);
	}
	return 0;
	
}


int execute_pipe (COMMAND cmdR, COMMAND cmdW){
	PIPE pinput = create_pipe();
	PIPE poutput = create_pipe();

	char** argv = token_input(getInput(cmdW));
	int pid,es,r;
	char* input = getOutput(cmdR);
	char output [1024];
	char buff [1024];
	int length = strlen(input);

	pid = fork();
	if(pid == 0){
		closeWPipe(pinput);
		closeRPipe(poutput);


		dup2(getpREnd(pinput),0);
		closeRPipe(pinput); 
	
		dup2(getpWEnd(poutput),1);
		closeWPipe(poutput);

		execvp(argv[0],argv);
		perror("Failed to execute command!");
		exit(-1);
	}
	else{
		closeWPipe(poutput);
		closeRPipe(pinput);
		
		write(getpWEnd(pinput),input,length);
		closeWPipe(pinput);
		int status=0;
		wait(&status);
		if(WIFEXITED(status)){
			es=WEXITSTATUS(status);
		}
		else {			
			perror("Failed to execute command!File not overwrited.");
			exit(-1);
		}
		if (es == 0){
		memset(&buff[0],'\0',sizeof(buff));
		r=read(getpREnd(poutput),&buff,1024);
		strcpy(output,buff);
		output[r-1] = '\0';
		setOutput(cmdW,output);
		}

	}
	return 0;
	
}