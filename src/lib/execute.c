#include "execute.h"


int execute_one_command (COMMAND cmd){
	PIPE pipe = create_pipe();
	int pid,r=1,es,w,status=0;
	char** argv = token_input(getInput(cmd));
	char buff[MAXSIZE*4];
	char output[MAXSIZE*4];

	pid = fork();
	if(pid == 0){
		closeRPipe(pipe);
		dup2(getpWEnd(pipe),1);
		closeWPipe(pipe);
		execvp(argv[0],argv);
		perror("Failed to execute simple command!");
		_exit(-1);
	}
	else{
		if(pid<0){
	 		perror("Failed fork!");
	 		return -1;
	 	}

		closeWPipe(pipe);
		w = waitpid(pid,&status, WUNTRACED);
		if (w<0){			
			perror("Failed to wait for simple command!");
			freePipe(pipe);
			free_argv(argv);
			return -1;
		}                 
		
		if(WIFEXITED(status))
			es=WEXITSTATUS(status);
		
		if (es >= 255){
			printf("Wrong simple process exit status:%d\n",es);
			freePipe(pipe);
			free_argv(argv);
		return -1;
		}


		memset(&buff[0],'\0',sizeof (buff));
		r=read(getpREnd(pipe),&buff,MAXSIZE*4);
		if(r){
			strcpy(output,buff);
			output[r-1]='\0';
			setOutput(cmd,output);
		}
		closeRPipe(pipe);
		freePipe(pipe);
		free_argv(argv);
	}
	return 0;
	
}


int execute_two_commands (COMMAND cmdR, COMMAND cmdW){
	int pid,es,r,length,w,status=0;
	char** argv = token_input(getInput(cmdW));
	char* input = getOutput(cmdR);
	char output [MAXSIZE*4];
	char buff [MAXSIZE*4];

	PIPE pinput = create_pipe();
	PIPE poutput = create_pipe();
	
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
		perror("Failed to execute pipe command!");
		_exit(-1);
	}
	else{
	 	if(pid<0){
	 		perror("Failed fork!");
	 		return -1;
	 	}
		closeWPipe(poutput);
		closeRPipe(pinput);
		if(input)
		write(getpWEnd(pinput),input,length);
		closeWPipe(pinput);
		
		
		w = waitpid(pid,&status, WUNTRACED);
		if (w<0){
			perror("Failed to wait for pipe command!");
			freePipe(poutput);
			freePipe(pinput);
			free(input);
			free_argv(argv);
			return -1;
		}
		if(WIFEXITED(status))
			es=WEXITSTATUS(status);
		
		if (es >= 255){
			printf("Wrong pipe process exit status:%d\n",es);
			freePipe(poutput);
			freePipe(pinput);
			free(input);
			free_argv(argv);
		return -1;
		}
	
		memset(&buff[0],'\0',sizeof(buff));
		r=read(getpREnd(poutput),&buff,MAXSIZE*4);
		if(r){	
		strcpy(output,buff);
		output[r-1] = '\0';
		setOutput(cmdW,output);
		}
	
		free_argv(argv);
		free(input);
		freePipe(pinput);
		freePipe(poutput);
	}
	return 0;
	
}