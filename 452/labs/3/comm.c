#include <signal.h>

#include <stdio.h>

#include <unistd.h>

#include <stdbool.h>

#include <sys/types.h>

#include <sys/wait.h>

#include <errno.h>

bool running = true; // boolean varible for conditions
int signalKill = 5; // loop variable 


void sigHandler1(int number) { //usr1 function

    printf ("recieved a SIGUSR1 signal\n");

}

void sigHandler2(int number) { // usr2 function
	printf("recieved a SIGUSR2 signal\n");
}

void killSig(int number) { //kill function
	printf(" Recieved.\n");
	signalKill--;
}


int main() {

	// both parent and child have signals instantiated here since both in the main loop
    signal(SIGUSR1, sigHandler1);
    signal(SIGUSR2, sigHandler2);
    signal(SIGINT, killSig);
 
	
    pid_t who = fork();
   pid_t parent = getpid(); 
	int rand = 16272;
    if (who == 0) {// Child Process 
       while (running ) {
	printf("waiting...\t");
        sleep(rand % 3);// child sleeps 
	kill(parent, SIGUSR1);
	rand/=3;
        }
        return 0; // returns a SIGUSR argument to parent
    }

    else {// parent process

        int code;

           printf ("Spawned Child PID#%d\n", who); // who returns PID of child to parent
	while(running || signalKill > 0){ // loop 
	   pause();// wait for signal
	   usleep(300000); // microseconds
	   kill(who, SIGUSR2);
	   if (errno == EINTR) {// improper call?
            perror ("Oops...");// go here
   	   }

        }
	if(signalKill == 0){
		running = false;
		kill(parent, SIGINT);
		kill(who, SIGINT);
	}
        wait(&code);
	if(signalKill < 5){// once flag is triggered, the code will execute the loop five more times
	signalKill--;// start terminating process by decrementing
	}
    }

    printf ("That's it, I'm shutting you down\n"); // gracefull shutdown

}
