#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


void error(char *msg){

    perror(msg);
    exit(0);
}


int main(int argc, char *argv[]){
	//initial  variables
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    int talking = 1;
    char buffer[1000]; // messages up to 1000 characters long


    if (argc < 3) { //stdin and stdout are 1 and 2, anything over is wrong
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }

    portno = atoi(argv[2]);// stdout
    sockfd = socket(AF_INET, SOCK_STREAM, 0);//create socket

    if(sockfd < 0){ // check if opened correctly
    	error("ERROR opening socket");
    }
    
    server = gethostbyname(argv[1]);//stdin

    if (server == NULL){ // check for server
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));//clears server stdin
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);

    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0){
        error("ERROR connecting"); // checks connection of socket 
    }
    
    while(talking){//infinite loop  until ^C is pressed
    printf("Please enter the message: (Ctrl + C to quit)");
    
    bzero(buffer, 1000);//clears array of char
    fgets(buffer, 999, stdin);// scans data from stdin

    n = write(sockfd, buffer, strlen(buffer)); //writes message to server 

    if(n < 0){ // n is 0 if successful writing occurs
         error("ERROR writing to socket");
    }

    bzero(buffer,1000); //clear array and read for response from server
    n = read(sockfd,buffer,999);//reads from server

    if(n < 0){ // n is 0 if successful read occurs
         error("ERROR reading from socket");
    }

    printf("Server said: %s\n", buffer);//output from server
    }

    return 0;

}


