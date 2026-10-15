#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#define BUFF_SIZE 1024

void error_handling(char * error);

int main(int argc, char * argv[])
{
	// we are taking port no from user initially
	if(argc!=2)
	{
		printf("usage: %s <port no eg 8080>", argv[0]);
		exit(1);
	}
	
	// make a socket , we use dgram for UDP
	int server_sock=socket(AF_INET, SOCK_DGRAM, 0);
	
	//checking for error
	if(server_sock==-1)
	{
		error_handling("UDP server Socket Creation Error");
	}
	
	
	// for binding create address
   struct sockaddr_in client_addr = {0};
    struct sockaddr_in server_addr = {0};
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(atoi(argv[1]));   // atoi converts ascii to int
	server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	
	
	if(bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr))==-1)
	{
		error_handling("binding error:");
	}
	
	
	
	// here in UDP we donot need for listening and accepting we can directly communicate
	// thers is no handshaking
	// also it can resopond to many client because no connection was established in the first place
	// it is like a multiple uncommitted relationship lol
		 


   // we still need buffer for storing message
    char message[BUFF_SIZE];
    ssize_t size;
	
	while(1)
	{
		// because client address and its size can differ we put this in loop
    socklen_t size_of_clientaddr=sizeof(client_addr);
	
	
        size = recvfrom(server_sock, message, sizeof(message),0,(struct sockaddr *)&client_addr, &size_of_clientaddr);   // instead of read() in tcp we now use rcevfrom()
    
		//ssize_t recvfrom(int socket, void *buffer, size_t length, int flags, struct sockaddr *address, socklen_t *address_len);   
		// In TCP we used accept where we also neef to define space for client address but we specified NULL
		
		
		// now we send again using 
		//ssize_t sendto(int sockfd, const void *buf, size_t len, int flags,const struct sockaddr *dest_addr, socklen_t addrlen)
         sendto(server_sock, message, size, 0, (struct sockaddr *)&client_addr, size_of_clientaddr);
    
	}
	 
	close (server_sock);
	return 0;
}

void error_handling(char * error)
{
	perror(error);
	exit(1);
}
