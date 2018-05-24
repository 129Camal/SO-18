#include "execute.h"


int execute_one_command (COMMAND cmd){
	PIPE pipe = create_pipe();
	char** argv = token_input(getInput(cmd));
	char buff[1024*2];
	char output[1024*2];
	int pid,r=1,es;

	pid = fork();
	if(pid == 0){
		closeRPipe(pipe);
		dup2(getpWEnd(pipe),1);
		closeWPipe(pipe);
		execvp(argv[0],argv);
		perror("Failed to execute command!");
		_exit(-1);
	}
	else{
		closeWPipe(pipe);
		int w,status=0;
		w = waitpid(pid,&status, WUNTRACED);
		if (w<0){			
			perror("Failed to exit command!");
			return -1;
		}                 
		
		if(WIFEXITED(status)){
			 es=WEXITSTATUS(status);
		}
		if (es != 0){
		return -1;
		}


		memset(&buff[0],'\0',sizeof (buff));
		r=read(getpREnd(pipe),buff,1024*2);
		if(r){
			strcpy(output,buff);
			output[r-1]='\0';
			setOutput(cmd,output);
		}
		closeRPipe(pipe);
		freePipe(pipe);
	}
	return 0;
	
}


int execute_two_commands (COMMAND cmdR, COMMAND cmdW){
	PIPE pinput = create_pipe();
	PIPE poutput = create_pipe();

	char** argv = token_input(getInput(cmdW));
	int pid,es,r;
	char* input = getOutput(cmdR);
	char output [1024*2];
	char buff [1024*2];
	int length; 
	if (input)
		length = strlen(input);
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
		_exit(-1);
	}
	else{
		closeWPipe(poutput);
		closeRPipe(pinput);
		
		write(getpWEnd(pinput),input,length);
		closeWPipe(pinput);
		
		int w,status=0;
		w = waitpid(pid,&status, WUNTRACED);
		if (w<0){			
			perror("Failed to exit command!");
			return -1;
		}
		if(WIFEXITED(status))
			es=WEXITSTATUS(status);
		if (es != 0){
		free(input);
		return -1;
		}
	
		memset(&buff[0],'\0',sizeof(buff));
		r=read(getpREnd(poutput),&buff,1024*2);
		strcpy(output,buff);
		output[r-1] = '\0';
		setOutput(cmdW,output);
	


		free(input);
		freePipe(pinput);
		freePipe(poutput);
	}
	return 0;
	
}