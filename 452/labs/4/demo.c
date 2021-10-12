#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

/*
 *AUTHOR:Jacob Stone
 *CLASS:CIS 452
 *DATE: 9/30/21
 *PURPOSE:this program is meant to simulate a thread execution manifested by a file server process
 *The program will take in user input for filename, generate worker threads, repeat asking for filenames until
 *user exits with ^C command
 *The child will sleep for a determined amount of time, and print out file diagnostic message then terminate
 *Lastly, the program prints out diagnostic data of total amount of files serviced
 */


void sigHandler(int sig_num); //gracefully exit program

void* thread_time(void *arg);// thread function 

int counter = 0;//global (A.K.A shared data)

int main() {
	signal(SIGINT, sigHandler);// signal handler for SIGINT

	char filename[100];// variable for user input string 

	while(1){//beginning of loop
	fflush(stdin); // clears mem leak
	printf("Please enter a valid filename to access:\n");//ask user for input
	scanf("%s", filename);//get input 
	printf("Now accessing file: %s\n", filename);// verify input
	
	pthread_t thread;// create thread in loop
	int status;// for error message

	if ((status = pthread_create(&thread, NULL, thread_time, (void *)filename)) != 0) {//calls thread function 
        	fprintf(stderr, "Thread create error %d: %s\n", status, strerror(status));//if error
        	exit(1);//exit program
	}//end if
	if(pthread_detach(thread) > 0){
		printf("error detaching...\n");
	}
	}//end while

	return 0;
}//end main

void *thread_time(void *arg){ //thread function
	counter++; // increases file count
	int sleepNum = rand() % 10; // creating a  random variable to decide amount of sleep
	if(sleepNum >= 2){ //80% probability that sleep is 1 second
		printf("Memory in disk cache\n");
		sleep(1);
	}
	else{ // 20% of the time has a sleep of 7 - 10 seconds
	       printf("One Sec, Memory in hard drive.\n");	       
		sleep((rand() % 4) + 7); // generates a random amount of sleep time from 7 -10
	}
	printf("File: %s Accessed.\n", arg);//prints out file accessed each time

	pthread_exit(0);
}

void sigHandler(int sig_num){ // signal handler function when ^C is pressed
	printf("\nTOTAL FILE REQUESTS RECIEVED: %d\n", counter);//diagnostic statistic
        printf("End Program...\n");//end program
	exit(0);
}
