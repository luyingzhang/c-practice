/*
 * m3k_socket_server.c
 *
 *  Created on: 2012/5/7
 *      Author: boris
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>

int main(){
	int sockfd, new_fd, numbytes;
	struct sockaddr_in my_addr;
	struct sockaddr_in their_addr;
	int sin_size;
	char buf[100];

	//TCP socket
	if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1 ){
		perror("socket");
		exit(1);
	}

	//Initail, bind to port 65075
	my_addr.sin_family = AF_INET;
	my_addr.sin_port = htons(65075);
	my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	bzero( &(my_addr.sin_zero), 8 );

	//binding
	if ( bind(sockfd, (struct sockaddr*)&my_addr, sizeof(struct sockaddr)) == -1 ){
		perror("bind");
		exit(1);
	}

	//Start listening
	if ( listen(sockfd, 10) == -1 ){
		perror("listen");
		exit(1);
	}

	//Wait for connect!
	while(1){
		sin_size = sizeof(struct sockaddr_in);
		perror("server is run");
		if ( (new_fd = accept(sockfd, (struct sockaddr*)&their_addr, &sin_size)) == -1 ){
			perror("accept");
			exit(1);
		}

		if ( !fork() ){
			//Receive
			if ( (numbytes = read(new_fd, buf, sizeof(buf))) == -1 ){
			  	perror("recv");
				exit(1);
			}
			printf("Receive %d bytes , ", numbytes);
			printf("%s\n", buf);
			//Send back
			if ( (numbytes = write(new_fd, buf, strlen(buf))) == -1){
				perror("send");
				exit(0);
			}
			printf("Send %d bytes , ", numbytes);
			printf("%s\n", buf);
			close(new_fd);
		}
	}
	close(sockfd);
	return 0;
}
