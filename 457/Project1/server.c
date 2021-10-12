/* A simple server in the internet domain using TCP

   The port number is passed as an argument */

#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <string.h>

void error(char *msg){

    perror(msg);
    exit(1);
}


int main(int argc, char *argv[]){
	//initial variables
     int sockfd, newsockfd, portno, clilen;
     char buffer[1000]; //message array
     struct sockaddr_in serv_addr, cli_addr;
     int n; // flag for checking error
     int goodbyeFlag = 1;// while loop 

     if (argc < 2){// stdin is 1 so anything higher is an error
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
     }

     sockfd = socket(AF_INET, SOCK_STREAM, 0); //create socket

     if (sockfd < 0){ // check socket opens correctly
        error("ERROR opening socket");
     }
     
     bzero((char *) &serv_addr, sizeof(serv_addr)); // clears server stdin
     portno = atoi(argv[1]);//port no is stdin
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);

     if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
          error("ERROR on binding"); // binds server and client
     }
     
     listen(sockfd,5); // checks for new connections (5 new)
     clilen = sizeof(cli_addr);// sets client length to structure
     newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen); //part of the three way handshake
	// accepts connection of server call	

     if (newsockfd < 0) { // checks to see if accepted correctly
          error("ERROR on accept");
          }

     printf("Respond? (Ctrl + C to quit)");

     while(goodbyeFlag){ //infinte loop

     bzero(buffer,1000); // char array for message is cleared out
     n = read(newsockfd,buffer,999); //scans in message from client 
     	
     if (n < 0){ // n is 0 is read occurs successfully
     	error("ERROR reading from socket");
     }
     
     printf("Client said: %s\n",buffer);
     printf("Your response: ");

     bzero(buffer, 1000);//clears array 
     fgets(buffer, 999, stdin);//scans message and puts into empty array

     n = write(newsockfd, buffer, strlen(buffer)); //writes to client 

     if (n < 0) { // n is 0 is write is successful
     	error("ERROR writing to socket");
	}
     }//end of While loop

     return 0; 

}//end of main


