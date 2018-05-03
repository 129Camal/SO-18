#include "execute.h"


int execute_no_pipe (COMMAND cmd){
	PIPE pipe = create_pipe();
	char** argv = token_input(getInput(cmd));
	char buff[1024];
	char output[1024];
	int pid,r=1;

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
		int status=0;
		wait(&status);
		if(WIFEXITED(status)){
			int es=WEXITSTATUS(status);
			printf("EXIT STATUS: %d\n",es);
		}
		else {			
			perror("Failed to execute command!File not overwrited.");
			exit(-1);
		}
		r=read(getpREnd(pipe),&buff,1024);
		strncpy(output,buff,r);
		setOutput(cmd,output);
		}
	return 0;
	
}

/*
int execute_pipe (COMMAND cmd, PIPE){
	//int e_pipe[2];
	int pid;
	//if (pipe(e_pipe)){
		//perror("Error! Couldn't create pipe!");
		//exit(-1);
	//}
	pid = fork();
	if(pid == 0){
		//close(e_pipe[0]);
		//dup2(e_pipe[1],1);
		//close(e_pipe[1]);
		execvp(cmd[0],cmd);
		perror("Failed to execute command!");
		exit(-1);
	}
	else{
		int status=0;
		wait(&status);
		if(WIFEXITED(status)){
			int es=WEXITSTATUS(status);
			printf("EXIT STATUS: %d\n",es);
		}
		else {			
			perror("Failed to execute command!File not overwrited.");
			exit(-1);
		}

	}
	return 0;
	
}

*/