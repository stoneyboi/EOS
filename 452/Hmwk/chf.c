#include <sys/types.h>

#include <stdio.h>

#include <unistd.h>

int main(){

	pid_t pid, pid1;
	pid = fork();
	if(pid < 0){
		printf("fork() failed\n");
		return(1);
	}

	else if(pid == 0){
		pid1 = getpid();
		printf("pid = %d A \n", pid); // A
		printf("pid1 = %d B \n", pid1); // B
	}

	else{
		pid1 = getpid();
		printf("pid = %d C \n", pid); // C
		printf("pid1 = %d D \n", pid1); // D

	}

	return 0;
}
