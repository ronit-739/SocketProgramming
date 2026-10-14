#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define BUFF_SIZE 1024

void error_handling(char * error);

int main(int argc, char * argv[])
{
	// we are taking port no from user initially
	if(argc!=3)
	{
		printf("usage: %s <port no eg 8080> <ip address eg 122.168.1.1>", argv[0]);
		exit(1);
	}
	
	// make a socket
	int server_sock=socket(AF_INET, SOCK_STREAM, 0);
	
	//checking for error
	if(server_sock==-1)
	{
		error_handling("server Socket Creation Error");
	}
	
	
	// for binding create address
	
	
    struct sockaddr_in server_addr = {0};
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(atoi(argv[1]));   // atoi converts ascii to int
	if (!inet_aton(argv[2], &server_addr.sin_addr)) // ip to address conversion eg 255.255.255.255 to 0x ffffffff
	{
		error_handling("ip to address conversion error");
	}
	
	
	if(connect(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr))==-1)
	{
		error_handling("connection error:");
	}
	else{
		printf("connection is established\n");
		
	}
	
char message[BUFF_SIZE];
	
	// communication
	
	
	// read -> total size of buffer
	//write -> stringlength only
	// both return total no of byte read or write
	
	while(1)
	{
		
		fputs("Input message: (enter 'q' or 'Q' to quit):", stdout);
		fgets(message, BUFF_SIZE, stdin);
		if(strcmp(message, "q\n")==0||strcmp(message, "Q\n")==0)
		{
			break;
		}
		write(server_sock, message, strlen(message));
		int stringLength_of_readed_message=read(server_sock, message, sizeof(message)-1); // read does not add '\0' at end
		message[stringLength_of_readed_message]='\0';
		printf("message from server is : %s\n", message);
		
	}
	close(server_sock);
	
	
	

	return 0;
}

void error_handling(char * error)
{
	perror(error);
	exit(1);
}
