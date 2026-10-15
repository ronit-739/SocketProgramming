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
	int server_sock=socket(AF_INET, SOCK_DGRAM, 0);
	
	//checking for error
	if(server_sock==-1)
	{
		error_handling("UDP server Socket Creation Error");
	}
	
	
	// for binding create address
	
       struct sockaddr_in from_addr = {0};
socklen_t from_addr_len = sizeof(from_addr);
// i created this to store  response address from server


    struct sockaddr_in server_addr = {0};
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(atoi(argv[1]));   // atoi converts ascii to int
	if (!inet_aton(argv[2], &server_addr.sin_addr)) // ip to address conversion eg 255.255.255.255 to 0x ffffffff
	{
		error_handling("ip to address conversion error");
	}
	
	// no need for connection
	
char message[BUFF_SIZE];
	
	// communication
	
	
	// rcevfrom() -> total size of buffer
	//sendto() -> stringlength only
	// both return total no of byte read or write
	
	socklen_t serveraddr_len=sizeof(server_addr);
	while(1)
	{
	
		
		fputs("Input message: (enter 'q' or 'Q' to quit):", stdout);
		fgets(message, BUFF_SIZE, stdin);
		if(strcmp(message, "q\n")==0||strcmp(message, "Q\n")==0)
		{
			break;
		}
		sendto(server_sock, message, strlen(message), 0, (struct sockaddr *)&server_addr, serveraddr_len);
		int stringLength_of_readed_message=recvfrom(server_sock, message, sizeof(message),0,(struct sockaddr *)&from_addr, &from_addr_len); // read does not add '\0' at end
		
		if(stringLength_of_readed_message==-1)
		{
			error_handling("read error");
		}
		
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
